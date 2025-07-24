#ifndef GET_NEXT_LINE_SAFE_H
# define GET_NEXT_LINE_SAFE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);

#endif
