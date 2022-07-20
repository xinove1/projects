/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:38:00 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/14 20:15:43 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean(t_game *game, void *ptr)
{
	if (ptr)
		free(ptr);
	if (game->map)
		clean_map(game->map);
	if (game->players_p)
		free(game->players_p);
}

int	exit_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 6)
		UnloadTexture(game->tiles[i]);
	clean(game, NULL);
	exit(0);
}

void	clean_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}
