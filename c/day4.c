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


// checks for leading five zeros
int match(unsigned char *hash) {
    return (!hash[0] &&
            !hash[1] &&
             hash[2] < 0x10);
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
        if (match(buf)) {
            break;
        }
    }
    
    printf("found %s with hash: ", string);
    print_md5(buf);
    free(buf);
    return 0;
}
