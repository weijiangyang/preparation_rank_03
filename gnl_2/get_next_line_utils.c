#include "get_next_line.h"

int ft_strlen(char *s)
{
    int len;

    if (!s)
        return (0);
    len = 0;
    while (*s)
    {
        len++;
        s++;
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
    char *copy;

    i = 0;
    if (!s)
        return (NULL);
    copy = malloc (ft_strlen(s) + 1);
    if (!copy)
        return (NULL);
    while (i < ft_strlen(s))
    {
        copy[i] = s[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}

char *ft_strjoin(char *s1, char *s2)
{
    int i;
    int j;
    char *joined;

    if (!s1)
        s1 = "";
    if (!s2)
        s2 = "";
    i = 0;
    j = 0;
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

char *extract_line(char *s)
{
    int i;
    int j;
    char *extracted;

    i = 0;
    j = 0;
    if (!s || s[0] == '\0') // n'oublie pas
        return (NULL);
    while (s[i] && s[i] != '\n') // ne confond pas avec '\0'
        i++;
    if (s[i] == '\n')
        i++;
    extracted = malloc (i + 1);
    if (!extracted)
        return (NULL);
    while (j < i)
    {
        extracted[j] = s[j];
        j++;
    }
    extracted[j] = '\0';
    return (extracted);
}
