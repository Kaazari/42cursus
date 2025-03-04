#include <stdlib.h>

// 32, 10, 9, \0

char	**ft_split(char *str)
{
	if (!str)
		return (NULL);
	int i = 0;
	int j = 0;
	int k = 0;
	char **split = (char **)malloc(sizeof(char *) * 256);
	if (!split)
		return (NULL);
	while (str[i] == 32 || str[i] == 10 || str[i] == 9)
			i++;
	while (str[i])
	{
		k = 0;
		split[j] = (char *)malloc(sizeof(char) * 4096);
		if (!split[j])
			return (NULL);
		while (str[i] != 32 && str[i] != 10 && str[i] != 9 && str[i])
		{
			split[j][k] = str[i];
			i++;
			k++;
		}
		while ((str[i] == 32 || str[i] == 10 || str[i] == 9) && str[i])
			i++;
		split[j][k] = '\0';
		j++;
	}
	split[j] = '\0';
	return (split);
}
