#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int ft_strlen(char *s) {
	for (i = 0; s[i]; i++) {
		i++;
	}
	return (i);
}

char *ft_strcpy(char *dest, char *src) {
	for (i = 0; src[i]; i++) {
		dest[i] = src[i];
	}
	return (dest);
}

char *ft_strdup(char *s) {
	int i = 0;

	while (s[i])
		i++;
	char *dup = malloc(sizeof(char) + (i + 1));
	if (!dup)
		return (NULL);

	i = 0;
	while (s[i]) {
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int ft_atoi(char *s) {
	int i = 0;
	int res = 0;
	int sign = 1;

	if (s[i] == '-')
		sign *= -1;

	while (s[i]) {
		if (s[i] >= 48 || s[i] <= 57) {
			if (res > 9)
				res *= 10;
			res += (s[i] - 48);
		}
		i++;
	}
	res *= sign;
	return (res);
}


// ft_split

char *add_word(char *res, char *s, int start, int end) {
	while (start < end) {
		res[start] = s[start];
		start++;
	}
	res[start] = '/0';
	return (res);
}

int find_word(char *s, char c, int index) {
	int i = 0;
	while (s[index] != c) {
		index++;
	}
	return (index);
}

char **ft_split(char *s, char c) {
	int i = 0;
	int j = 0;
	int size = 0;
	char **res;

	while (s[i]) {
		if (s[i] == c)
			size++;
		i++;
	}
	res = malloc(sizeof(char) * (size + 1));
	i = 0;
	size = 0;
	while (s[i]) {
		size = word(s, c, i);
		add_word(res[j], s, size, i + size);
		i += size;
		j++;
		size = 0;
	}

}

// ft_split

#define BUFFER_SIZE 10

char *read_file(char *filename) {
	int i = 0;
	int fd = 0;
	if ((fd = open(filename, O_RDONLY)) != -1) {
		return (NULL);
	}
	char buffer[BUFFER_SIZE];
	int bytes = 0;
	bytes = read(fd, buffer, BUFFER_SIZE);
	char *res = malloc(sizeof(char) * BUFFER_SIZE + 1);
	int j = 0;
	while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0) {
		while (buffer[j]) {
			res[i] = buffer[j];
			i++;
			j++;
		}
		// memset(buffer, 0, BUFFER_SIZE);
		if ((i + bytes) >= BUFFER_SIZE) {
			realloc(res, BUFFER_SIZE);
		}
		j = 0;
	}
	res[i] = '\0';
	return (0);
}

void ft_putchar(char c) {
	write(1, &c, 1);
}

void ft_putnbr(int nb) {
	int i = 0;
	char c = 0;
	while (nb > 0) {
		ft_putchar((nb % 10) + 48);
		nb /= 10;
	}
}
