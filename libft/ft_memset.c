/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:49:02 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 13:37:41 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	size_t	i;
	char	*ret;

	ret = dest;
	i = 0;
	while (i < len)
	{
		ret[i] = (unsigned char) c;
		i++;
	}
	return (dest);
}
