/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:51:48 by zdjitte           #+#    #+#             */
/*   Updated: 2024/09/12 19:51:55 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_puthexa(unsigned int i, char *base)
{
	int				count;
	unsigned int	y;

	count = 0;
	y = i;
	while (y != 0)
	{
		y = y / 16;
		count++;
	}
	if (i == 0)
		return (ft_printchar('0'));
	else if (i <= 15)
		ft_printchar(base[i]);
	else
	{
		ft_puthexa((i / 16), base);
		ft_puthexa((i % 16), base);
	}
	return (count);
}

int	ft_check_conv(va_list args, const char c)
{
	int	counter;

	counter = 0;
	if (c == 'c')
		counter += ft_printchar(va_arg(args, int));
	else if (c == 's')
		counter += if_s(va_arg(args, char *));
	else if (c == 'p')
		return (if_p(va_arg(args, unsigned long long)));
	else if (c == 'd' || c == 'i')
		return (if_d(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (if_x(va_arg(args, unsigned int), c));
	else if (c == '%')
		return (ft_printchar('%'));
	return (counter);
}

int	ft_printf(const char *s, ...)
{
	unsigned int	i;
	va_list			args;
	unsigned long	display;

	display = 0;
	if (!s)
		return (display);
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			display += ft_check_conv(args, s[i + 1]);
			i++;
		}
		else
			display += ft_printchar(s[i]);
		i++;
	}
	va_end(args);
	return (display);
}
