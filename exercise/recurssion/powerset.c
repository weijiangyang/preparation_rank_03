#include <stdlib.h>
#include <stdio.h>

void print_tab(int *tab, int size)
{
    int i = 0;

    while (i < size)
    {
        printf("%d",tab[i]);
        i++;
    }
    printf("\n");
}

void backtracking (int *tab, int size, int *path, int target, int current_sum, int startIndex, int depth)
{
    if (current_sum == target)
    {
        print_tab(path, depth);
    }

  
    int i = startIndex;
    while (i < size)
    {
        path[depth] = tab[i];
        backtracking(tab, size, path, target, current_sum + path[depth], i + 1, depth + 1);
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac < 3)
        return (perror("Error: argument error"), 1);
    int size = ac - 2;
    int target = atoi(av[1]);
    int tab[size];
    int i = 0;
    while (i < size)
    {
        tab[i] = atoi(av[i + 2]);
        i++;
    }
    int *path = calloc (size , sizeof(int));
    if (!path)
        return (perror("Error: malloc eche"), 1);
    backtracking(tab, size, path, target, 0, 0, 0);
    free(path);
    
    return (0);
}