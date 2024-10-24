#include <stdio.h>
#include <string.h>

char expression[20];
char var = 'Z';

void main()
{
    printf("Enter the expression: ");
    scanf("%s", expression);

    printf("Intermediate code:\n");

    while (strlen(expression) > 3)
    {
        int flag = 0;

        if (flag != 1)
        {
            for (int i = 0; i < strlen(expression); i++)
            {
                if (expression[i] == '/' || expression[i] == '*')
                {
                    printf("%c=%c%c%c\n", var, expression[i - 1], expression[i], expression[i + 1]);
                    
                    expression[i - 1] = var;
                    var--;

                    for (int j = i; expression[j] != '\0'; j++)
                        expression[j] = expression[j + 2]; 
                    
                    flag = 1;
                    break;
                }
            }
        }

        if (flag != 1)
        {
            for (int i = 0; i < strlen(expression); i++)
            {
                if (expression[i] == '+' || expression[i] == '-')
                {
                    printf("%c=%c%c%c\n", var, expression[i - 1], expression[i], expression[i + 1]);
                    
                    expression[i - 1] = var;
                    var--;

                    for (int j = i; expression[j] != '\0'; j++)
                        expression[j] = expression[j + 2]; 
                    
                    flag = 1;
                    break;
                }
            }
        }
    }

    printf("%s\n", expression);
}

