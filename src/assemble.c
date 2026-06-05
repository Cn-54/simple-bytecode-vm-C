#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Opcode.h"

typedef struct {
    char *words[4];   // opcode + A + B + C
    int count;
} Tokens;

typedef struct {
    const char *name;
    Opcode opcode;
} OpcodeEntry;

static const OpcodeEntry opcodeTable[] = {
    {"HALT", HALT},
    {"NOP",  NOP},
    {"SET",  SET},
    {"LOAD", LOAD},
    {"STORE", STORE},
    {"ADD",  ADD},
    {"SUB",  SUB},
    {"MUL",  MUL},
    {"DIV",  DIV},
    {"MOD",  MOD},
    {"POW",  POW},
    {"JMP",  JMP},
    {"JGT",  JGT},
    {"JLT",  JLT},
    {"JEQ",  JEQ},
    {"OUT",  OUT},
    {"PUT",  PUT},
    {"INP",  INP},
    {"ONL",  ONL},
    {"PUTI", PUTI},
    {"OUTI", OUTI},
    {"INPI", INPI}
};

static Tokens tokenise(char line[]){
    Tokens t = {0};

    char *token = strtok(line, " ");

    while (token && t.count < 4)
    {
        for (char *p = token; *p; p++)
            *p = toupper((unsigned char)*p);

        t.words[t.count++] = token;
        token = strtok(NULL, " ");
    }

    return t;
}

static void Emit(FILE *file,int op,int a,int b,int c){
    fprintf(file, "%d,%d,%d,%d,\n", op,a,b,c);
}

static Opcode getOpcode(const char *str){
    for (size_t i = 0; i < sizeof(opcodeTable)/sizeof(opcodeTable[0]); i++)
    {
        if (strcmp(str, opcodeTable[i].name) == 0)
            return opcodeTable[i].opcode;
    }
    return HALT;
}


int assemble(const char *input, const char *output){
    FILE *in = fopen(input, "r");
    if (!in) return 1;

    FILE *out = fopen(output, "w");
    if (!out){
        fclose(in);
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), in))
    {
        line[strcspn(line, "\r\n")] = 0;

        Tokens t = tokenise(line);

        if (t.count == 0)
            continue;

        Opcode op = getOpcode(t.words[0]);

        int op1 = 0, op2 = 0, op3 = 0;

        if (t.count > 1) op1 = atoi(t.words[1]);
        if (t.count > 2) op2 = atoi(t.words[2]);
        if (t.count > 3) op3 = atoi(t.words[3]);

        switch (op)
        {
            case HALT:
            case NOP:
            case ONL:
                Emit(out, op, 0, 0, 0);
                break;
            case SET:
                Emit(out, op, op2, 0, op1);
                break;
            case LOAD:
            case STORE:
                Emit(out, op, op1, 0, op2);
                break;
            case ADD:
            case SUB:
            case MUL:
            case DIV:
            case MOD:
            case POW:
                Emit(out, op, op1, op2, op3);
                break;
            case JMP:
                Emit(out, op, op1, 0,0);
                break;
            case JGT:
            case JLT:
            case JEQ:
                Emit(out, op, op1, op2, op3);
                break;
            case OUT:
            case PUT:
            case INP:
            case PUTI:
            case OUTI:
            case INPI:
                Emit(out, op, op1, 0, 0);
                break;
            default:
                printf("Unknown opcode: %s\n", t.words[0]);
                break;
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("usage: ./assemble <program.A> <output.M>\n");
        return 1;
    }
    assemble(argv[1], argv[2]);
}