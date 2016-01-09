#include "aoc.h"

#define BUF_SIZE 256

char *original = "CRnCaSiRnBSiRnFArTiBPTiTiBFArPBCaSiThSiRnTiBPBPMgArCaSiRnTiMgArCaSiThCaSiRnFArRnSiRnFArTiTiBFArCaCaSiRnSiThCaCaSiRnMgArFYSiRnFYCaFArSiThCaSiThPBPTiMgArCaPRnSiAlArPBCaCaSiRnFYSiThCaRnFArArCaCaSiRnPBSiRnFArMgYCaCaCaCaSiThCaCaSiAlArCaCaSiRnPBSiAlArBCaCaCaCaSiThCaPBSiThPBPBCaSiRnFYFArSiThCaSiRnFArBCaCaSiRnFYFArSiThCaPBSiThCaSiRnPMgArRnFArPTiBCaPRnFArCaCaCaCaSiRnCaCaSiRnFYFArFArBCaSiThFArThSiThSiRnTiRnPMgArFArCaSiThCaPBCaSiRnBFArCaCaPRnCaCaPMgArSiRnFYFArCaSiThRnPBPMgAr";


typedef struct Replacement {
    char in[BUF_SIZE],
         out[BUF_SIZE];
    struct Replacement *next;
} Replacement;


Replacement *make_replacements_list(FILE *fp) {
    char buf[BUF_SIZE],
         repl_in[BUF_SIZE],
         repl_out[BUF_SIZE];

    Replacement *head = NULL,
                *last = NULL,
                *repl;

    while (fgets(buf, BUF_SIZE, fp)) {
        if (sscanf(buf, "%s => %s\n", repl_in, repl_out) == EOF) {
            error("bad line");
            return NULL;
        }
        repl = malloc(sizeof(Replacement));
        if (!head) {
            head = repl;
        }
        strcpy(repl->in, repl_in);
        strcpy(repl->out, repl_out);
        if (last) {
            last->next = repl;
        }
        last = repl;
    }
    repl->next = NULL;
    return head;
}


void free_replacements_list(Replacement *r) {
    Replacement *next;
    while (r) {
        next = r->next;
        free(r);
        r = next;
    }
}


char *make_replacement(Replacement *repl, int *i) {
    int orig_len = strlen(original);
    int ncmp = strlen(repl->in);
    int out_len = strlen(repl->out);
    int new_len = orig_len - ncmp + out_len + 1;
    int made_replacement = 0;
    char *new = calloc(new_len, sizeof(char));
    char *p = original;
    char *o = new;

    for (int j = 0; j < *i; j++) {
        *o++ = *p++;
    }

    for (; *i < orig_len - ncmp; (*i)++) {
        if (strncmp(repl->in, p, ncmp) == 0) {
            char *rp = repl->out;
            for (int k = 0; k < out_len; k++) {
                *o++ = *rp++;
            }
            p += ncmp;
            *i += ncmp;
            made_replacement = 1;
            break;
        }
        *o++ = *p++;
    }

    if (!made_replacement) {
        free(new);
        return NULL;
    }
    for (int j = *i; j < orig_len; j++) {
        *o++ = *p++;
    }

    return new;
}


int main() {
    FILE *fp = fopen("day19_input.txt", "r");
    Set *s = Set_new();

    Replacement *head = make_replacements_list(fp);
    Replacement *repl = head;
    int total = 0;
    int orig_len = strlen(original);
    
    while (repl) {
        int i = 0;
        int lim = orig_len - strlen(repl->in);
        char *str;
        while (i < lim) {
            str = make_replacement(repl, &i);
            if (str) {
                Set_add(s, str);
                total++;
            }
        }
        repl = repl->next;
    }
    
    printf("total: %i, set size: %i\n", total, s->nelem);
    
    // free all
    char **strs = Set_iter(s);
    for (int i = 0; i < s->nelem; i++) {
        free(strs[i]);
    }
    free(strs);
    free_replacements_list(head);
    Set_free(s);
    return 0;
}
