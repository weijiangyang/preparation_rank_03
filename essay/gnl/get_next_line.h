#ifndef GET_NEXT_LINE_H
#   define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 21

#endif

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char *get_next_line(int fd);
int ft_strlen(char *str);
int end_line(char *s);
char *ft_strdup(char *s);
char *ft_strjoin(char *s1, char *s2);
char *extract_line(char *str);

#endif