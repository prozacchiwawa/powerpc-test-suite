#include <stdarg.h>
#include "lfsr.h"

int lfsr_step(int *lfsr) {
  int top = (*lfsr >> 15) & 1;
  *lfsr = ((*lfsr << 1) | top) ^ 0x2347;
  return *lfsr;
}

uint32_t int_lfsr(int *lfsr) {
  return lfsr_step(lfsr) << 16 | lfsr_step(lfsr);
}
