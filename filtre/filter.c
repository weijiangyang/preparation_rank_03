#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 21

#endif

int ft_strncmp(char *s1, char *s2, int n)
{
    int i;

    i = 0;
    while (i < n && s1[i]&& s2[i] && s1[i] == s2[i])
        i++;
    if (i == n)
        return (0);
    else
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *filter(char *word)
{
    int s_word;
    char *input;
    char *buffer;
    int bytes_read;
    int size_total;

    size_total = 0;
    s_word = strlen(word);
    input = malloc(1);
    if (!input)
        return NULL;
    buffer = malloc (BUFFER_SIZE);
    if(!buffer)
        return NULL;
    
    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        char *tmp = realloc(input, size_total + bytes_read + 1);
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
        free(buffer);
        size_total += i;
    }
    input[size_total] = '\0';
    char *ptr = input;
    while (*ptr)
    {
        if (strncmp(ptr, word, s_word) == 0)
        {
            int i = 0;
            while (i < s_word)
            {
                *ptr = '*';
                i++;
                ptr++;
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
    {
        fprintf(stderr, "Error: argument error\n");
        return 1;
    }

    char *line = filter(av[1]);
    printf("%s", line);
    return (0);
}