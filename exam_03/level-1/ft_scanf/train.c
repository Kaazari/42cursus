#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int c;
	int found = 0;

	while ((c = fgetc(f)) != EOF && isspace(c))
	{
		found = 1;
	}
	if (c != EOF)
		ungetc(c, f);
	if (found)
		return (1);
	else
	 	return (-1);
}

int match_char(FILE *f, char c)
{
	int actual = fgetc(f);
	if (c == actual)
		return (1);
	else
	{
		if (actual != EOF)
			ungetc(actual, f);
		return (-1);
	}
}

int scan_char(FILE *f, va_list ap)
{
	char *ptr = va_arg(ap, char *);
	int c = fgetc(f);
	if (c == EOF)
		return (-1);
	*ptr = c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int *ptr = va_arg(ap, int *);
	int val = 0;
	int sign = 1;
	int c;
	int digits_read = 0;

	// Ignorer les espaces
	while ((c = fgetc(f)) != EOF && isspace(c))
		;

	// Gérer le signe
	if (c == '-') {
		sign = -1;
		c = fgetc(f);
	} else if (c == '+') {
		c = fgetc(f);
	}

	// Lire les chiffres
	while (c != EOF && isdigit(c))
	{
		val = val * 10 + (c - '0');
		c = fgetc(f);
		digits_read = 1;  // Au moins un chiffre lu
	}

	if (!digits_read) {
		if (c != EOF)
			ungetc(c, f);
		return -1;  // Aucun chiffre lu = échec
	}

	if (c != EOF)
		ungetc(c, f);
	*ptr = val * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char *ptr = va_arg(ap, char *);
	int c;
	int i = 0;

	while ((c = fgetc(f)) != EOF && !isspace(c))
	{
		ptr[i++] = c;
	}

	if (i == 0) {
		if (c != EOF)
			ungetc(c, f);
		ptr[0] = '\0';
		return -1;  // Aucun caractère lu = échec
	}

	if (c != EOF)
		ungetc(c, f);
	ptr[i] = '\0';  // Terminer la chaîne
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main(int argc, char **argv)
{
	int age;
	char name[100];
	char initial;
	ft_scanf("%d %s %c", &age, name, &initial);
	printf("Age: %d\n", age);
	printf("Name: %s\n", name);
	printf("Initial: %c\n", initial);
	return (0);
}
