/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:47:52 by nthomas-          #+#    #+#             */
/*   Updated: 2022/03/25 09:21:22 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_str(const char *str, int *negative);
int			ft_isspace(char c);

int	ft_atoi(const char *str)
{
	int	number;
	int	i;
	int	flag;

	number = 0;
	flag = 0;
	i = parse_str(str, &flag);
	if (i < 0)
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		number = (str[i] - '0') + (number * 10);
		i++;
	}
	if (flag)
		number *= -1;
	return (number);
}

static int	parse_str(const char *str, int *negative)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (flag == 0 && ft_isspace(str[i]))
			;
		else if (flag == 0 && (str[i] == '-' || str[i] == '+'))
		{
			if (str[i] == '-')
				*negative = 1;
			flag = 1;
		}
		else if (!(str[i] >= '0' && str[i] <= '9'))
		{
			i = -1;
			break ;
		}
		else if (str[i] >= '0' && str[i] <= '9')
			break ;
		i++;
	}
	return (i);
}

int	ft_isspace(char c)
{
	if (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}
