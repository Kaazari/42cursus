#include "get_next_line.h"

static int	ft_strlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2, int len)
{
	char	*result;
	int		i, j;

	if (!s1)
	{
		result = malloc(len + 1);
		if (!result)
			return (NULL);
		i = 0;
		while (i < len)
		{
			result[i] = s2[i];
			i++;
		}
		result[i] = '\0';
		return (result);
	}
	result = malloc(ft_strlen(s1) + len + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static int	p = 0, r = 0;
	char		*line = NULL;
	int			i, n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

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
			line = ft_strjoin(line, buf + p, n - p + 1);
			if (!line)
				return (NULL);
			p = n + 1;
			break;
		}
		line = ft_strjoin(line, buf + p, r - p);
		if (!line)
			return (NULL);
		p = r;
	}

	return (line);
}
