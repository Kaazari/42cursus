#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	printf("match_space used\n");
	int c;
	while (isspace(c = fgetc(f)))
		;
	if (c == EOF)
		return (-1);
	else
	{
		ungetc(c, f);
		return (1);
	}
	return (0);
}

int match_char(FILE *f, char c)
{
	printf("match_char used\n");
	int r = fgetc(f);
	if (r == c)
		return (1);
	else if (r == EOF)
		return (-1);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	printf("scan_char used\n");
	int c = fgetc(f);
	if (c == EOF)
		return (-1);
	c = va_arg(ap, int);
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	printf("scan_int used\n");
	int c;
	int num = 1;
	int sign = 1;
	if ((c = fgetc(f)) == '-')
		sign = -1;
	else if ((c = fgetc(f)) == '+')
		sign = 1;
	if (c == EOF)
		return (-1);
	ungetc(c, f);
	while (isdigit(c = fgetc(f)) && c != EOF)
		num = num * 10 + c;
	ungetc(c, f);
	num = num * sign;
	num = va_arg(ap, int);
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	printf("scan_string used\n");
	int c = fgetc(f);
	char *s;
	int i = 0;
	if (c == EOF)
		return(-1);
	ungetc(c, f);
	s = va_arg(ap, char *);
	while (!isspace(c = fgetc(f)) && c != EOF)
	{
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	if (i == 0)
		return (0);
	if (c == EOF)
		return(-1);
	ungetc(c, f);
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
	// scanf("%d %s %c", &age, name, &initial);
	printf("Age: %d\n", age);
	printf("Name: %s\n", name);
	printf("Initial: %c\n", initial);
	return (0);
}
