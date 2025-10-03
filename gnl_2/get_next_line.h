#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char * get_next_line(int fd);
int ft_strlen(char *s);
int end_line(char *s);
char *ft_strdup(char *s);
char *ft_strjoin(char *s1, char *s2);
char *extract_line(char *s);

#endif
