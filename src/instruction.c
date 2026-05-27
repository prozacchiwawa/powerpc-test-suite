#include "instruction.h"

enum Argument nth_argument(struct Instruction *i, int n) {
  switch(n) {
  case 0:
    return i->A;
  case 1:
    return i->B;
  default:
    return i->C;
  }
}

