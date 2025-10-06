#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int ft_strlen(char *s)
{
    if (!s || !*s)
        return (0);
    int len = 0;
    while (*s)
    {
        len++;
        s++;
    }
    return (len);
}

void sort(char *str)
{
    int i = 0;
    int j = 0;
    int swapped = 0;
    int n = ft_strlen(str);
    while (i < n - 1)
    {
        swapped = 0;
        j = 0;
        while (j < n - i - 1)
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
        i++;
    }
}

void perm(char *str, char *path, int n, int *used, int depth)
{
    if (depth == n)
    {
        printf("%s\n", path);
        return;
    }
    int i;
    i = 0;
    while (i < n)
    {
        if (!used[i])
        {
            path[depth] = str[i];
            used[i] = 1;
            perm(str, path, n, used, depth + 1);
            used[i] = 0;
        }
        i++;
    }

}

int main(int ac, char **av)
{
    if (ac != 2)
        return (perror("Error: argument error"), 1);
    
    char *str = strdup(av[1]);
    sort(str);
    char *path = calloc (ft_strlen(av[1]) + 1, sizeof(char));// n'oublie pas de initialiser
    if (!path)
        return (perror("Error:malloc echec"), 1);
    int *used = calloc (ft_strlen(str) , sizeof(int));
    if (!used)
        return (perror("Error:malloc echec"), 1);
    perm(str, path, ft_strlen(str),used, 0);
    free(path);
    free(str);
    free(used);
    return (0);
}