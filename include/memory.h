#ifndef MEMORY_H_
#define MEMORY_H_

typedef struct{
    int Code[256];
    int Data[256];
} MEM;

MEM loadMemory(const char *path);


#endif