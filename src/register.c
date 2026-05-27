#include <stdint.h>
#include <stdio.h>
#include "register.h"

void fillreg(const char *r, uint32_t value) {
  printf("\tlis 0,%d\n", (value >> 16) & 0xffff);
  printf("\tori %s,0,%d\n", r, value & 0xffff);
}

