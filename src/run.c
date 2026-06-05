#include "VM.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: ./run <program>\n");
        return 1;
    }

    VM *vm = createVM();
    runVM(vm, argv[1]);
    destroyVM(vm);

    return 0;
}