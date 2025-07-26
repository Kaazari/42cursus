#ifndef X_H
# define X_X
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

#endif

char	*ft_strdup(char *str)
{
	char *copy;
	int i = 0;

	while (str[i])
		i++;
	copy = malloc(sizeof(char) * i + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*get_next_line(int fd)
{
	char line[70000];
	static char buf[BUFFER_SIZE + 1];
	static int i = 0;
	static int b_pos = 0;
	static int readed = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (357)
	{
		if (b_pos == readed)
		{
			readed = read(fd, buf, BUFFER_SIZE);
			if (readed <= 0)
				break ;
			buf[readed] = '\0';
			b_pos = 0;
		}
		line[i++] = buf[b_pos++];
		if (buf[b_pos - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	i = 0;
	return (ft_strdup(line));
}

int main(int ac, char **av)
{
	int fd = open(av[1], O_RDONLY);
	char *line;
	int i = 0;
	while (i < 8)
	{
		i++;
		line = get_next_line(fd);
		printf("%s", line);
	}
	return (0);
}
