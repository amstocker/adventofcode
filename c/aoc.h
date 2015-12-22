/*
 * Advent of Code
 * ==============
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


// error.c
void error(const char *msg);

// utils.c
int int_array_min(const int *array, const int len);
int *int_array_mins(const int *array, const int len, const int n);
int int_array_sum(const int *array, const int len);
int int_array_prod(const int *array, const int len);
