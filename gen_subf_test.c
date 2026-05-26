#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NARGS 2

enum Argument {
  Nothing,
  Register,
  Immediate
};

struct Instruction {
  const char *name;
  enum Argument A, B;
};

struct Instruction to_generate[] = {
  { "add", Register, Register },
  { "add.", Register, Register },
  { "addi", Register, Immediate },
  { "addc", Register, Register },
  { "addc.", Register, Register },
  { "addic", Register, Immediate },
  { "addic.", Register, Immediate },
  { "addco", Register, Register },
  { "addco.", Register, Register },
  { "adde", Register, Register },
  { "adde.", Register, Register },
  { "addeo", Register, Register },
  { "addeo.", Register, Register },
  { "addme", Register, Nothing },
  { "addme.", Register, Nothing },
  { "addmeo", Register, Nothing },
  { "addmeo.", Register, Nothing },
  { "addze", Register, Nothing },
  { "addze.", Register, Nothing },
  { "addzeo", Register, Nothing },
  { "addzeo.", Register, Nothing },
  { "addis", Register, Immediate },
  { "addis.", Register, Immediate },
  { "subf", Register, Register },
  { "subf.", Register, Register },
  { "subfo", Register, Register },
  { "subfo.", Register, Register },
  { "subfc", Register, Register },
  { "subfc.", Register, Register },
  { "subfco", Register, Register },
  { "subfco.", Register, Register },
  { "subfe", Register, Register },
  { "subfe.", Register, Register },
  { "subfeo", Register, Register },
  { "subfeo.", Register, Register },
  { "subfme", Register, Nothing },
  { "subfme.", Register, Nothing },
  { "subfmeo", Register, Nothing },
  { "subfmeo.", Register, Nothing },
  { "subfze", Register, Nothing },
  { "subfze.", Register, Nothing },
  { "subfzeo", Register, Nothing },
  { "subfzeo.", Register, Nothing },
  { "subfic", Register, Immediate },
};

int lfsr_step(int *lfsr) {
  int top = (*lfsr >> 15) & 1;
  *lfsr = ((*lfsr << 1) | top) ^ 0x2347;
  return *lfsr;
}

uint32_t int_lfsr(int *lfsr) {
  return lfsr_step(lfsr) << 16 | lfsr_step(lfsr);
}

void fillreg(const char *r, uint32_t value) {
  printf("\tlis 0,%d\n", (value >> 16) & 0xffff);
  printf("\tori %s,0,%d\n", r, value & 0xffff);
}

enum Argument nth_argument(struct Instruction *i, int n) {
  switch(n) {
  case 0:
    return i->A;
  default:
    return i->B;
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "usage: gen_subf_test [seed] [n]\n");
    return 1;
  }

  int seed = atoi(argv[1]);
  int cycles = atoi(argv[2]);

  // Load up the registers with 
  for (int i = 0; i < cycles; i++) {
    // Fill the registers with useful values.
    fillreg("0", int_lfsr(&seed));
    printf("\tmtcrf 255,0\n");

    fillreg("0", int_lfsr(&seed) << 24);
    printf("\tmtspr 1, 0\n");

    uint32_t random_instr = int_lfsr(&seed) % (sizeof(to_generate) / sizeof(to_generate[0]));
    struct Instruction *i = &to_generate[random_instr];

    // Emit the actual instruction.
    for (int a = 0; a < NARGS; a++) {
      enum Argument arg = nth_argument(i, a);
      if (arg == Register) {
	char regname[20];
	sprintf(regname, "%d", a+3);
	fillreg(regname, int_lfsr(&seed));
      }
    }
    printf("\t%s\t3", i->name);
    for (int a = 0; a < NARGS; a++) {
      enum Argument arg = nth_argument(i, a);
      if (arg == Nothing) {
	continue;
      }
      if (arg == Register) {
	printf(",%d", a+3);
      } else {
	printf(",%d", (int_lfsr(&seed) & 0xffff) - 32768);
      }
    }
    printf("\n");
    
    // load r3 with each thing we want to print
    // ensure that cr and xer are saved in callee-save registers so
    // we still have them after printing.
    printf("\tmfspr 30,1\n");
    printf("\tmfcr 31\n");
    printf("\tbl print_hex\n");
    printf("\tmr 3,31\n");
    printf("\tbl print_hex\n");
    printf("\tmr 3,30\n");
    printf("\tbl print_hex\n");
    
    printf("\n\n");
  }
}
