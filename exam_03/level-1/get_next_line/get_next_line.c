#include "get_next_line.h"

static int	ft_strlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static void	ft_strcpy(char *dst, char *src)
{
	int i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

static void	ft_strncpy(char *dst, char *src, int n)
{
	int i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static int	p = 0, r = 0;
	char		*line = NULL;
	int			i, n;

	while (1)
	{
		if (p >= r)
		{
			r = read(fd, buf, BUFFER_SIZE);
			if (r <= 0)
				break;
			p = 0;
		}
		i = p;
		n = -1;
		while (i < r)
		{
			if (buf[i] == '\n')
			{
				n = i;
				break;
			}
			i++;
		}
		if (n != -1)
		{
			char *tmp = malloc(ft_strlen(line) + n - p + 2);
			if (line)
				ft_strcpy(tmp, line);
			ft_strncpy(tmp + ft_strlen(line), buf + p, n - p + 1);
			tmp[ft_strlen(line) + n - p + 1] = 0;
			free(line);
			line = tmp;
			p = n + 1;
			break;
		}
		char *tmp = malloc(ft_strlen(line) + r - p + 1);
		if (line)
			ft_strcpy(tmp, line);
		ft_strncpy(tmp + ft_strlen(line), buf + p, r - p);
		tmp[ft_strlen(line) + r - p] = 0;
		free(line);
		line = tmp;
		p = r;
	}
	return (line);
}
