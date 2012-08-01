#include <limits.h>
#include <stdio.h>

#define SAMPLE_RATE 32768

// about 31 Hz (C1) (at 32k)
#define PHASE_MAX 1041
// about C2
#define PHASE_MIN 512

#define ERROR_T_MAX 4294967295

#define WINDOW (PHASE_MAX - PHASE_MIN)

typedef   signed char  sample_t;
typedef unsigned int   error_t;
typedef unsigned short phase_t;

sample_t bass[2048] =
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

sample_t voice[2400] =
{
      -1,   -2,   -2,   -3,   -2,   -3,   -4,   -3,   -4,   -5,   -4,   -5,   -6,   -5,   -6,   -5,
      -6,   -5,   -6,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -4,   -3,   -4,   -3,   -4,   -3,
      -4,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,   -3,   -3,   -4,   -3,
      -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,   -5,   -4,   -5,
      -4,   -5,   -4,   -5,   -4,   -4,   -4,   -4,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,
      -5,   -4,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,
      -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -2,   -3,   -2,
      -3,   -2,   -3,   -2,   -3,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -2,   -1,   -2,
      -1,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,    0,   -1,    0,   -1,    0,    0,   -1,
       0,   -1,    0,   -1,   -2,   -2,   -1,   -2,   -3,   -2,   -3,   -4,   -4,   -4,   -5,   -4,
      -5,   -5,   -6,   -5,   -6,   -5,   -5,   -6,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -3,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
      -3,   -3,   -3,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,
      -4,   -3,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,
      -4,   -5,   -4,   -5,   -4,   -5,   -4,   -3,   -4,   -4,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -2,   -3,   -2,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,
      -2,   -2,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -1,    0,
      -1,    0,   -1,   -1,    0,   -1,   -1,    0,   -1,   -2,   -1,   -1,   -2,   -3,   -2,   -3,
      -3,   -4,   -5,   -5,   -4,   -5,   -5,   -6,   -5,   -6,   -5,   -5,   -6,   -5,   -4,   -5,
      -5,   -4,   -5,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,
      -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,
      -3,   -4,   -3,   -4,   -3,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,
      -4,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -3,   -4,   -3,   -4,
      -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,
      -3,   -4,   -3,   -4,   -3,   -2,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -2,   -2,   -3,
      -2,   -3,   -2,   -1,   -2,   -1,   -2,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -2,   -1,
      -2,   -1,    0,   -1,    0,    0,   -1,    0,   -1,    0,   -1,   -1,   -2,   -1,   -1,   -2,
      -3,   -2,   -3,   -4,   -3,   -4,   -5,   -4,   -4,   -5,   -6,   -5,   -6,   -5,   -6,   -5,
      -6,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -4,
      -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -5,   -4,   -5,   -4,   -4,
      -5,   -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -3,   -3,   -3,   -4,
      -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,   -3,   -2,   -2,   -3,   -2,
      -2,   -3,   -2,   -3,   -2,   -2,   -3,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -2,
      -1,   -2,   -1,   -2,   -1,   -1,    0,   -1,    0,   -1,    0,   -1,    0,   -1,    0,   -1,
      -1,   -2,   -1,   -2,   -2,   -2,   -3,   -4,   -3,   -4,   -5,   -4,   -5,   -5,   -6,   -5,
      -6,   -5,   -6,   -5,   -6,   -5,   -4,   -5,   -4,   -5,   -5,   -4,   -3,   -4,   -3,   -4,
      -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
      -4,   -3,   -4,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,   -5,
      -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -5,
      -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,
      -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,   -3,   -4,   -3,   -2,   -3,   -2,
      -3,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,
      -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,    0,   -1,    0,   -1,    0,   -1,    0,
      -1,    0,   -1,   -2,   -2,   -1,   -2,   -3,   -2,   -3,   -4,   -3,   -4,   -5,   -4,   -4,
      -5,   -6,   -5,   -6,   -5,   -6,   -5,   -6,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -3,
      -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,
      -3,   -3,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,
      -3,   -4,   -5,   -4,   -5,   -4,   -5,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,
      -4,   -5,   -4,   -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,
      -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,
      -2,   -2,   -3,   -2,   -3,   -2,   -2,   -3,   -2,   -3,   -2,   -1,   -2,   -2,   -1,   -2,
      -1,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -2,   -1,    0,   -1,    0,   -1,
      -1,    0,    0,   -1,    0,   -1,   -2,   -2,   -1,   -2,   -3,   -2,   -3,   -4,   -4,   -5,
      -5,   -4,   -5,   -6,   -5,   -6,   -5,   -6,   -5,   -5,   -6,   -5,   -4,   -5,   -5,   -4,
      -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -3,
      -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,
      -3,   -4,   -3,   -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,
      -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,
      -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,
      -4,   -3,   -2,   -3,   -2,   -3,   -2,   -2,   -3,   -2,   -3,   -2,   -1,   -2,   -1,   -2,
      -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,    0,   -1,    0,
      -1,    0,   -1,   -1,    0,   -1,    0,   -1,   -2,   -2,   -1,   -2,   -3,   -2,   -3,   -4,
      -3,   -4,   -5,   -4,   -5,   -6,   -5,   -6,   -5,   -5,   -6,   -5,   -6,   -5,   -4,   -5,
      -4,   -4,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,   -3,   -4,   -3,
      -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,
      -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,
      -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -3,   -4,   -3,   -4,   -3,
      -4,   -3,   -3,   -3,   -3,   -4,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -3,   -4,
      -3,   -4,   -3,   -4,   -3,   -2,   -3,   -3,   -2,   -3,   -2,   -3,   -2,   -2,   -1,   -2,
      -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,    0,
      -1,   -1,    0,   -1,    0,   -1,    0,    0,   -1,   -2,   -1,   -2,   -2,   -3,   -2,   -3,
      -4,   -3,   -4,   -5,   -4,   -4,   -5,   -6,   -5,   -6,   -5,   -6,   -5,   -6,   -5,   -4,
      -5,   -4,   -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,   -3,   -3,   -2,
      -3,   -2,   -2,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -4,   -3,   -4,   -4,   -3,   -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,
      -4,   -5,   -4,   -5,   -4,   -5,   -4,   -2,   -4,   -5,   -4,   -4,   -3,   -4,   -3,   -4,
      -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -4,   -4,   -3,   -4,   -3,   -2,   -3,   -2,   -2,   -3,   -2,   -2,   -3,   -2,   -1,
      -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,   -2,   -1,
      -1,    0,   -1,    0,   -1,    0,    0,   -1,    0,   -1,   -2,   -1,   -1,   -2,   -3,   -2,
      -2,   -3,   -3,   -4,   -5,   -4,   -4,   -5,   -6,   -5,   -6,   -5,   -6,   -5,   -6,   -5,
      -5,   -4,   -4,   -5,   -4,   -3,   -4,   -4,   -3,   -4,   -3,   -4,   -3,   -2,   -3,   -2,
      -2,   -3,   -2,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,
      -4,   -3,   -4,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -5,   -4,   -4,   -5,   -4,   -5,
      -4,   -5,   -4,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -3,   -3,   -4,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,   -2,   -3,   -2,   -3,   -3,   -2,   -3,   -2,
      -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -1,   -2,   -2,   -1,
      -2,   -1,    0,   -1,    0,   -1,    0,    0,   -1,    0,   -1,   -2,   -1,   -1,   -2,   -2,
      -3,   -2,   -3,   -4,   -3,   -4,   -5,   -4,   -4,   -5,   -6,   -5,   -6,   -6,   -5,   -6,
      -5,   -4,   -4,   -5,   -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,   -3,
      -3,   -2,   -3,   -2,   -3,   -2,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -5,   -4,   -5,   -4,   -4,
      -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -3,   -4,
      -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -3,   -4,   -3,
      -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,   -3,   -2,   -3,   -2,   -3,   -2,   -2,   -3,
      -2,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,   -2,   -1,   -2,   -1,   -2,   -1,
      -2,   -1,   -1,    0,   -1,    0,   -1,    0,   -1,    0,   -1,   -1,   -2,   -1,   -1,   -2,
      -3,   -3,   -2,   -3,   -3,   -4,   -4,   -5,   -4,   -5,   -5,   -6,   -5,   -6,   -5,   -5,
      -6,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -3,   -4,   -4,   -3,   -4,   -3,   -2,   -2,
      -3,   -2,   -3,   -2,   -3,   -3,   -2,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,
      -3,   -4,   -3,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -5,   -5,   -4,   -5,
      -4,   -5,   -4,   -5,   -4,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,   -4,   -3,   -4,   -3,
      -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -2,
      -3,   -2,   -1,   -2,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -2,
      -1,   -2,   -1,    0,    0,   -1,    0,    0,   -1,    0,   -1,   -1,   -2,   -1,   -2,   -1,
      -2,   -3,   -2,   -3,   -4,   -3,   -4,   -5,   -5,   -4,   -5,   -6,   -6,   -5,   -6,   -5,
      -6,   -6,   -5,   -4,   -5,   -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,
      -3,   -2,   -2,   -3,   -2,   -3,   -2,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,
      -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -4,   -5,   -4,   -5,
      -4,   -5,   -4,   -5,   -4,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,
      -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -2,   -3,   -2,   -3,   -2,   -3,
      -2,   -3,   -2,   -1,   -2,   -1,   -2,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -1,
      -2,   -1,   -2,   -1,    0,   -1,    0,   -1,    0,   -1,    0,   -1,   -2,   -1,   -1,   -2,
      -1,   -2,   -3,   -3,   -4,   -3,   -4,   -5,   -5,   -4,   -5,   -6,   -5,   -6,   -5,   -6,
      -5,   -6,   -5,   -5,   -5,   -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,
      -3,   -2,   -2,   -3,   -2,   -3,   -2,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -3,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -5,   -4,   -5,
      -5,   -4,   -5,   -4,   -5,   -4,   -4,   -4,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,
      -3,   -4,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,
      -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -2,   -3,   -2,   -3,   -2,   -3,
      -2,   -2,   -3,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -2,   -1,   -2,   -1,   -1,   -2,
      -1,   -2,   -1,   -2,   -1,   -1,    0,   -1,    0,   -1,   -1,    0,   -1,   -2,   -1,   -2,
      -1,   -2,   -3,   -2,   -3,   -4,   -3,   -4,   -5,   -4,   -4,   -5,   -6,   -5,   -6,   -5,
      -6,   -5,   -6,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -3,   -4,   -3,   -4,   -4,   -3,
      -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -3,   -2,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -5,   -4,
      -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -5,
      -4,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,
      -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -2,   -3,   -2,   -2,
      -3,   -2,   -3,   -2,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -1,   -1,
      -2,   -1,   -2,   -1,   -2,   -1,    0,   -1,    0,   -1,    0,   -1,    0,   -1,   -2,   -2,
      -1,   -2,   -1,   -2,   -3,   -2,   -3,   -3,   -4,   -5,   -4,   -4,   -5,   -6,   -5,   -6,
      -5,   -6,   -5,   -6,   -5,   -5,   -4,   -4,   -5,   -4,   -3,   -4,   -3,   -4,   -3,   -4,
      -3,   -2,   -3,   -2,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -4,   -3,   -4,   -4,
      -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,
      -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,   -5,   -4,   -4,   -5,   -4,   -5,   -4,
      -5,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -3,   -3,   -3,
      -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -2,   -3,   -2,
      -3,   -2,   -3,   -2,   -3,   -2,   -2,   -1,   -2,   -1,   -2,   -1,   -2,   -1,   -1,   -2,
      -1,   -1,   -2,   -1,   -2,   -1,   -2,   -1,    0,   -1,    0,    0,    0,   -1,    0,   -1,
      -1,   -2,   -1,   -2,   -1,   -2,   -3,   -2,   -3,   -4,   -4,   -5,   -4,   -4,   -5,   -6,
      -5,   -6,   -5,   -6,   -5,   -6,   -5,   -4,   -5,   -4,   -5,   -4,   -3,   -4,   -3,   -3,
      -4,   -3,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -3,   -4,   -3,
      -4,   -3,   -4,   -3,   -4,   -3,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4,   -3,   -4
};


typedef struct {
  phase_t phase;
  error_t error;
  phase_t iteration;
} continuation;

continuation heap[WINDOW+1];

/* Initialise the heap structure.
 * NOTE: Could inline first error calculation iteration, then restore heap property */
void heap_init() {
  for (int i = 0; i+PHASE_MIN < PHASE_MAX; i++) {
    heap[i].phase = i+PHASE_MIN;
    heap[i].error = 0;
    heap[i].iteration = 0;
  }
}

int heap_in_bounds(phase_t index) {
  return index > 0 && index < WINDOW;
}

void heap_swap(phase_t a, phase_t b) {
  continuation tmp = heap[a];
  heap[a] = heap[b];
  heap[b] = tmp;
}

phase_t heap_left(phase_t i) {
  return i << 1;
}

phase_t heap_right(phase_t i) {
  return (i << 1)+1;
}

void heap_heapify(phase_t i) {
  phase_t l = heap_left(i);
  phase_t r = heap_right(i);
  phase_t smallest;
  if (heap_in_bounds(l) && heap[l].error < heap[i].error) {
    smallest = l;
  } else {
    smallest = i;
  }
  if (heap_in_bounds(r) && heap[r].error < heap[smallest].error) {
    smallest = r;
  }
  if (smallest != i) {
    heap_swap(i, smallest);
    heap_heapify(smallest);
  }
}

float freq(int phase) {
  return 1.0/(phase * (1.0 / SAMPLE_RATE));
}

unsigned int error_squared(signed char a, signed char b) {
  return (unsigned int) ((signed int) a - (signed int) b) * ((signed int) a - (signed int) b);
}

void print_heap_elem(int i) {
  printf("Phase: %i\tError: %i\tIteration: %i\n", heap[i].phase, heap[i].error, heap[i].iteration);
}

phase_t phase(sample_t *data) {
  heap_init();
  while (heap[1].iteration < WINDOW) {
    /* 5 steps in window
       This might do unneccessary work if the initial error is large enough
       but saves heap management overhead in case the error is growing very evenly accross offsets */ 
    /* TODO:
       - Find a reasonable value for "unrolling" accross samples (loudness, noise, frequency)
       - Be careful not to leave WINDOW (should be a divisor or needs extra checking (duff's device anyone?)
    */
    /*
    heap[1].error += error_squared(data[heap[1].iteration], data[heap[1].iteration + heap[1].phase]);
    heap[1].error += error_squared(data[heap[1].iteration+1], data[heap[1].iteration + heap[1].phase+1]);
    heap[1].error += error_squared(data[heap[1].iteration+2], data[heap[1].iteration + heap[1].phase+2]);
    heap[1].error += error_squared(data[heap[1].iteration+3], data[heap[1].iteration + heap[1].phase+3]);
    heap[1].error += error_squared(data[heap[1].iteration+4], data[heap[1].iteration + heap[1].phase+4]);
    heap[1].iteration += 5;
    */

    /* 25 steps in window */
    /* NOTE: same as above
    /*
    heap[1].error += error_squared(data[heap[1].iteration], data[heap[1].iteration + heap[1].phase]);
    heap[1].error += error_squared(data[heap[1].iteration+1], data[heap[1].iteration + heap[1].phase+1]);
    heap[1].error += error_squared(data[heap[1].iteration+2], data[heap[1].iteration + heap[1].phase+2]);
    heap[1].error += error_squared(data[heap[1].iteration+3], data[heap[1].iteration + heap[1].phase+3]);
    heap[1].error += error_squared(data[heap[1].iteration+4], data[heap[1].iteration + heap[1].phase+4]);
    heap[1].error += error_squared(data[heap[1].iteration+5], data[heap[1].iteration + heap[1].phase+5]);
    heap[1].error += error_squared(data[heap[1].iteration+6], data[heap[1].iteration + heap[1].phase+6]);
    heap[1].error += error_squared(data[heap[1].iteration+7], data[heap[1].iteration + heap[1].phase+7]);
    heap[1].error += error_squared(data[heap[1].iteration+8], data[heap[1].iteration + heap[1].phase+8]);
    heap[1].error += error_squared(data[heap[1].iteration+9], data[heap[1].iteration + heap[1].phase+9]);
    heap[1].error += error_squared(data[heap[1].iteration+10], data[heap[1].iteration + heap[1].phase+10]);
    heap[1].error += error_squared(data[heap[1].iteration+11], data[heap[1].iteration + heap[1].phase+11]);
    heap[1].error += error_squared(data[heap[1].iteration+12], data[heap[1].iteration + heap[1].phase+12]);
    heap[1].error += error_squared(data[heap[1].iteration+13], data[heap[1].iteration + heap[1].phase+13]);
    heap[1].error += error_squared(data[heap[1].iteration+14], data[heap[1].iteration + heap[1].phase+14]);
    heap[1].error += error_squared(data[heap[1].iteration+15], data[heap[1].iteration + heap[1].phase+15]);
    heap[1].error += error_squared(data[heap[1].iteration+16], data[heap[1].iteration + heap[1].phase+16]);
    heap[1].error += error_squared(data[heap[1].iteration+17], data[heap[1].iteration + heap[1].phase+17]);
    heap[1].error += error_squared(data[heap[1].iteration+18], data[heap[1].iteration + heap[1].phase+18]);
    heap[1].error += error_squared(data[heap[1].iteration+19], data[heap[1].iteration + heap[1].phase+19]);
    heap[1].error += error_squared(data[heap[1].iteration+20], data[heap[1].iteration + heap[1].phase+20]);
    heap[1].error += error_squared(data[heap[1].iteration+21], data[heap[1].iteration + heap[1].phase+21]);
    heap[1].error += error_squared(data[heap[1].iteration+22], data[heap[1].iteration + heap[1].phase+22]);
    heap[1].error += error_squared(data[heap[1].iteration+23], data[heap[1].iteration + heap[1].phase+23]);
    heap[1].error += error_squared(data[heap[1].iteration+24], data[heap[1].iteration + heap[1].phase+24]);
    heap[1].iteration += 25;
    */

    /* one step in window */
    heap[1].error += error_squared(data[heap[1].iteration], data[heap[1].iteration + heap[1].phase]);
    heap[1].iteration += 1;
    /* resort heap */
    heap_heapify(1);
  }
  //  for (int i = 1; i < WINDOW; i++) {
  //    printf("%i\n", heap[i].iteration);
  //  }
  return heap[1].phase;
}

int main() {
  int phase_sum = 0;
  for (int i = 0; i < 1000; i++) {
    phase_sum += phase(bass);
  }
  //printf("%i", phase_sum);
  
  //  printf("\n");
  //  printf("Bass phase: %i freq: %f\n", phase(bass), freq(phase(bass)));
  //  printf("Voice phase: %i freq: %f\n", phase(voice), freq(phase(voice)));
  //  phase(voice);
}
