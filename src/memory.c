#include "Memory.h"
#include <stdio.h>

MEM loadMemory(const char *path) {
    MEM mem = {0};

    FILE *file = fopen(path, "r");
    if (!file) return mem;

    int i = 0;
    while (i + 3 < 256) {
        int op, a, b, c;
        if (fscanf(file, "%d,%d,%d,%d,", &op, &a, &b, &c) != 4)
            break;
        mem.Code[i]     = op;
        mem.Code[i + 1] = a;
        mem.Code[i + 2] = b;
        mem.Code[i + 3] = c;
        i += 4;
    }

    fclose(file);
    return mem;
}