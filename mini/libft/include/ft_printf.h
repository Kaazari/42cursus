/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:18:08 by zdjitte           #+#    #+#             */
/*   Updated: 2024/03/19 19:50:52 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int		ft_ptrlen(unsigned long long num);

void	ft_putptr(unsigned long long num);

int		ft_ptr(unsigned long long ptr);

int		ft_check_conv(va_list args, const char c);

int		ft_printf(const char *s, ...);

int		ft_putunbr(unsigned int i);

int		ft_puthexa(unsigned int i, char *base);

int		ft_printchar(char c);

void	ft_putstr(char *str);

int		if_s(char *s);

int		if_p(unsigned long long ptr);

int		if_d(int i);

int		if_x(unsigned int hex, char c);

#endif
