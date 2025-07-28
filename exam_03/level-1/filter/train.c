#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void	filter(char *del)
{
	int i = 0;
	int j = 0;
	int mark = 0;
	char buf[4096];
	int readed = 0;
	readed = read(0, buf, sizeof(buf) - 1);
	if (readed <= 0)
	{
		perror("Error: ");
		return ;
	}
	buf[readed] = '\0';
	int len = ft_strlen(del);
	while (buf[i])
	{
		j = 0;
		mark = i;
		if (buf[i] == del[j])
		{
			while ((buf[i] == del[j]) && buf[i] && del[j])
			{
				i++;
				j++;
			}
			if (len == j)
			{
				j = 0;
				while (j++ < len)
					printf("*");
				i--;
			}
			else
			{
				i = mark;
				printf("%c", buf[i]);
			}
		}
		else
			printf("%c", buf[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		while (1)
			filter(av[1]);
	}
}
