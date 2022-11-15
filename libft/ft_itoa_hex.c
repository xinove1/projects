/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:32:02 by nthomas-          #+#    #+#             */
/*   Updated: 2022/03/24 13:17:44 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_hex(unsigned long n);
static void		populate_result(unsigned long n, int i, char *str, int lower);

char	*ft_itoa_hex(unsigned long n, int lower)
{
	int				i;
	char			*result;

	result = malloc(count_hex(n) + 1);
	if (!result)
		return (NULL);
	i = count_hex(n) - 1;
	result[i + 1] = '\0';
	if (!n)
		result[i] = '0';
	populate_result(n, i, result, lower);
	return (result);
}

static void	populate_result(unsigned long n, int i, char *str, int lower)
{
	while (n && str)
	{
		if (n % 16 > 9)
		{
			if (lower)
				str[i] = (n % 16) + 87;
			else
				str[i] = (n % 16) + 55;
		}
		else
			str[i] = (n % 16) + '0';
		n /= 16;
		i--;
	}
}

static size_t	count_hex(unsigned long n)
{
	size_t	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}
