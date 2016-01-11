#include "aoc.h"

#define BUF_SIZE 256

char *original = "CRnCaSiRnBSiRnFArTiBPTiTiBFArPBCaSiThSiRnTiBPBPMgArCaSiRnTiMgArCaSiThCaSiRnFArRnSiRnFArTiTiBFArCaCaSiRnSiThCaCaSiRnMgArFYSiRnFYCaFArSiThCaSiThPBPTiMgArCaPRnSiAlArPBCaCaSiRnFYSiThCaRnFArArCaCaSiRnPBSiRnFArMgYCaCaCaCaSiThCaCaSiAlArCaCaSiRnPBSiAlArBCaCaCaCaSiThCaPBSiThPBPBCaSiRnFYFArSiThCaSiRnFArBCaCaSiRnFYFArSiThCaPBSiThCaSiRnPMgArRnFArPTiBCaPRnFArCaCaCaCaSiRnCaCaSiRnFYFArFArBCaSiThFArThSiThSiRnTiRnPMgArFArCaSiThCaPBCaSiRnBFArCaCaPRnCaCaPMgArSiRnFYFArCaSiThRnPBPMgAr";
int orig_len;


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
    int in_len = strlen(repl->in);
    int out_len = strlen(repl->out);
    
    // size of replacement string depends on difference btw in & out lengths
    char *new = calloc(orig_len + (out_len - in_len) + 1, sizeof(char));
    char *p = original;
    char *o = new;

    for (int j = 0; j < *i; j++) {
        *o++ = *p++;
    }

    int made_replacement = 0;
    for (; *i < orig_len - in_len; (*i)++) {
        if (strncmp(repl->in, p, in_len) == 0) {
            for (int k = 0; k < out_len; k++) {
                *o++ = repl->out[k];
            }
            p += in_len;
            *i += in_len;
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


void part1(Replacement *repl) {
    Set *s = Set_new();

    int total = 0;
    while (repl) {
        int start = 0;
        int lim = orig_len - strlen(repl->in);
        char *str;
        while (start < lim) {
            str = make_replacement(repl, &start);
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
    Set_free(s);
}


int main() {
    orig_len = strlen(original);
    
    FILE *fp = fopen("day19_input.txt", "r");
    Replacement *head = make_replacements_list(fp);
    
    part1(head);
    
    free_replacements_list(head);
    return 0;
}
