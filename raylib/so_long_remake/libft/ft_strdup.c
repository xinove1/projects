/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:49:18 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 13:37:33 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;

	cpy = malloc(ft_strlen(str) + 1);
	if (cpy == 0)
		return (cpy);
	ft_strlcpy(cpy, str, ft_strlen(str) + 1);
	return (cpy);
}
