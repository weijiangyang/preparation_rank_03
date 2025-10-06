/*filter:
Allowed functions: read, strlen, malloc, calloc, realloc, free, printf, perror
------------------------------------------------------------------------------

Write a programm taht will take one and only one argument s.

Your programm will then read from stdin and write all the content read in stdout
except that every occurence of s must be replaced by '*'.

For example :

./filter bonjour
will behave the same way as:


in case of error during read or a malloc you must write "Error: " followed by
the error message in stderr and return 1.

$> echo 'abcdefgaaaabcdefabc' | ./filter abc | cat -e
***defgaaa***def***

If the program is called whitout argument or with an empty argument or with
multiples arguments it must return 1.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 21

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
    char *input;
    int bytes_read;
    char *buffer;
    int size_total;

    size_total = 0;
    if (!word)
        return NULL;
    s_word = strlen(word);
    input = malloc(1);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    if (!input)
        return (NULL);
    while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        char *tmp = input;
        tmp = realloc(input, size_total + bytes_read + 1);
        if (!tmp)
        {
            free(input);
            free(buffer);
            return (NULL);
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
    if (ac < 2 || !av[1])
    {
        fprintf(stderr, "Usage: %s <word>\n", av[0]);
        return 1;
    }

    char *word = av[1];
    char *line = filter(word);
    printf("%s", line);
    return (0);
}
