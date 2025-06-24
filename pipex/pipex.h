#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_data
{
	int		fd;
	int		fd2;
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
	char	*readed;
}	t_data;

#endif
