#include <openssl/md5.h>
#include "aoc.h"

// Day 4 Input:
const char *SECRET = "iwrupvqb";


void md5(unsigned char *buf, char *str, int nb) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, str, nb);
    MD5_Final(buf, &ctx);
}


void print_md5(unsigned char *hash) {
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", hash[i]);
    fputc('\n', stdout);
}


// Part I: checks for five leading zeros
int match5(unsigned char *hash) {
    return (!hash[0] &&
            !hash[1] &&
             hash[2] < 0x10);
}


// Part II: checks for six leading zeros
int match6(unsigned char *hash) {
    return (!hash[0] &&
            !hash[1] &&
            !hash[2]);
}


int main() {
    char string[256];
    int s = sizeof(SECRET);
    memcpy(string, SECRET, s);
    unsigned char *buf = malloc(sizeof(char) * MD5_DIGEST_LENGTH);
    
    int modmask = 10;
    int nlen = 1;
    for(int i = 1;; i++) {
        sprintf(&string[s], "%d", i);
        if ((i % modmask) == 0) {
            nlen++;
            modmask *= 10;
        }
        md5(buf, string, s+nlen);
        if (match6(buf)) {
            printf("found %s with hash: ", string);
            print_md5(buf);
            break;
        }
        if (match5(buf)) {
            printf("found %s with hash: ", string);
            print_md5(buf);
        }
    }
    
    free(buf);
    return 0;
}


// Reddit solution: https://www.reddit.com/r/adventofcode/comments/3vdn8a/day_4_solutions/cxmqljn
/***

#include <openssl/md5.h>
#include <inttypes.h>
#include <stdio.h>

#define KEY "abcdef"
#define LEN 32

#define MASK 0x00f0ffff // adjust for endianness and # of leading zeros

int main()
{
    unsigned char hash[16], buf[LEN];
    long i = 1;

    do MD5(buf, snprintf(buf, LEN, KEY "%ld", ++i), hash);
    while(*(int32_t *) hash & MASK);

    printf("%ld\n", i);

    return 0;
}

***/
