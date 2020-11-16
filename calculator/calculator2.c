#include <stdio.h>
#include <stdlib.h> // atof
#include <ctype.h> // isadigit

#define LINEBUF 100
#define NUMBUF 100
#define VALSTACK 100

struct Stack {
    int pos;
    double array[VALSTACK];
};

int get_line(char line[], int limit);
void calculator(char line[]);
double parse_number(char line[], int *i);
double push(struct Stack *stack, double f);
double pop(struct Stack *stack);

int main() {
    char line[LINEBUF];
    while (get_line(line, LINEBUF) > 0) {
        calculator(line);
    }
    return 0;
}

int get_line(char line[], int limit) {
    int i, c;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i += 1) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        i += 1;
    }
    line[i] = '\0';
    return i;
}

void calculator(char line[]) {
    int i, c;
    double op1, op2;
    struct Stack stack;
    stack.pos = 0;

    for (i = 0; line[i] != '\0'; i += 1) {
        // eat whitespace
        for ( ; line[i] == ' ' || line[i] == '\t'; i += 1) {
            ;
        }
        if (isdigit(line[i])) {
            push(&stack, parse_number(line, &i));
            continue;
        }
        // parse operators
        switch (line[i]) {
            case '+':
                op2 = pop(&stack);
                op1 = pop(&stack);
                printf("%g + %g = %g\n", op1, op2, push(&stack, op1 + op2));
                break;
            case '-':
                op2 = pop(&stack);
                op1 = pop(&stack);
                printf("%g - %g = %g\n", op1, op2, push(&stack, op1 - op2));
                break;
            case '*':
                op2 = pop(&stack);
                op1 = pop(&stack);
                printf("%g * %g = %g\n", op1, op2, push(&stack, op1 * op2));
                break;
            case '/':
                op2 = pop(&stack);
                op1 = pop(&stack);            
                if (op2 != 0) {
                    printf("%g / %g = %g\n", op1, op2, push(&stack, op1 / op2));
                }
                else {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop(&stack));
                break;
            default:
                printf("error: unkown operator %c\n", line[i]);
                break;
        }
    }
}

double parse_number(char line[], int *i) {
    int j;
    char tmp[NUMBUF];

    // collect integer part
    for (j = 0; isdigit(line[*i]) && *i < NUMBUF - 1; *i += 1, j += 1) {
        tmp[j] = line[*i];
    }
    // collect fraction part
    if (line[*i] == '.') {
        tmp[j] = line[*i];
        for ( *i += 1, j += 1; isdigit(line[*i]) && *i < NUMBUF - 1; *i += 1, j += 1) {
            tmp[j] = line[*i];
        }
    }
    tmp[j] = '\0';
    return atof(tmp);
}

double push(struct Stack *stack, double f) {
    int *p = &stack->pos;
    double *array = stack->array;
    if (*p < VALSTACK) {
        array[*p] = f;
        *p += 1;
        return f;
    }
    else {
        printf("error: stack full, can't push %g\n", f);
        return 0.0;
    }
}

double pop(struct Stack *stack) {
    int *p = &stack->pos;
    double *array = stack->array;
    if (*p > 0) {
        *p -= 1;
        return array[*p];
    }
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
