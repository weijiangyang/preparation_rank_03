#include "get_next_line.h"

void reset_stash(char **stash)
{
    if (*stash)
        free(*stash);
    *stash = NULL;
}

char *read_and_stash(int fd, char *buffer, char *stash)
{
    int bytes_read;
    char *tmp;

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
        return  (NULL);
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
    char *buffer;
    char *line;
    static char *stash;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = malloc (BUFFER_SIZE + 1);
    if(!buffer)
        return (reset_stash(&stash), NULL);
    stash = read_and_stash(fd, buffer, stash);
    free(buffer);
    line = extract_and_update(&stash);
    return (line);
}

int main(void)
{
    int fd;

    fd = open("text.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    return (0);
}