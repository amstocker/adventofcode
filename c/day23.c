#include "aoc.h"

#define LINEBUF_SIZE 64
#define ARGBUF_SIZE 32


//static unsigned int REGISTER_A = 0;
//static unsigned int REGISTER_B = 0;


typedef enum {
    REG_A,
    REG_B,
    REG_INVALID,
} Register;


typedef enum {
    OP_HLF,
    OP_TPL,
    OP_INC,
    OP_JMP,
    OP_JIE,
    OP_JIO,
    OP_INVALID,
} Operation;


typedef struct {
    Operation op;
    Register reg;
    int val;
} Instruction;


void read_until_eol(FILE *fp, char *linebuf) {
    // assumes buffer won't overflow...
    char c;
    char *p = linebuf;
    while ((c = fgetc(fp)) != '\n') {
        *p++ = c;
    }
    *p = '\0';
}


Operation parse_op(char *op_str) {

#define ifcmp(S) if (strcmp(op_str, (S)) == 0)
    ifcmp("hlf") return OP_HLF;
    ifcmp("tpl") return OP_TPL;
    ifcmp("inc") return OP_INC;
    ifcmp("jmp") return OP_JMP;
    ifcmp("jie") return OP_JIE;
    ifcmp("jio") return OP_JIO;
#undef ifcmp

    error("invalid instruction");
    return OP_INVALID;
}


Register parse_reg(char *arg_str) {

#define ifcmp(S) if (strcmp(arg_str, (S)) == 0)
    ifcmp("a") return REG_A;
    ifcmp("b") return REG_B;
#undef ifcmp

    error("invalid register");
    return REG_INVALID;
}


int parse_val(char *val_str) {
    int i;
    int r = sscanf(val_str, "%i", &i);
    if (r == EOF) {
        error("invalid value");
        return 0;
    }
    return i;
}


void parse_one_arg(char *linebuf, Instruction *inst) {
    char *fmt = "%s %s";
    char op_str[ARGBUF_SIZE];
    char arg_str[ARGBUF_SIZE];
    int r = sscanf(linebuf, fmt, op_str, arg_str);
    if (r == EOF) {
        error("invalid line");
        return;
    }
    inst->op = parse_op(op_str);
    switch (inst->op) {
        case OP_JMP:
            inst->val = parse_val(arg_str);
            break;
        default:
            inst->reg = parse_reg(arg_str);
    }
}


void parse_two_args(char *linebuf, Instruction *inst) {
    char *fmt = "%s %s %s";
    char op_str[ARGBUF_SIZE];
    char arg1_str[ARGBUF_SIZE];
    char arg2_str[ARGBUF_SIZE];
    int r = sscanf(linebuf, fmt, op_str, arg1_str, arg2_str);
    if (r == EOF) {
        error("invalid line");
        return;
    }
    inst->op = parse_op(op_str);
    inst->reg = parse_reg(arg1_str);
    inst->val = parse_val(arg2_str);
}


int main() {
    FILE *fp = fopen("day23_input.txt", "r");
    char c;
    char linebuf[LINEBUF_SIZE];
    char *p = linebuf;

    Instruction inst;
    while ((c = fgetc(fp)) != EOF) {
        switch (c) {
            case '\n':
                *p = '\0';
                parse_one_arg(linebuf, &inst);
                break;
            case ',':
                read_until_eol(fp, p);
                parse_two_args(linebuf, &inst);
                break;
            default:
                *p++ = c;
                continue;
        }

        p = linebuf;
        memset(&inst, 0, sizeof inst);
    }
}
