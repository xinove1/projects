/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:48:49 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 13:37:45 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t	i;

	i = 0;
	if (!len)
		return (0);
	while (i < len && ((char *) b1)[i] == ((char *) b2)[i])
		i++;
	if (i == len)
		i--;
	return ((unsigned char)((char *) b1)[i] - (unsigned char)((char *) b2)[i]);
}
