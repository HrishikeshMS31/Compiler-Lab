#include <stdio.h>
#include <string.h>
char line[100];
int operator(char c)
{
	if(c == '+'||c == '-'||c == '*'||c == '/'||c == '='){
		printf("%c : Operator\n", c);
	    	return 1;
	    	}
    return 0;
}

int delimiter(char c)
{
	if(c == '{'||c == '}'||c == '('||c == ')'||c == '['||c == ']'||c == ','||c == ';'){
		printf("%c : Delimiter\n", c);
		return 1;
	}
    return 0;
}

int keyword(char token[])
{
    if (strcmp(token, "void") == 0 || strcmp(token, "char") == 0 || strcmp(token, "main") == 0 ||
        strcmp(token, "int") == 0 || strcmp(token, "long") == 0 ||
        strcmp(token, "float") == 0 || strcmp(token, "double") == 0)
    { 
        return 1;
    }

    return 0;
}

void main()
{
    char c;
    FILE *f = fopen("input.txt", "r");
    printf("Hrishikesh M Sreenivas\n\n");
    while (fgets(line, sizeof(line), f))
    {
        int flag1 = 0;
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == '/' && line[i + 1] == '/')
            {
                flag1 = 1;
                break;
            }       
        }
        if (flag1)
            continue;        
        int flag2 = 0;
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == '/' && line[i + 1] == '*')
            {
                while (fgets(line, sizeof(line), f))
                {
                    for (int j = 0; j < strlen(line); j++)
                    {
                        if (line[j] == '*' && line[j + 1] == '/')
                            flag2 = 1;
                    }
                    if (flag2)
                        break;
                }
            }
        }
        if (flag2)
            continue;
        if(strcmp(line, "\t") != 1){
        printf("\n-------------------------");
        printf("\n%s", line);
        printf("-------------------------\n");
        }
        char token[100];
        int index = 0;
        strcpy(token, "");

        for (int i = 0; i < strlen(line); i++)
        {
            
		    
            if (operator(line[i]) || delimiter(line[i]) || line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            {
                // Check if the token is an identifier or a keyword
                if (strcmp(token, "") != 0)
                {
                    if (keyword(token))
                        printf("%s : Keyword\n", token);
                    else  
                        printf("%s : Identifier\n", token);

                    strcpy(token, "");
                    index = 0;
                }
            }
            else  
            {
                token[index++] = line[i];
                token[index] = '\0';
            }
        }
    }

    fclose(f);
}

