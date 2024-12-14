/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdjitte <zdjitte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:18:35 by zdjitte           #+#    #+#             */
/*   Updated: 2024/03/26 12:30:56 by zdjitte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

// # include <fcnt1.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef FD_MAX
#  define FD_MAX 4096
# endif

char	*get_next_line(int fd);

char	*ft_strchr(char *s, int chr);

char	*ft_strdup(char *s1);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_fornext(char *stash);

char	*ft_finale(int fd, char *stash);

int		ft_strlen(char *s);

#endif
