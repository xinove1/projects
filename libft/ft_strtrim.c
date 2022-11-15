/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:49:40 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 13:37:15 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char c, char const *set, int set_size);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		beg;
	int		set_size;

	set_size = ft_strlen(set);
	i = 0;
	while (to_trim(s1[i], set, set_size))
		i++;
	beg = i;
	i = ft_strlen(s1) - 1;
	while (i && to_trim(s1[i], set, set_size))
		i--;
	if (beg > i)
	{
		trim = malloc(1);
		trim[0] = '\0';
	}
	else
		trim = ft_substr(s1, beg, i - beg + 1);
	return (trim);
}

static int	to_trim(char c, char const *set, int set_size)
{
	int	i;

	i = 0;
	while (i < set_size)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
