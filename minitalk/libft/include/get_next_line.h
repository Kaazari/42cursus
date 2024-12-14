/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:06:20 by zdjitte           #+#    #+#             */
/*   Updated: 2024/03/26 12:31:12 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// # include <fcnt1.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);

char	*ft_strchr(char *s, int chr);

char	*ft_strdup(char *s1);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_fornext(char *stash);

char	*ft_finale(int fd, char *stash);

int		ft_strlen(char *s);

#endif
