/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:52:07 by zdjitte           #+#    #+#             */
/*   Updated: 2024/09/12 19:52:10 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_ptrlen(unsigned long long num)
{
	int	i;

	i = 0;
	while (num != 0)
	{
		num = num / 16;
		i++;
	}
	return (i);
}

void	ft_putptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_putptr(num / 16);
		ft_putptr(num % 16);
	}
	else
		if (num <= 9)
			ft_printchar((num + '0'));
	else
		ft_printchar((num - 10 + 'a'));
}

int	ft_ptr(unsigned long long ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		return (i += write(1, "(nil)", 5));
	i += write(1, "0x", 2);
	if (ptr)
	{
		ft_putptr(ptr);
		i += ft_ptrlen(ptr);
	}
	return (i);
}
