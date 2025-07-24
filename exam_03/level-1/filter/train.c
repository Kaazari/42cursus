#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	replace_c(char c, char *s)
{
		int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			printf("*");
		else
			printf("%c", s[i]);
		i++;
	}
}

void	replace_str(char *str, char *s)
{
	int i = 0;
	if (str[i + 1] == '\0')
	{
		replace_c(str[i], s);
		return ;
	}
	int j;
	while (s[i])
	{
		j = 0;
		while ((str[j] && s[i]) && s[i] == str[j])
		{
			i++;
			j++;
		}
		if (str[j] == '\0')
		{
			while (j > 0)
			{
				printf("*");
				j--;
			}
			i = i - 1; // Reculer d'un caractère car on va incrémenter après
		}
		else
		{
			i = i - j;
			printf("%c", s[i]);
		}
		i++;
	}
	// printf("\n");	
}

int	main(int ac, char **av)
{
	int i = 0;

	if (ac == 2)
	{
		while (1)
		{
			char *s = malloc(1024);
			if (!s)
				return (1);
			int bytes = read(STDIN_FILENO, s, 1023);
			if (bytes <= 0)
				return (1);
			s[bytes] = '\0';
			replace_str(av[1], s);
			free(s);
			bytes = 0;
		}
		return (0);
	}
	return (1);
}
