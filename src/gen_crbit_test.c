#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "lfsr.h"
#include "argument.h"
#include "register.h"
#include "instruction.h"

const char *instructions[] = {
  "crand",
  "crandc",
  "creqv",
  "crnand",
  "crnor",
  "cror",
  "crorc",
  "crxor",
  0
};

uint32_t cr_values[] = {
  0xffffffff,
  0xaaaaaaaa,
  0x55555555,
  0
};

int main() {
  for (int i = 0; instructions[i]; i++) {
    for (int j = 0; j < 4; j++) {
      fillreg("0", cr_values[j]);
      printf("\tmtcrf 255,0\n");
      printf("\t%s\t31,0,1\n", instructions[i]);
      printf("\tmfcr 3\n");
      printf("\tbl\tprint_hex\n");
      printf("\n");
    }
  }
  return 0;
}
