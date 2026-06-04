#ifndef VM_H_
#define VM_H_

#include "Instruction.h"
#include "memory.h"


typedef struct {
    MEM mem;
    INS current;
    int pc;
    int halted;
} VM;

VM *createVM();
void runVM(VM *vm,const char *program);
void destroyVM(VM *vm);

#endif