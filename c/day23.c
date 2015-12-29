/***

--- Day 23: Opening the Turing Lock ---

Little Jane Marie just got her very first computer for Christmas from some
unknown benefactor. It comes with instructions and an example program, but the
computer itself seems to be malfunctioning. She's curious what the program
does, and would like you to help her run it.

The manual explains that the computer supports two registers and six
instructions (truly, it goes on to remind the reader, a state-of-the-art
technology). The registers are named a and b, can hold any non-negative
integer, and begin with a value of 0. The instructions are as follows:

  - hlf r sets register r to half its current value, then continues with the
    next instruction.
  - tpl r sets register r to triple its current value, then continues with the
    next instruction.
  - inc r increments register r, adding 1 to it, then continues with the next
    instruction.
  - jmp offset is a jump; it continues with the instruction offset away
    relative to itself.
  - jie r, offset is like jmp, but only jumps if register r is even ("jump if
    even").
  - jio r, offset is like jmp, but only jumps if register r is 1 ("jump if
    one", not odd).

All three jump instructions work with an offset relative to that instruction.
The offset is always written with a prefix + or - to indicate the direction of
the jump (forward or backward, respectively). For example, jmp +1 would simply
continue with the next instruction, while jmp +0 would continuously jump back
to itself forever.

The program exits when it tries to run an instruction beyond the ones defined.

For example, this program sets a to 2, because the jio instruction causes it to
skip the tpl instruction:

    inc a
    jio a, +2
    tpl a
    inc a

What is the value in register b when the program in your puzzle input is
finished executing?

Your puzzle answer was 307.

--- Part Two ---

The unknown benefactor is very thankful for releasi-- er, helping little Jane
Marie with her computer. Definitely not to distract you, what is the value in
register b after the program is finished executing if register a starts as 1
instead?

Your puzzle answer was 160.

***/

#include "aoc.h"

#define LINEBUF_SIZE 64
#define ARGBUF_SIZE 32


// part 1:
// static unsigned int REGISTER_A = 0;
// part 2:
static unsigned int REGISTER_A = 1;
static unsigned int REGISTER_B = 0;

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

typedef struct Instruction {
    Operation op;
    Register reg;
    int val;
    int lineno;
    struct Instruction *prev;
    struct Instruction *next;
} Instruction;

typedef struct {
    Instruction *first;
    int nlines;
} Program;

void print_instruction(Instruction *inst) {
    printf("[line: %i, op: %i, reg: %i, val: %i]\n",
            inst->lineno, inst->op, inst->reg, inst->val);
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


void read_until_eol(FILE *fp, char *buf) {
    // assumes buffer won't overflow...
    char c;
    while ((c = fgetc(fp)) != '\n') {
        *buf++ = c;
    }
    *buf = '\0';
}


Instruction *parse_instruction(FILE *fp) {
    char c;
    char linebuf[LINEBUF_SIZE];
    char *p = linebuf;
    Instruction *inst = calloc(1, sizeof(Instruction));
    while ((c = fgetc(fp)) != EOF) {
        switch (c) {
            default:
                *p++ = c;
                continue;
            case '\n':
                *p = '\0';
                parse_one_arg(linebuf, inst);
                break;
            case ',':
                read_until_eol(fp, p);
                parse_two_args(linebuf, inst);
                break;
        }
        return inst;
    }
    free(inst);
    return NULL;
}


Program *create_program(FILE *fp) {
    int line = 0;
    Program *prog = malloc(sizeof(Program));
    Instruction *inst;
    Instruction *last;
    while ((inst = parse_instruction(fp))) {
        if (!(prog->first)) {
            prog->first = inst;
            inst->prev = NULL;
        } else {
            inst->prev = last;
            last->next = inst;
        }
        last = inst;
        inst->lineno = line;
        line++;
    }
    prog->nlines = line;
    last->next = NULL;
    return prog;
}


void free_program(Program *prog) {
    Instruction *inst = prog->first;
    while (inst) {
        free(inst);
        inst = inst->next;
    }
    free(prog);
}


unsigned int *choose_reg(Instruction *inst) {
    switch (inst->reg) {
        case REG_A:
            return &REGISTER_A;
        case REG_B:
            return &REGISTER_B;
        case REG_INVALID:
            break;
    }
    error("shouldn't get here");
    return NULL;
}


Instruction *do_jump(Instruction *inst) {
    int jmp = inst->val;
    if (jmp >= 0) {
        while (jmp-- && inst) {
            inst = inst->next;
        }
    } else if (jmp < 0) {
        while (jmp++ && inst) {
            inst = inst->prev;
        }
    }
    return inst;
}


Instruction *execute_instruction(Instruction *inst) {
    switch (inst->op) {
        case OP_HLF:
            *choose_reg(inst) >>= 1;
            break;
        case OP_TPL:
            *choose_reg(inst) *= 3;
            break;
        case OP_INC:
            (*choose_reg(inst))++;
            break;
        case OP_JMP:
            return do_jump(inst);
        case OP_JIE:
            if (*choose_reg(inst) % 2 == 0) {
                return do_jump(inst);
            }
            break;
        case OP_JIO:
            if (*choose_reg(inst) == 1) {
                return do_jump(inst);
            }
            break;
        case OP_INVALID:
            error("shouldn't get here");
            return NULL;
    }
    // if no jump
    return inst->next;
}


void execute_program(Program *prog) {
    Instruction *next = prog->first;
    while (next) {
        next = execute_instruction(next);
    }
}


int main() {
    FILE *fp = fopen("day23_input.txt", "r");
    Program *prog = create_program(fp);
    fclose(fp);
    
    execute_program(prog);
    printf("final state; A: %u, B: %u\n", REGISTER_A, REGISTER_B);
    
    free_program(prog);
    return 0;
}
