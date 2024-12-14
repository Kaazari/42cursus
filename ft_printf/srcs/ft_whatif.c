/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whatif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:52:17 by zdjitte           #+#    #+#             */
/*   Updated: 2024/09/12 19:52:21 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
#include "include/libft.h"

int	ft_putunbr(unsigned int i)
{
	unsigned long	ui;
	int				count;

	ui = i;
	count = 0;
	while (i != 0)
	{
		i = i / 10;
		count++;
	}
	if (ui == 0)
	{
		ft_printchar('0');
		return (1);
	}
	else if (ui <= 9)
		ft_printchar((ui + 48));
	else
	{
		ft_putunbr(ui / 10);
		ft_putunbr(ui % 10);
	}
	return (count);
}

int	if_s(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	if_p(unsigned long long ptr)
{
	return (ft_ptr(ptr));
}

int	if_d(int i)
{
	int		count;
	char	*y;

	y = ft_itoa(i);
	count = if_s(y);
	free(y);
	return (count);
}

int	if_x(unsigned int hex, char c)
{
	char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	return (ft_puthexa(hex, base));
}
