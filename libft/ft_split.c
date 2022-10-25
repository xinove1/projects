/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:49:12 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 13:40:39 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_d(char const *str, char d);

static size_t	find_next_d(char const *str, size_t i, int flag, char d);

char	**ft_split(char const *s, char c)
{
	char	**splited;
	size_t	i;
	size_t	beg_end[2];
	size_t	d_count;

	d_count = count_d(s, c);
	splited = malloc((d_count + 1) * sizeof(char *));
	if (splited == 0)
		return (0);
	i = 0;
	beg_end[0] = 0;
	while (i < d_count)
	{
		beg_end[1] = find_next_d(s, beg_end[0], 0, c);
		if (!beg_end[0] && s[beg_end[0]] == c)
		{
			beg_end[0] = find_next_d(s, beg_end[0], 1, c) + 1;
			continue ;
		}
		splited[i] = ft_substr(s, beg_end[0], beg_end[1] - beg_end[0]);
		beg_end[0] = find_next_d(s, beg_end[0], 1, c) + 1;
		i++;
	}
	splited[i] = NULL;
	return (splited);
}

static size_t	find_next_d(char const *str, size_t i, int flag, char d)
{
	while (str[i])
	{
		if (flag == 0 && str[i] == d && i)
			return (i);
		else if (str[i] == d && str[i + 1] != d)
			return (i);
		i++;
	}
	return (i);
}

static	size_t	count_d(char const *str, char d)
{
	int		i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i + 1] == d || str[i + 1] == '\0') == 1)
			if ((str[i] == d || str[i] == '\0') == 0)
				count++;
		i++;
	}
	return (count);
}
