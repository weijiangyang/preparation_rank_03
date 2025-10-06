#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int abs_val(int n)
{
    return (n < 0 ? -n : n);
}

int no_attack(int *tab, int col, int row)
{
    int pre_col;
    int pre_row;

    pre_col = 0;
    while (pre_col < col)
    {
        pre_row = tab[pre_col]; // ne fais pas tab[pre_col] = pre_row !!!!
        if (row == pre_row || abs_val(row - pre_row) == abs_val(col - pre_col))
            return (0);

        pre_col++;
    }
    return (1);
}

void backtracking(int *tab, int col, int n, int *nb_sols)
{
    if (col == n)
    {
        int i = 0;
        while (i < n)
        {
            printf("%d", tab[i]);
            i++;
        }
        (*nb_sols)++;
        printf("\n");
        return; // n'oublie pas return
    }

    int row;
    row = 0;
    while (row < n)
    {

        if (no_attack(tab, col, row))
        {
            tab[col] = row;
            backtracking(tab, col + 1, n, nb_sols);
        }

        row++;
    }
}

int main(int ac, char **av)
{
    if (ac == 2 && av[1][0] != '-')
    {
        int n = atoi(av[1]);
        int nb_sols = 0;
        int *positions = malloc(sizeof(int) * n); // malloc pour tab
        if (!positions)
            return 1;
        backtracking(positions, 0, n, &nb_sols);
        printf("%d\n", nb_sols);
        free(positions); // liberer tab
    }
    return 0;
}
