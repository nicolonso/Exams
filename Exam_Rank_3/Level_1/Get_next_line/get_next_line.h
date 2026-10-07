#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Libraries 

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char *get_next_line(int fd);

# endif
