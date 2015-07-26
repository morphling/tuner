extern crate alsa;

use std::ffi::CString;
use alsa::Direction;
use alsa::pcm::{PCM, HwParams, Format, Access, State};

const SAMPLE_RATE: u32 = 44100;
// Smallest phase - phase of highest frequency
// Choose 55Hz - 110Hz for now, so:
const PHASE_MIN: usize = 401; // 44100/110
const PHASE_MAX: usize = 802; // 44100/55

const SAMPLES: usize = PHASE_MAX*2;

type Sample = i16;

struct Config {
    card: CString
}

fn default_config() -> Config {
    Config {
        card: CString::new("default").unwrap()
    }
}

fn error_squared(a: Sample, b: Sample) -> u64 {
    let d = (a as i32 - b as i32) as i64;
    return (d*d) as u64;
}

fn window_error(data: &[Sample], offset: usize, error_limit: u64) -> u64 {
    let mut error = 0;
    for i in 0..PHASE_MAX {
        error += error_squared(data[i], data[i+offset]);
        if error >= error_limit {
            break;
        }
    }
    return error;
}

fn phase(data: &[Sample]) -> usize {
    let mut min_error = window_error(data, PHASE_MIN, u64::max_value());
    let mut min_phase = 0;
    for phase in PHASE_MIN + 1 .. PHASE_MAX {
        let error = window_error(data, phase, min_error);
        if error < min_error {
            min_error = error;
            min_phase = phase;
        }
    }
    return min_phase;
}

// Frequency range:
// Cello & Guitar open strings
// + some room downwards for drop tunings (1 tone?)
// + some room both directions for being off (semitone?)

// Actually, autocorrelation is terrible with octaves anyways, so why not
// just go over one octave? Preferably the lowest, I think.

fn main() {
    // make_noise();
    let config = default_config();

    {
        let pcm = PCM::open(&*config.card, Direction::Capture, false).unwrap();

        let hwp = HwParams::any(&pcm).unwrap();
        hwp.set_channels(1).unwrap();
        hwp.set_rate(SAMPLE_RATE, 0).unwrap();
        hwp.set_format(Format::s16()).unwrap();
        hwp.set_access(Access::RWInterleaved).unwrap();
        pcm.hw_params(&hwp).unwrap();
        let io = pcm.io_i16().unwrap();

        pcm.prepare().unwrap();
        loop {
            let mut data = [0i16; SAMPLES];
            assert_eq!(io.readi(&mut data).unwrap(), SAMPLES);
            let phase = phase(&data);
            println!("phase: {}, freq: {}", phase, SAMPLE_RATE as f64 / phase as f64);
        }
    }
    const n :usize = 100;
    let mut buf = [0i16; n*1024];

    {
        let pcm = PCM::open(&*config.card, Direction::Capture, false).unwrap();

        let hwp = HwParams::any(&pcm).unwrap();
        hwp.set_channels(1).unwrap();
        hwp.set_rate(SAMPLE_RATE, 0).unwrap();
        hwp.set_format(Format::s16()).unwrap();
        hwp.set_access(Access::RWInterleaved).unwrap();
        pcm.hw_params(&hwp).unwrap();
        let io = pcm.io_i16().unwrap();

        pcm.prepare().unwrap();
        assert_eq!(io.readi(&mut buf[..]).unwrap(), n*1024); //2*44100);//, 1024);

        pcm.drain().unwrap();
    }

    println!("playback!");

    let pcm = PCM::open(&*config.card, Direction::Playback, false).unwrap();

    // Set hardware parameters: 44100 Hz / Mono / 16 bit
    let hwp = HwParams::any(&pcm).unwrap();
    hwp.set_channels(1).unwrap();
    hwp.set_rate(SAMPLE_RATE, 0).unwrap();
    hwp.set_format(Format::s16()).unwrap();
    hwp.set_access(Access::RWInterleaved).unwrap();
    pcm.hw_params(&hwp).unwrap();
    let io = pcm.io_i16().unwrap();

    // Play recording back for 2 seconds.
    //for _ in 0..2*44100/1024 {
        assert_eq!(io.writei(&buf[..]).unwrap(), n*1024);//2*44100);//, 1024);
    //}

    // In case the buffer was larger than 2 seconds, start the stream manually.
    if pcm.state() != State::Running { pcm.start().unwrap() };
    // Wait for the stream to finish playback.
    pcm.drain().unwrap();
}

fn make_noise() {
    // Open default playback device
    let pcm = PCM::open(&*CString::new("default").unwrap(), Direction::Playback, false).unwrap();

    // Set hardware parameters: 44100 Hz / Mono / 16 bit
    let hwp = HwParams::any(&pcm).unwrap();
    hwp.set_channels(1).unwrap();
    hwp.set_rate(44100, 0).unwrap();
    hwp.set_format(Format::s16()).unwrap();
    hwp.set_access(Access::RWInterleaved).unwrap();
    pcm.hw_params(&hwp).unwrap();
    let io = pcm.io_i16().unwrap();

    // Make a sine wave
    let mut buf = [0i16; 1024];
    for (i, a) in buf.iter_mut().enumerate() {
        *a = ((i as f32 * 2.0 * ::std::f32::consts::PI / 128.0).sin() * 8192.0) as i16
    }

    // Play it back for 2 seconds.
    for _ in 0..2*44100/1024 {
        assert_eq!(io.writei(&buf[..]).unwrap(), 1024);
    }

    // In case the buffer was larger than 2 seconds, start the stream manually.
    if pcm.state() != State::Running { pcm.start().unwrap() };
    // Wait for the stream to finish playback.
    pcm.drain().unwrap();
}
