/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:32:35 by nthomas-          #+#    #+#             */
/*   Updated: 2022/03/24 13:17:24 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_c(va_list args)
{
	char	c;

	c = va_arg(args, int);
	write(1, &c, 1);
	return (1);
}

int	print_string(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (str)
	{
		write(1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
	write(1, "(null)", 6);
	return (6);
}
