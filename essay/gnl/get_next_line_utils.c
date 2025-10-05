#include "get_next_line.h"

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return (len);
}

int end_line(char *s)
{
    if (!s)
        return (0);
    while (*s)
    {
        if (*s == '\n')
            return (1);
        s++;
    }
    return (0);
}

char *ft_strdup(char *s)
{
    int i;
    int len;
    char *copied;

    i = 0;
    len = ft_strlen(s);
    copied = malloc (len + 1);
    if (!copied)
        return (NULL);
    while (i < len)
    {
        copied[i] = s[i];
        i++;
    }
    copied[i] = '\0';
    return (copied);
}

char *ft_strjoin(char *s1, char *s2)
{
    if (!s1)
        s1 = "";
    if (!s2)
        s2 = "";
    int i = 0;
    int j = 0;
    char *joined;

    joined = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!joined)
        return (NULL);
    while (s1[i])
    {
        joined[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        joined[i + j] = s2[j];
        j++;
    }
    joined[i + j] = '\0';
    return (joined);
}

char *extract_line(char *str)
{
    int i;
    int j;
    char *line;

    i = 0;
    j = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        i++;
    line = malloc (i + 1);
    if (!line)
        return NULL;
    while (j < i)
    {
        line[j] = str[j];
        j++;
    }
    line[j] = '\0';
    return (line);

}