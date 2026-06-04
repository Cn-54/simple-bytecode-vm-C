#ifndef OPCODE_H_
#define OPCODE_H_

typedef enum {
    HALT  = -1,
    NOP   =  0,
    SET   =  1,
    LOAD  =  2,
    STORE =  3,
    ADD   =  4,
    SUB   =  5,
    MUL   =  6,
    DIV   =  7,
    MOD   =  8,
    POW   =  9,
    JMP   = 10,
    JGT   = 11,
    JLT   = 12,
    JEQ   = 13,
    OUT   = 14,
    PUT   = 15,
    INP   = 16,
    ONL   = 17,
    PUTI  = 18,
    OUTI  = 19,
    INPI  = 20,
} Opcode;
    

#endif