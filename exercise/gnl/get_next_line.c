#include <stdlib.h>
#include <unistd.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

# endif

int ft_strlen(char *s)
{
    int len;

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
    char *copied;
    int i;
    int len;

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
    int i;
    int j;
    char *joined;

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
    char *line;
    int i;
    int j;
    
    i = 0;
    j = 0;
    if (!s)
        return (NULL);
    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    line = malloc (i + 1);
    if (!line)
        return (NULL);
    while (j < i)
    {
        line[j] = s[j];
        j++;
    }
    line[j] = '\0';
    return (line);
}

void reset_stash(char **stash)
{
    if (*stash)
        free(stash);
    *stash = NULL;
}

char *read_and_stash(int fd, char *buffer, char *stash)
{
    char *tmp;
    int bytes_read;

    bytes_read = 1;
    while (bytes_read > 0 && (!stash || !end_line(stash)))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == 0)
            break;
        if (bytes_read < 0)
            return (reset_stash(&stash), NULL);
        buffer[bytes_read] = '\0';
        tmp = stash;
        if (!stash || stash[0] == '\0')
            stash = ft_strdup(buffer);
        else
            stash = ft_strjoin(stash, buffer);
        free(tmp);
    }
    return (stash);
}

char *extract_and_update(char **stash)
{
    char *line;
    char *next;
    char *tmp;

    if (!*stash)
        return (NULL);
    line = extract_line(*stash);
    next = *stash + ft_strlen(line);
    tmp = *stash;
    if (*next == '\0')
        *stash = NULL;
    else
        *stash = ft_strdup(next);
    free(tmp);
    return (line);
}

char *get_next_line(int fd)
{
    char *line;
    static char *stash = NULL;
    char *buffer;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc (BUFFER_SIZE + 1);
    if (!buffer)
        return (reset_stash(&stash), NULL);
    stash = read_and_stash(fd, buffer, stash);
    free(buffer);
    line = extract_and_update(&stash);
    return (line);
}

/*#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("text.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    return (0);

}*/