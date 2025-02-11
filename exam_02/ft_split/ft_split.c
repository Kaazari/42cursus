#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char **ft_split(char *str)
{
	if (!str)
		return (NULL);
	char **words;

	int i = 0;
	int j = 0;
	int k = 0;
	while (str[i])
	{
		i++;
	}
	i++;
	words = (char **)malloc(sizeof(char *) * 256);
	if (!words)
		return (NULL);
	i = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
			i++;
	while (str[i])
	{
		k = 0;
		words[j] = (char *)malloc(sizeof(char) * 4096);
		if (!words[j])
			return (NULL);
		while (str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
		{
			words[j][k] = str[i];
			i++;
			k++;
		}
		while (str[i] && (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' || str[i] == '\0'))
			i++;
		words[j][k] = '\0';
		j++;
	}
	words[j] = '\0';
	return (words);
}

// int main(void)
// {
// 	char **words = ft_split("La terre est	ronde");
// 	int i = 0;
// 	int j;
// 	while (words[i])
// 	{
// 		printf("%s", words[i]);
// 		printf("\n");
// 		i++;
// 	}

// }
