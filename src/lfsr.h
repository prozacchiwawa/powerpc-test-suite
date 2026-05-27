#ifndef _LFSR_H_
#define _LFSR_H_

#include <stdint.h>

uint32_t int_lfsr(int *lfsr);
int lfsr_step(int *lfsr);

#endif//_LFSR_H_
