#include <limits.h>
#include <stdio.h>

#define WINDOW 1024
#define SAMPLE_RATE 32768

signed char bass[2048] =
{
       7,    6,    6,    7,    6,    7,    7,    6,    6,    7,    6,    5,    6,    6,    5,    4,
       4,    3,    4,    3,    3,    2,    1,    2,    1,    1,    0,    0,   -1,   -1,   -2,   -2,
      -3,   -3,   -4,   -4,   -5,   -6,   -7,   -7,   -8,   -9,  -10,  -10,  -11,  -12,  -13,  -13,
     -14,  -15,  -15,  -16,  -17,  -18,  -18,  -19,  -20,  -21,  -22,  -23,  -23,  -24,  -25,  -25,
     -26,  -27,  -28,  -28,  -29,  -30,  -31,  -32,  -33,  -33,  -34,  -35,  -36,  -36,  -37,  -38,
     -38,  -39,  -40,  -41,  -41,  -42,  -43,  -44,  -44,  -45,  -45,  -46,  -47,  -48,  -49,  -49,
     -50,  -50,  -51,  -52,  -52,  -53,  -53,  -54,  -54,  -55,  -55,  -56,  -56,  -57,  -58,  -58,
     -59,  -58,  -59,  -60,  -59,  -60,  -60,  -61,  -60,  -61,  -62,  -61,  -62,  -61,  -62,  -62,
     -63,  -62,  -63,  -62,  -63,  -62,  -62,  -63,  -62,  -63,  -62,  -61,  -61,  -62,  -61,  -60,
     -60,  -61,  -60,  -60,  -59,  -58,  -57,  -57,  -56,  -56,  -55,  -56,  -55,  -55,  -54,  -53,
     -52,  -52,  -51,  -50,  -50,  -49,  -47,  -47,  -46,  -46,  -44,  -43,  -42,  -42,  -40,  -39,
     -39,  -37,  -36,  -35,  -34,  -33,  -32,  -30,  -29,  -28,  -27,  -25,  -24,  -22,  -21,  -20,
     -18,  -17,  -15,  -14,  -12,  -11,   -9,   -8,   -6,   -5,   -3,   -1,    1,    2,    4,    5,
       7,    9,   10,   12,   13,   15,   16,   19,   20,   22,   23,   24,   26,   27,   29,   30,
      32,   34,   36,   37,   39,   40,   42,   43,   45,   46,   47,   48,   49,   51,   52,   53,
      54,   56,   57,   58,   59,   60,   61,   62,   63,   64,   64,   65,   66,   67,   67,   68,
      68,   69,   70,   70,   71,   70,   71,   72,   71,   72,   71,   72,   71,   72,   71,   72,
      71,   70,   71,   70,   69,   69,   68,   67,   67,   66,   65,   64,   64,   63,   62,   61,
      60,   59,   58,   57,   56,   54,   53,   52,   51,   49,   48,   47,   46,   44,   43,   41,
      40,   38,   36,   34,   32,   31,   30,   29,   27,   26,   24,   23,   21,   19,   17,   16,
      15,   13,   12,   10,    8,    6,    5,    3,    2,    0,   -1,   -3,   -4,   -6,   -7,   -8,
     -10,  -11,  -13,  -14,  -16,  -17,  -18,  -19,  -21,  -22,  -24,  -25,  -27,  -27,  -28,  -30,
     -31,  -32,  -33,  -35,  -36,  -37,  -38,  -39,  -40,  -41,  -42,  -43,  -44,  -45,  -45,  -46,
     -47,  -48,  -49,  -50,  -50,  -51,  -52,  -53,  -53,  -54,  -55,  -55,  -56,  -57,  -58,  -58,
     -59,  -59,  -60,  -61,  -61,  -61,  -62,  -62,  -63,  -63,  -64,  -63,  -64,  -63,  -64,  -65,
     -64,  -64,  -65,  -64,  -65,  -64,  -64,  -65,  -64,  -63,  -64,  -64,  -63,  -63,  -62,  -62,
     -61,  -62,  -61,  -61,  -60,  -59,  -59,  -58,  -58,  -57,  -57,  -56,  -55,  -55,  -54,  -53,
     -53,  -52,  -51,  -51,  -50,  -49,  -48,  -48,  -47,  -46,  -45,  -45,  -44,  -43,  -42,  -41,
     -40,  -40,  -39,  -38,  -37,  -36,  -36,  -35,  -34,  -33,  -32,  -31,  -31,  -30,  -29,  -29,
     -28,  -27,  -26,  -26,  -25,  -24,  -23,  -23,  -22,  -21,  -20,  -20,  -19,  -19,  -18,  -18,
     -17,  -16,  -16,  -15,  -15,  -14,  -14,  -13,  -12,  -11,  -11,  -10,  -10,   -9,  -10,   -9,
      -8,   -9,   -8,   -7,   -8,   -7,   -7,   -6,   -5,   -6,   -5,   -4,   -5,   -4,   -4,   -3,
      -4,   -3,   -3,   -2,   -3,   -2,   -1,   -2,   -1,   -2,   -1,   -1,    0,   -1,    0,    0,
       1,    0,    0,    1,    2,    1,    2,    2,    1,    2,    3,    2,    2,    3,    2,    3,
       3,    4,    3,    4,    3,    4,    3,    4,    4,    4,    4,    3,    4,    4,    4,    4,
       4,    3,    4,    3,    4,    3,    4,    3,    4,    4,    3,    4,    3,    4,    3,    3,
       3,    2,    3,    3,    2,    3,    2,    1,    2,    1,    2,    2,    1,    2,    1,    0,
       1,    0,    1,    0,    1,    0,   -1,    0,    0,   -1,    0,   -1,    0,    0,   -1,    0,
      -1,    0,   -1,   -2,   -1,   -2,   -1,   -2,   -1,    0,   -1,    0,   -1,    0,   -1,    0,
      -1,   -1,    0,   -1,    0,   -1,    0,    0,    0,    1,    1,    0,    1,    0,    1,    0,
       1,    0,    1,    0,    1,    1,    0,    1,    0,    1,    0,    1,    0,    1,    1,    2,
       1,    2,    1,    2,    1,    0,    1,    0,    1,    0,    1,    0,    1,    0,   -1,    0,
       0,   -1,    0,   -1,    0,   -1,   -1,   -2,   -1,   -2,   -2,   -3,   -2,   -3,   -4,   -3,
      -4,   -4,   -5,   -6,   -5,   -6,   -5,   -6,   -7,   -6,   -6,   -7,   -6,   -7,   -8,   -8,
      -7,   -8,   -7,   -8,   -8,   -9,   -8,   -9,   -8,   -9,   -9,  -10,   -9,  -10,   -9,  -10,
      -9,  -10,   -9,   -9,   -9,   -9,   -9,   -9,   -9,   -9,  -10,   -9,  -10,   -9,  -10,   -9,
     -10,   -9,   -9,   -8,   -8,   -9,   -8,   -7,   -8,   -7,   -7,   -6,   -7,   -6,   -5,   -6,
      -5,   -5,   -4,   -4,   -4,   -3,   -2,   -3,   -2,   -1,   -2,   -1,   -1,    0,   -1,    0,
       1,    1,    1,    2,    1,    2,    2,    3,    2,    2,    3,    3,    4,    4,    5,    4,
       5,    6,    6,    5,    6,    7,    6,    7,    6,    7,    8,    7,    8,    8,    7,    8,
       8,    9,    8,    9,    8,    9,    9,    8,    9,    8,    7,    8,    7,    8,    7,    6,
       7,    7,    6,    6,    5,    5,    4,    3,    4,    3,    2,    2,    1,    1,    0,    0,
      -1,   -1,   -2,   -2,   -3,   -3,   -4,   -4,   -5,   -6,   -7,   -7,   -8,   -9,  -10,  -10,
     -11,  -12,  -13,  -14,  -14,  -15,  -16,  -17,  -17,  -18,  -19,  -20,  -20,  -21,  -22,  -23,
     -24,  -24,  -25,  -26,  -27,  -28,  -29,  -29,  -30,  -31,  -32,  -32,  -33,  -34,  -35,  -36,
     -36,  -37,  -38,  -39,  -40,  -41,  -41,  -42,  -43,  -44,  -44,  -45,  -45,  -46,  -47,  -47,
     -48,  -49,  -50,  -50,  -51,  -51,  -52,  -53,  -54,  -54,  -55,  -55,  -56,  -56,  -57,  -57,
     -58,  -58,  -59,  -58,  -59,  -60,  -59,  -60,  -61,  -60,  -61,  -62,  -61,  -61,  -62,  -63,
     -62,  -63,  -63,  -62,  -63,  -64,  -63,  -63,  -64,  -63,  -64,  -63,  -64,  -63,  -63,  -62,
     -63,  -63,  -62,  -61,  -61,  -62,  -61,  -60,  -60,  -60,  -59,  -58,  -57,  -57,  -56,  -56,
     -55,  -55,  -54,  -54,  -53,  -53,  -52,  -51,  -51,  -50,  -49,  -48,  -47,  -47,  -45,  -45,
     -43,  -43,  -42,  -41,  -40,  -39,  -38,  -36,  -35,  -34,  -33,  -32,  -31,  -29,  -28,  -27,
     -25,  -24,  -23,  -22,  -20,  -19,  -17,  -16,  -14,  -12,  -10,   -9,   -7,   -6,   -5,   -3,
      -2,    0,    2,    4,    5,    7,    8,   10,   12,   14,   15,   17,   19,   20,   22,   23,
      25,   27,   29,   30,   32,   33,   35,   36,   38,   39,   40,   42,   43,   45,   46,   48,
      49,   51,   52,   54,   55,   55,   57,   59,   59,   60,   61,   62,   63,   64,   65,   66,
      67,   68,   68,   69,   70,   71,   71,   72,   72,   73,   72,   73,   74,   73,   74,   73,
      74,   73,   74,   73,   72,   73,   73,   72,   71,   71,   70,   69,   69,   68,   67,   66,
      66,   65,   64,   63,   62,   61,   60,   59,   58,   56,   55,   54,   53,   51,   50,   48,
      47,   46,   44,   43,   41,   40,   37,   36,   33,   32,   31,   30,   29,   26,   24,   23,
      22,   20,   18,   16,   15,   13,   12,   10,    9,    7,    5,    3,    2,    1,   -1,   -2,
      -4,   -5,   -7,   -9,  -10,  -11,  -13,  -14,  -16,  -17,  -19,  -20,  -21,  -23,  -24,  -25,
     -26,  -28,  -29,  -31,  -32,  -32,  -34,  -35,  -36,  -37,  -38,  -40,  -40,  -41,  -42,  -43,
     -45,  -45,  -46,  -47,  -48,  -49,  -49,  -50,  -51,  -51,  -52,  -53,  -54,  -54,  -55,  -56,
     -57,  -57,  -58,  -58,  -59,  -59,  -60,  -60,  -61,  -61,  -62,  -62,  -62,  -63,  -62,  -63,
     -64,  -63,  -63,  -64,  -63,  -63,  -64,  -63,  -64,  -65,  -64,  -63,  -64,  -64,  -63,  -64,
     -63,  -62,  -63,  -62,  -61,  -61,  -60,  -61,  -60,  -60,  -59,  -59,  -58,  -58,  -57,  -56,
     -56,  -55,  -54,  -54,  -53,  -53,  -52,  -51,  -51,  -50,  -50,  -48,  -48,  -47,  -47,  -45,
     -46,  -42,  -30,  -39,  -43,  -40,  -41,  -39,  -39,  -38,  -37,  -36,  -36,  -35,  -33,  -34,
     -32,  -32,  -31,  -30,  -30,  -28,  -30,  -22,  -20,  -27,  -24,  -24,  -24,  -23,  -23,  -22,
     -21,  -20,  -20,  -19,  -19,  -18,  -17,  -17,  -16,  -15,  -14,  -14,  -13,  -13,  -12,  -12,
     -12,  -11,  -10,  -11,  -10,   -9,   -9,   -8,   -9,   -8,   -7,   -7,   -6,   -7,   -6,   -5,
      -5,   -4,   -5,   -4,   -4,   -3,   -4,   -3,   -2,   -3,   -2,   -2,   -1,   -2,   -1,    0,
      -1,    0,    0,    1,    0,    1,    1,    2,    1,    2,    2,    3,    3,    2,    3,    4,
       3,    4,    3,    4,    5,    4,    5,    4,    5,    4,    5,    4,    5,    5,    6,    5,
       6,    5,    6,    5,    6,    6,    5,    6,    5,    6,    5,    5,    6,    5,    6,    5,
       4,    5,    4,    5,    5,    5,    4,    5,    4,    3,    4,    3,    4,    3,    2,    2,
       3,    2,    3,    2,    3,    2,    2,    1,    2,    1,    2,    2,    1,    2,    1,    2,
       1,    1,    0,    1,    0,    1,    0,    1,    0,    1,    1,    1,    1,    0,    1,    1,
       1,    1,    1,    1,    1,    1,    1,    0,    1,    0,    1,    0,    1,    1,    0,    1,
       0,    1,    0,    1,    2,    2,    1,    2,    1,    2,    1,    1,    2,    1,    0,    0,
       1,    1,    1,    2,    1,    0,    1,    0,    1,    0,    1,    1,    0,    1,    0,   -1,
       0,   -1,    0,   -1,    0,   -1,   -2,   -1,   -2,   -1,   -2,   -3,   -2,   -3,   -3,   -3,
      -4,   -5,   -4,   -4,   -5,   -6,   -5,   -6,   -7,   -7,   -6,   -7,   -8,   -7,   -7,   -7,
      -8,   -7,   -8,   -9,   -8,   -9,   -8,   -9,   -8,   -9,  -10,   -9,  -10,   -9,  -10,   -9,
     -10,   -9,  -10,   -9,  -10,  -10,  -10,  -11,  -10,  -10,  -11,  -10,  -11,  -11,  -10,  -11,
     -10,   -9,  -10,  -10,   -9,  -10,   -9,  -10,   -9,   -9,   -8,   -9,   -8,   -7,   -8,   -7,
      -6,   -7,   -7,   -6,   -5,   -6,   -6,   -5,   -4,   -5,   -4,   -3,   -4,   -3,   -3,   -2,
      -3,   -2,   -1,   -2,   -1,   -2,   -1,   -1,    0,   -1,    0,    0,    1,    1,    2,    1,
       2,    3,    2,    2,    3,    3,    4,    3,    4,    5,    4,    5,    4,    5,    6,    5,
       6,    5,    5,    6,    5,    6,    5,    6,    6,    6,    5,    6,    5,    6,    5,    6,
       5,    5,    4,    5,    4,    3,    4,    3,    3,    3,    2,    1,    2,    1,    0,    1,
       0,    0,   -1,   -2,   -1,   -2,   -3,   -3,   -4,   -4,   -5,   -5,   -6,   -6,   -7,   -8,
      -8,   -9,  -10,  -10,  -11,  -12,  -12,  -13,  -14,  -15,  -15,  -16,  -16,  -17,  -18,  -18,
     -19,  -20,  -21,  -21,  -22,  -23,  -24,  -24,  -25,  -26,  -27,  -27,  -28,  -29,  -29,  -30,
     -31,  -32,  -33,  -34,  -34,  -35,  -36,  -37,  -37,  -38,  -39,  -39,  -40,  -41,  -42,  -42,
     -43,  -44,  -44,  -45,  -46,  -46,  -47,  -48,  -48,  -49,  -50,  -51,  -51,  -52,  -52,  -53,
     -53,  -54,  -54,  -55,  -55,  -56,  -56,  -57,  -58,  -57,  -58,  -59,  -59,  -60,  -59,  -60,
     -61,  -60,  -61,  -62,  -61,  -62,  -61,  -62,  -62,  -63,  -62,  -63,  -62,  -63,  -62,  -63,
     -62,  -63,  -62,  -63,  -62,  -61,  -62,  -61,  -62,  -61,  -60,  -61,  -60,  -59,  -59,  -58,
     -57,  -56,  -57,  -56,  -56,  -55,  -55,  -54,  -53,  -52,  -52,  -51,  -50,  -49,  -49,  -48,
     -47,  -47,  -46,  -45,  -44,  -43,  -42,  -40,  -39,  -39,  -38,  -36,  -35,  -34,  -33,  -32,
     -31,  -30,  -28,  -27,  -25,  -24,  -22,  -21,  -20,  -19,  -17,  -15,  -14,  -12,  -11,   -9,
      -8,   -6,   -5,   -3,   -2,    0,    2,    4,    5,    7,    8,   10,   12,   13,   15,   16,
      18,   20,   22,   23,   25,   26,   28,   29,   30,   32,   33,   35,   36,   38,   39,   41,
      42,   44,   45,   47,   48,   50,   50,   51,   53,   54,   55,   56,   58,   59,   59,   60,
      61,   62,   63,   64,   65,   65,   66,   67,   68,   68,   69,   69,   70,   70,   71,   70,
      71,   72,   71,   72,   72,   71,   72,   71,   71,   70,   71,   70,   70,   69,   68,   68,
      67,   67,   66,   65,   64,   63,   62,   62,   61,   59,   58,   57,   56,   55,   54,   52,
      51,   49,   49,   48,   46,   45,   43,   42,   40,   39,   36,   35,   33,   31,   29,   29,
      28,   26,   25,   22,   21,   19,   18,   16,   14,   12,   11,    9,    8,    7,    5,    4,
       1,    0,   -2,   -3,   -5,   -6,   -8,   -9,  -11,  -12,  -13,  -14,  -15,  -17,  -18,  -20,
     -21,  -23,  -24,  -25,  -26,  -28,  -29,  -29,  -31,  -33,  -33,  -34,  -35,  -36,  -37,  -38,
     -39,  -40,  -41,  -42,  -43,  -43,  -44,  -46,  -46,  -47,  -48,  -48,  -49,  -50,  -51,  -51,
     -52,  -52,  -53,  -54,  -55,  -55,  -56,  -56,  -57,  -57,  -58,  -58,  -59,  -58,  -59,  -59,
     -60,  -61,  -60,  -61,  -60,  -61,  -62,  -61,  -62,  -61,  -61,  -62,  -61,  -62,  -61,  -62,
     -61,  -61,  -60,  -61,  -60,  -61,  -60,  -59,  -60,  -59,  -58,  -58,  -58,  -57,  -57,  -56,
     -56,  -55,  -55,  -54,  -54,  -53,  -53,  -52,  -52,  -51,  -50,  -50,  -49,  -49,  -48,  -47
};


float freq(int phase) {
  return 1.0/(phase * (1.0 / SAMPLE_RATE));
}

unsigned int error_squared(signed char a, signed char b) {
  return (unsigned int) ((signed int) a - (signed int) b) * ((signed int) a - (signed int) b);
}

unsigned int window_error(signed char *data, int offset) {
  unsigned int sum = 0;
  for (int i = 0; i < WINDOW; i++) {
    sum += error_squared(data[i], data[i+offset]);
  }
  return sum;
}

unsigned int differences[WINDOW];

int phase(signed char *data) {
  // NOTE: for i = 0 difference should always be 0, so start with 1 in real code 
  for (int i = 0; i < WINDOW; i++) {
    differences[i] = window_error(data, i);
  }

  unsigned int min = INT_MAX;
  int min_i = 0;
  for (int i = 32; i < WINDOW; i++) {
    if (differences[i] < min) {
      min = differences[i];
      min_i = i;
      //      printf("New min with %i at %i (freq: %f)\n", min, min_i, freq(min_i));
    }
  }
  return min_i;
}

int main() {
  /* printf("Sine phase: %i freq: %f\n", phase(sine), freq(phase(sine))); */
  /* printf("Voice phase: %i freq: %f\n", phase(voice), freq(phase(voice))); */
  /* printf("Voice2 phase: %i freq: %f\n", phase(voice2), freq(phase(voice2))); */
  //printf("%i", error_squared(2, -3));
  //printf("Bass phase: %i freq: %f\n", phase(bass), freq(phase(bass)));
  //printf("%f", freq(32));
  int sum = 0;
  for (int i = 0; i < 1000; i++) {
    sum += phase(bass);
  }
  printf("%i", sum);
}
