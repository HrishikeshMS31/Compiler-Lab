#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

// Structure to store production rules
struct Production {
    char nonTerminal;
    char production[MAX];
};

// Function to check if a character is a terminal
int isTerminal(char symbol) {
    return !isupper(symbol) && symbol != '$'; // If it's not uppercase and not epsilon, it's a terminal
}

// Function to check if epsilon ('$') is in the FIRST set
int containsEpsilon(char firstSet[MAX]) {
    return strchr(firstSet, '$') != NULL; // Check if '$' is in the set
}

// Function to find FIRST of a given non-terminal
void findFirst(struct Production productions[], int count, char firstSet[MAX], char nonTerminal) {
    for (int i = 0; i < count; i++) {
        if (productions[i].nonTerminal == nonTerminal) {
            int allEpsilons = 1; // Assume all symbols can derive epsilon
            
            if (strcmp(productions[i].production, "$") == 0) {
                // If production is exactly epsilon
                if (!strchr(firstSet, '$')) {
                    int len = strlen(firstSet);
                    firstSet[len] = '$';
                    firstSet[len + 1] = '\0';
                }
                continue;
            }
            
            for (int j = 0; productions[i].production[j] != '\0'; j++) {
                char symbol = productions[i].production[j];
                
                // If it's a terminal, add it to FIRST and break
                if (isTerminal(symbol)) {
                    if (!strchr(firstSet, symbol)) { // Avoid duplicates
                        int len = strlen(firstSet);
                        firstSet[len] = symbol;
                        firstSet[len + 1] = '\0';
                    }
                    allEpsilons = 0; // This is a terminal, so no epsilon here
                    break;
                } else {
                    // If it's a non-terminal, recursively find its FIRST
                    char subFirst[MAX] = {0};
                    findFirst(productions, count, subFirst, symbol);

                    // Add the subFirst to the current FIRST set
                    for (int k = 0; subFirst[k] != '\0'; k++) {
                        if (subFirst[k] != '$' && !strchr(firstSet, subFirst[k])) {
                            int len = strlen(firstSet);
                            firstSet[len] = subFirst[k];
                            firstSet[len + 1] = '\0';
                        }
                    }

                    // If epsilon is not in subFirst, stop processing further
                    if (!containsEpsilon(subFirst)) {
                        allEpsilons = 0;
                        break;
                    }
                }
            }

            // If all symbols can derive epsilon, add epsilon to FIRST
            if (allEpsilons && !strchr(firstSet, '$')) {
                int len = strlen(firstSet);
                firstSet[len] = '$';
                firstSet[len + 1] = '\0';
            }
        }
    }
}

// Function to get unique non-terminals
int getNonTerminals(struct Production productions[], int count, char nonTerminals[]) {
    int nonTerminalCount = 0;
    for (int i = 0; i < count; i++) {
        char nonTerminal = productions[i].nonTerminal;
        if (!strchr(nonTerminals, nonTerminal)) { // Check for uniqueness
            nonTerminals[nonTerminalCount++] = nonTerminal;
        }
    }
    return nonTerminalCount;
}

int main() {
    int count;
    struct Production productions[MAX];
    char nonTerminals[MAX] = {0};

    // Input number of productions
    printf("Enter the number of productions: ");
    scanf("%d", &count);

    // Input production rules
    for (int i = 0; i < count; i++) {
        printf("Enter production %d (e.g., A->aBC or A->$ for epsilon): ", i + 1);
        scanf(" %c->%s", &productions[i].nonTerminal, productions[i].production);
    }

    // Get unique non-terminals
    int nonTerminalCount = getNonTerminals(productions, count, nonTerminals);

    // Find and display FIRST set for each non-terminal
    for (int i = 0; i < nonTerminalCount; i++) {
        char firstSet[MAX] = {0};
        findFirst(productions, count, firstSet, nonTerminals[i]);

        // Output the FIRST set for current non-terminal
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (int j = 0; firstSet[j] != '\0'; j++) {
            printf("%c ", firstSet[j]);
        }
        printf("}\n");
    }

    return 0;
}

