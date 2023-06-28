#include <stdio.h>

#define MAX 300000

void brainFuck(char *code, char *input) {
    // Data array initialized to zero
    char tape[MAX] = {0};
    // Data pointer
    char *dp = tape;
    // Input pointer
    char *ip = input;
    // Current stream char
    char c;
    // Loop pointer 
    char *lp;

    while ((c = *code++)) {
        switch (c) {
            case '<':
                dp--; // Move data pointer to the left
                break;
            case '>':
                dp++; // Move data pointer to the right
                break;
            case '+':
                (*dp)++; // Increment the value at the current address
                break;
            case '-':
                (*dp)--; // Decrement the value at the current address
                break;
            case '.':
                putchar(*dp); // Output the current byte
                break;
            case ',':
                *dp = *ip++; // Accept input and store it in the current address
                break;
            case '[': // Start of loop, jump forward if the value at the current address is zero
                if (!*dp) {
                    // Inside loop flag
                    int loop_cnt = 1;
                    while (loop_cnt) {
                        c = *code++;
                        if (c == '[') {
                            loop_cnt++;
                        } else if (c == ']') {
                            loop_cnt--;
                        }
                    }
                } else {
                    lp = code; // Save the loop start position
                }
                break;
            case ']': // End of loop, jump back to the start if the value at the current address is non-zero
                if (*dp) {
                    code = lp; // Jump back to starting position
                } 
                break;
        }
    }
}

int main(void) {
    char *code = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
    char *input = "";
    brainFuck(code, input);

    return 0;
}

