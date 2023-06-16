/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:42:35 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 15:05:30 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	if (dst < src)
	{
		while (i < (int) len)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i >= 0)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i--;
		}
	}
	((char *) dst)[i] = '\0';
	return (dst);
}

void	clear_last(t_last **lasts, int fd)
{
	t_last	*tmp;
	t_last	*clear;

	if (!*lasts)
		return ;
	clear = *lasts;
	tmp = NULL;
	while (clear->fd != fd && clear->next)
	{
		tmp = clear;
		clear = clear->next;
	}
	if (clear->fd == fd)
	{
		if (clear == *lasts)
			*lasts = clear->next;
		if (tmp)
			tmp->next = clear->next;
		free(clear);
	}
}
