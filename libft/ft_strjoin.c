/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:49:22 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 13:37:31 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = malloc(i + j + 1);
	if (join == 0)
		return (join);
	ft_memcpy(join, s1, i);
	ft_memcpy(&join[i], s2, j);
	join[j + i] = '\0';
	return (join);
}
