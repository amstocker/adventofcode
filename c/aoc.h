/*
 * Advent of Code
 * ==============
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// error.c
void error(const char *msg);

// input.c
char *input_open(const char *filename);

// utils.c
int str_count_lines(const char *str);
int int_array_min(const int *array, const int len);
int int_array_sum(const int *array, const int len);
