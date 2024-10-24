/*
example input:

a = b + c
d = a - e
f = b * d
g = f
hault


*/
#include <stdio.h>
#include <string.h>

void generateAssembly(char *tac) {
    char var1, var2, var3, operation;

    // Parse the three-address code: e.g., "a = b + c"
    if (sscanf(tac, "%c = %c %c %c", &var1, &var2, &operation, &var3) == 4) {
        // Handle different operations and generate assembly
        switch (operation) {
            case '+':
                printf("MOV AX,%c\n", var2);
                printf("ADD AX,%c\n", var3);
                printf("MOV %c,AX\n", var1);
                break;
            case '-':
                printf("MOV AX,%c\n", var2);
                printf("SUB AX,%c\n", var3);
                printf("MOV %c,AX\n", var1);
                break;
            case '*':
                printf("MOV AX,%c\n", var2);
                printf("MUL %c\n", var3);
                printf("MOV %c,AX\n", var1);
                break;
            case '/':
                printf("MOV AX,%c\n", var2);
                printf("DIV %c\n", var3);
                printf("MOV %c,AX\n", var1);
                break;
            default:
                printf("Invalid operation: %s\n", tac);
                break;
        }
    } else if (sscanf(tac, "%c = %c", &var1, &var2) == 2) {
        printf("MOV %c,%c\n", var1, var2);
    } else {
        printf("Invalid expression: %s\n", tac);
    }
}

int main() {
    char tac[100];

    printf("Enter three-address code expressions (type 'hault' to end):\n");
    // Read multiple lines until "hault" is entered
    while (1) {
        fgets(tac, sizeof(tac), stdin);

        // Remove the newline character from input
        tac[strcspn(tac, "\n")] = 0;

        // Break if the user types "hault"
        if (strcmp(tac, "hault") == 0) {
            break;
        }
	
        // Generate the assembly instructions for the input line
        generateAssembly(tac);
    }

    return 0;
}

