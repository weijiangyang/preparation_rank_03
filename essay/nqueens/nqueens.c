#include <stdio.h>
#include <stdlib.h>

int no_attack(int *tab, int col, int row)
{
    int pre_col;
    int pre_row;

    pre_col = 0;
    while (pre_col < col)
    {
        pre_row = tab[pre_col];
        if (pre_row == row || row - pre_row == col - pre_col || pre_row - row == col - pre_col)
            return (0);
        pre_col++;
    }
    return (1);
}

void print_tab(int *tab, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        printf("%d ",tab[i]);
        i++;
    }
    printf("\n");
}

void backtracking (int *tab, int n, int col, int *nb_solution)
{
    if (col == n)
    {
        print_tab(tab, n);
        (*nb_solution)++;
      
        return ;
    }


    int row;
    
    row = 0;
   
    while (row < n)
    {
       
        if (no_attack(tab, col, row))
        {
             tab[col] = row;
            backtracking(tab, n,  col + 1, nb_solution);
        }
        
        row++;
    }
}

int main(void)
{
    int n;
    n = 10;
    int tab[n];
    int nb_solution = 0;

    backtracking(tab, n,  0, &nb_solution);
    //printf("%d\n", nb_solution);
    puts("hello");
    return (0);
}
