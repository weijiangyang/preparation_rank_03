#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024

#endif

int ft_strncmp(char *s1, char *s2, int n)
{
    int i;

    i = 0;
    while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (i == n)
        return (0);
    else
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *filter(char *word)
{
    int s_word;
    char *buffer;
    char *input;
    int bytes_read;
    int size_total;

    s_word = strlen(word);
    buffer = malloc (BUFFER_SIZE);
    input = malloc (1);
    size_total = 0;
    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        char *tmp;
        tmp = realloc(input, bytes_read + 1);
        if (!tmp)
        {
            free(input);
            free(buffer);
            return NULL;
        }
        input = tmp;
        int i = 0;
        while (i < bytes_read)
        {
            input[size_total + i] = buffer[i];
            i++;
        }
        size_total += bytes_read;
    }
    input[size_total] = '\0';
    char *ptr = input;
    while (*ptr)
    {
        if (ft_strncmp(ptr, word, s_word) == 0)
        {
            int j = 0;
            while (j < s_word)
            {
                *ptr = '*';
                ptr++;
                j++;
            }
        }
        else
            ptr++;
    }
    return (input);    
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (stderr, printf("Error:argument error"), 1);
    char *result = filter(av[1]);
    printf("%s", result);
    return (0);
}