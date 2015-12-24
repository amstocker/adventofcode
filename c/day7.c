#include "aoc.h"


#define MAX_LINE_LENGTH 128
#define MAX_NAME_LENGTH 2

typedef WireIdent char[MAX_NAME_LENGTH+1];
typedef Signal int;

typedef enum {
    WIRE
    SIGNAL,
} InputType;

typedef enum {
    INPUT,
    BINOP,
    UNAOP
} GateType;

typedef enum {
    AND,
    OR,
    NOT,
    RSHIFT,
    LSHIFT
} OpType;

typedef struct Gate {
    GateType gatetype;  // If GateType is INPUT, then optype is NULL.
    OpType optype;
    Gate *out,  // If GateType is UNAOP, then in2 is NULL and
         *in1,  // in1 is the argument of the unary operator.
         *in2;
    size_t outn;
}



char *parse_signal(char *p, Signal *signal) {

}


char *parse_ident(char *p, WireIdent *ident) {

}


char *parse_op(char *p, OpType *optype) {

}


void parse_line(char *line) {
    char *p = line;

    while (*p) {
        switch ((int)*p) {
            case 'a' ... 'z':

            case 'A' ... 'Z':
            case '0' ... '9':
            default:
                error("invalid line");
        }
    }
}


int main() {
    FILE *fp = fopen("day7_input.txt", "r");
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line,
                 MAX_LINE_LENGTH,
                 fp))
    {
        parse_line(line);    
        memset(line, 0, MAX_LINE_LENGTH);
    }
}
