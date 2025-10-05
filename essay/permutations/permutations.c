#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void sort(char *str)
{
    int i;
    int j;
    int swapped;
    int len;

    len = strlen(str);
    i = 0;
    while (i < len - 1)
    {
        j = 0;
        swapped = 0;
        while (j < len - i - 1)
        {
            if (str[j] > str[j + 1])
            {
                char tmp = str[j + 1];
                str[j + 1] = str[j];
                str[j] = tmp;
                swapped = 1;
            }
            j++;
        }
        if (swapped == 0)
            break;
    }
    
    i++;
}
void backtracing(char *str, char *path, int depth, int *used)
{
    int i;
    int len;

    len = strlen(str);
    i = 0;
    if (depth == len)
    {
        path[len] = '\0';
        printf("%s\n", path);
        return;
    }
    while (i < len)
    {
        if (!used[i])
        {
            path[depth] = str[i];
            used[i] = 1;
            backtracing(str, path, depth + 1, used);
            used[i] = 0;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    char *path;
    int *used;
    if (ac != 2)
        return (stderr, printf("Error:  argument error"), 1);
    char *str = strdup(av[1]);
    sort(str);
    int len = strlen(str);
    path = malloc(len + 1);
    if (!path)
        return (stderr, printf("Error : malloc echec"), 1);
    used = calloc(len, sizeof(int));
    if (!used)
        return (stderr, printf("Error : malloc echec"), 1);
    backtracing(str, path, 0, used);
    free(path);
    free(used);
    free(str);
    return (0);
}