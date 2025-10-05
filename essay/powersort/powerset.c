#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tab(int *tab, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        printf("%d", tab[i]);
        if (i < n - 1)
            printf(" ");
        i++;
    }
    printf("\n");
}

void backtracking (int *tab, int *path, int size, int target,  int startIndex, int current_sum, int depth)
{
    if (current_sum == target)
    {
        print_tab(path, depth);
    }

    int i = startIndex;
    while (i < size)
    {
        path[depth] = tab[i];
        backtracking(tab, path, size, target, i + 1, current_sum + tab[i], depth + 1);
        i++;
    }
}

int main(int ac, char **av)
{
    int *tab;

    tab = malloc ((ac - 2) * sizeof(int));
    if (!tab)
        return (stderr, printf("Error: malloc"), 1);
    int i = 0;
    while (i < ac - 2)
    {
        tab[i] = atoi(av[i + 2]);
        i++;
    }
    int target = atoi(av[1]);
    int size = ac - 2;
    int *path = malloc ((size) * sizeof(int));
    if (!path)
        return (stderr, printf("Error: malloc"), 1);
    backtracking(tab, path, size, target, 0, 0, 0);
    return (0);
}