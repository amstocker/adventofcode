#include <stdio.h>
#include <stdlib.h>
#include "aoc.h"


char *input_open(const char *filename) {
    int len;
    char *buf;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        goto error;
    }
    
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    buf = malloc(len+1);
    if (!buf) {
        goto error;
    }
    
    fread(buf, 1, len, fp);
    buf[len] = '\0';
    fclose(fp);
    return buf;

error:
    error("could not load input");
    return 0;
}
