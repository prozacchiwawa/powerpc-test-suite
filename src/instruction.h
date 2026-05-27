#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "argument.h"

#define NARGS 3

struct Instruction {
  const char *name;
  enum Argument A, B, C;
};

enum Argument nth_argument(struct Instruction *i, int n);

#endif//_INSTRUCTION_H_
