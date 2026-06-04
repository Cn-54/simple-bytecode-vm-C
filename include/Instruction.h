#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "Opcode.h"

typedef struct {
    Opcode op;
    int A;
    int B;
    int C;
} INS;
    

#endif