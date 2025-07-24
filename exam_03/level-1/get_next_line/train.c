#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);

#endif

char	*ft_strdup(char *s)
{
	char *cpy;
	int i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	cpy = malloc(sizeof(char) * i + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*get_next_line(int fd)
{
	static int pos = 0;
	static int readed = 0;
	static char buf[BUFFER_SIZE];
	char line[80000];
	int i = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		if (pos >= readed)
		{
			readed = read(fd, buf, BUFFER_SIZE);
			pos = 0;
		}
		if (readed <= 0)
		{
			readed = 0;
			break ;
		}
		line[i++] = buf[pos++];
		if (buf[pos - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
