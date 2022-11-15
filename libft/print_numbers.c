/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:32:39 by nthomas-          #+#    #+#             */
/*   Updated: 2022/03/24 13:17:33 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(va_list args, int lower)
{
	int		i;
	char	*str;

	if (lower == 1)
		str = ft_itoa_hex(va_arg(args, unsigned int), 1);
	else
		str = ft_itoa_hex(va_arg(args, unsigned int), 0);
	i = ft_strlen(str);
	write(1, str, i);
	free(str);
	return (i);
}

int	print_p(va_list args)
{
	int				count;
	unsigned long	n;
	char			*str;

	n = va_arg(args, unsigned long);
	str = ft_itoa_hex(n, 1);
	if (!IS_MACOS && n == 0)
	{
		write(1, "(nil)", 5);
		count = 5;
	}
	else
	{
		write(1, "0x", 2);
		count = ft_strlen(str);
		write(1, str, count);
		count += 2;
	}
	free(str);
	return (count);
}

int	print_numbers(va_list args, int unsigned_number)
{
	int		count;
	char	*str;

	count = 0;
	if (unsigned_number)
		str = ft_itoa_unsigned(va_arg(args, unsigned int));
	else
		str = ft_itoa(va_arg(args, int));
	while (str[count])
	{
		write(1, &str[count], 1);
		count++;
	}
	free(str);
	return (count);
}
