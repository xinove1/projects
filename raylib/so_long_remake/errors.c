/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:38:36 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/16 12:16:26 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	parser_error_handler(int error, t_game *game, void *ptr)
{
	ft_putstr_fd("Error\n", 2);
	if (error == 1)
		ft_putstr_fd("The map dosen't have a rectangular shape.\n", 2);
	else if (error == 2)
		ft_putstr_fd("Walls don't cover all the outer map.\n", 2);
	else if (error == 3)
		ft_putstr_fd("Empty map file.\n", 2);
	else if (error == 4)
		perror("");
	else if (error == 5)
		ft_putstr_fd("Map must have at least one exit, one collectible, "
			"and one starting position.\n", 2);
	else if (error == 6)
		ft_putstr_fd("Can't create a game without a map.\n", 2);
	else if (error == 7)
		ft_putstr_fd("Too many args.\n", 2);
	else if (error == 8)
		ft_putstr_fd("Unknow object on map.\n", 2);
	clean(game, ptr);
	exit(1);
}
