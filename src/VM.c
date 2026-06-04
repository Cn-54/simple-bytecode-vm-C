#include "VM.h"
#include "Opcode.h"
#include <stdlib.h>
#include <stdio.h>

    
VM *createVM() {
    VM *vm = malloc(sizeof(VM));
    if (!vm) return NULL;
    vm->mem = (MEM){0};
    vm->halted = 0;
    vm->pc = 0;
    return vm;
}

static void fetchInstruction(VM *vm) {
    vm->current.op = (Opcode)vm->mem.Code[vm->pc];
    vm->current.A  = vm->mem.Code[vm->pc + 1];
    vm->current.B  = vm->mem.Code[vm->pc + 2];
    vm->current.C  = vm->mem.Code[vm->pc + 3];
    vm->pc += 4;
}

static void decodeExecute(VM *vm,INS ins){
    switch (ins.op) {
        case HALT:
            vm->halted = 1;
            break;
        case NOP:
            break;
        case SET:
            vm->mem.Data[ins.C] = ins.A;
            break;
        case LOAD:
            vm->mem.Data[ins.A] = vm->mem.Data[ins.C];
            break;
        case STORE:
            vm->mem.Data[ins.C] = vm->mem.Data[ins.A];
            break;
        case ADD:
            vm->mem.Data[ins.C] = vm->mem.Data[ins.A] + vm->mem.Data[ins.B];
            break;
        case SUB:
            vm->mem.Data[ins.C] = vm->mem.Data[ins.A] - vm->mem.Data[ins.B];
            break;
        case MUL:
            vm->mem.Data[ins.C] = vm->mem.Data[ins.A] * vm->mem.Data[ins.B];
            break;
        case DIV:
            vm->mem.Data[ins.C] = vm->mem.Data[ins.A] / vm->mem.Data[ins.B];
            break;
        case MOD:
            vm->mem.Data[ins.C] = vm->mem.Data[ins.A] % vm->mem.Data[ins.B];
            break;
        case POW: {
            int base = vm->mem.Data[ins.A];
            int exp  = vm->mem.Data[ins.B];
            int result = 1;
            for (int i = 0; i < exp; i++) result *= base;
            vm->mem.Data[ins.C] = result;
            break;
        }
        case JMP:
            vm->pc = ins.C * 4;
            break;
        case JGT:
            if (vm->mem.Data[ins.A] > vm->mem.Data[ins.B])
                vm->pc = ins.C * 4;
            break;
        case JLT:
            if (vm->mem.Data[ins.A] < vm->mem.Data[ins.B])
                vm->pc = ins.C * 4;
            break;
        case JEQ:
            if (vm->mem.Data[ins.A] == vm->mem.Data[ins.B])
                vm->pc = ins.C * 4;
            break;
        case OUT:
            printf("%d", vm->mem.Data[ins.A]);
            break;
        case PUT:
            printf("%c", vm->mem.Data[ins.A]);
            break;
        case INP:
            scanf("%d", &vm->mem.Data[ins.A]);
            break;
        case ONL:
            printf("\n");
            break;
        case PUTI:
            printf("%c", vm->mem.Data[vm->mem.Data[ins.A]]);
            break;
        case OUTI:
            printf("%d", vm->mem.Data[vm->mem.Data[ins.A]]);
            break;
        case INPI:
            scanf("%d", &vm->mem.Data[vm->mem.Data[ins.A]]);
            break;
        default:
            printf("unknown opcode: %d\n", ins.op);
            vm->halted = 1;
            break;
    }
}

void runVM(VM *vm,const char *program){
    vm->mem = loadMemory(program);
    while(!vm->halted){
        fetchInstruction(vm);
        decodeExecute(vm, vm->current);
    }
}

void destroyVM(VM *vm) {
    if (!vm) return;
    free(vm);
}