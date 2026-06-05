#include "tools.h"
#include <string.h>

const char *getExtension(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return NULL;

    return dot + 1;
}