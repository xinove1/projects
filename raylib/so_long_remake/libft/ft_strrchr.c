/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:49:38 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 14:00:45 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;

	last = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			last = (char *) &s[i];
		i++;
	}
	if (c == '\0')
		return ((char *) &s[i]);
	return (last);
}
