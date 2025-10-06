/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_valide(char *str)
{
    int bal = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(') bal++;
        else if (str[i] == ')')
        {
            bal--;
            if (bal < 0) return 0;
        }
    }
    return (bal == 0);
}

void backtracking(char *str, int ldel, int rdel, int startIndex)
{
    if (ldel == 0 && rdel == 0)
    {
        if (is_valide(str))
            printf("%s\n", str);
        return;
    }

    for (int i = startIndex; str[i]; i++)
    {
        if (str[i] == '(' && ldel > 0)
        {
            char tmp = str[i];
            str[i] = '_';  // remplacer par '_'
            backtracking(str, ldel - 1, rdel, i + 1);
            str[i] = tmp;  // revenir en arrière
        }
        else if (str[i] == ')' && rdel > 0)
        {
            char tmp = str[i];
            str[i] = '_';  // remplacer par '_'
            backtracking(str, ldel, rdel - 1, i + 1);
            str[i] = tmp;  // revenir en arrière
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Usage: %s <string>\n", av[0]);
        return 1;
    }

    char *str = strdup(av[1]); // copie de la chaîne
    int ldel = 0, rdel = 0;
    int bal = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            bal++;
        else if (str[i] == ')')
        {
            bal--;
            if (bal < 0)
            {
                rdel++;  // trop de ')'
                bal = 0;
            }
        }
    }
    ldel = bal;  // trop de '('

    backtracking(str, ldel, rdel, 0);

    free(str);
    return 0;
}*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_valide(char *str)
{
    int bal = 0;
    int i = 0;

    while (str[i])
    {
        if (str[i] == '(')
            bal++;
        if (str[i] == ')')
        {
            bal--;
            if (bal < 0)
                return (0);
        }
        i++;
    }
    if (bal == 0)
        return (1);
    else
        return (0);
}

void backtracking (char *str, int ldel, int rdel, int startIndex)
{
    if (ldel == 0 && rdel == 0)
    {
        if (is_valide(str))
         printf("%s\n", str);
        return ;
    }
    int i;

    i = startIndex;
    while (str[i])
    {
        if (str[i] == '(')
        {
            if (ldel > 0)
            {
                char tmp = str[i];
                str[i] = '_';
                backtracking(str, ldel - 1, rdel, i + 1);
                str[i] = tmp;
            }
        }
        if (str[i] == ')')
        {
            if (rdel > 0)
            {
                char tmp = str[i];
                str[i] = '_';
                backtracking(str, ldel, rdel - 1, i + 1);
                str[i] = tmp;
            }
        } 
        i++;
    }
}

int main(int ac, char **av)
{
    int len = strlen(av[1]);
    int bal = 0;
    char *str = malloc (len + 1);
    str = strdup(av[1]);
    int ldel = 0;
    int rdel = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '(')
            bal++;
        else if (str[i] == ')')
        {
            bal --;
            if (bal < 0)
            {
                rdel++;
                bal = 0;
            }
                
        }
        i++;
    }
    ldel = bal;
    backtracking(str, ldel, rdel, 0);
    return (0);
}