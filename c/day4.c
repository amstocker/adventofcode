#include <openssl/md5.h>
#include "aoc.h"

const char *SECRET = "iwrupvqb";


void md5(MD5_CTX *ctx, unsigned char *buf, char *str, int nb) {
    MD5_Update(ctx, str, nb);
    MD5_Final(buf, ctx);
}


void print_md5(unsigned char *hash) {
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", hash[i]);
    fputc('\n', stdout);
}


// checks for leading five zeros
int match(unsigned char *hash) {
    return (!hash[0] && !hash[1] && !hash[2] && !hash[3] && hash[4] < 0x10);
}


int main() {
    char string[256];
    int s = sizeof(SECRET);
    memcpy(string, SECRET, s);
    
    unsigned char buf[MD5_DIGEST_LENGTH];
    MD5_CTX ctx;
    MD5_Init(&ctx);

    for(int i = 0;; i++) {
        sprintf(&string[s], "%d", i);
        
        md5(&ctx, &buf, string, s+(i/10)+1); // length of secret plus # of digits
        
        if (match(buf)) {
            break;
        }
    }
    
    printf("found %s\n with hash: ", string);
    print_md5(buf);
    return 0;
}
