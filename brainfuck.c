#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Brainfuck interpreter with a bounded tape, precomputed bracket jumps, and
// live stdin input.

#define TAPE_SIZE 300000

static unsigned char tape[TAPE_SIZE];

static void fail(const char *message) {
    fprintf(stderr, "brainfuck: %s\n", message);
    exit(1);
}

static int run(const char *code) {
    size_t n = strlen(code);
    size_t *jumps = malloc(n * sizeof *jumps);
    size_t *stack = malloc(n * sizeof *stack);
    if (!jumps || !stack) fail("out of memory");

    // Map each bracket to its match; this also validates pairing.
    size_t depth = 0;
    for (size_t i = 0; i < n; i++) {
        if (code[i] == '[') {
            stack[depth++] = i;
        } else if (code[i] == ']') {
            if (depth == 0) fail("unmatched ']'");
            size_t open = stack[--depth];
            jumps[open] = i;
            jumps[i] = open;
        }
    }
    if (depth > 0) fail("unmatched '['");

    size_t dp = 0;
    for (size_t i = 0; i < n; i++) {
        switch (code[i]) {
            case '>': // Move the data pointer right.
                if (++dp >= TAPE_SIZE) fail("tape overrun");
                break;
            case '<': // Move the data pointer left.
                if (dp == 0) fail("tape underrun");
                dp--;
                break;
            case '+': // Increment the current cell.
                tape[dp]++;
                break;
            case '-': // Decrement the current cell.
                tape[dp]--;
                break;
            case '.': // Output the current cell as a character.
                putchar(tape[dp]);
                break;
            case ',': { // Read one byte from stdin; EOF sets the cell to zero.
                int c = getchar();
                tape[dp] = c == EOF ? 0 : (unsigned char)c;
                break;
            }
            case '[': // Jump past the matching ']' when the cell is zero.
                if (tape[dp] == 0) i = jumps[i];
                break;
            case ']': // Jump back to the matching '[' when the cell is nonzero.
                if (tape[dp] != 0) i = jumps[i];
                break;
        }
    }

    free(jumps);
    free(stack);
    return 0;
}

int main(int argc, char **argv) {
    char *file_code = NULL;
    // Built-in Hello World, used when no file is given.
    const char *code =
        "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<++"
        "+++++++++++++.>.+++.------.--------.>+.>.";

    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) fail("cannot open file");
        if (fseek(file, 0, SEEK_END) != 0) fail("cannot read file");
        long size = ftell(file);
        if (size <= 0) fail("empty program");
        fseek(file, 0, SEEK_SET);
        file_code = malloc((size_t)size + 1);
        if (!file_code) fail("out of memory");
        if (fread(file_code, 1, (size_t)size, file) != (size_t)size) {
            fail("cannot read file");
        }
        fclose(file);
        file_code[size] = '\0';
        code = file_code;
    }

    int status = run(code);
    free(file_code);
    return status;
}
