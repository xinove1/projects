/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:38:54 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/16 12:15:58 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	parse_map(t_game *game, char *map_path)
{
	game->map_size = get_map_size(map_path, game);
	get_map(game, map_path);
	check_walls(game);
	parse_inner_map(game);
	parse_players_position(game);
}

void	parse_inner_map(t_game *game)
{
	int	x;
	int	y;
	int	exits;

	y = 1;
	exits = 0;
	while (y < game->map_size.y - 1)
	{
		x = 1;
		while (x < game->map_size.x - 1)
		{
			if (game->map[y][x] == 'C')
				game->collectables++;
			else if (game->map[y][x] == 'P')
				game->players++;
			else if (game->map[y][x] == 'E')
				exits++;
			else if (game->map[y][x] != '0' && game->map[y][x] != '1')
				parser_error_handler(8, game, NULL);
			x++;
		}
		y++;
	}
	if (game->collectables == 0 || game->players == 0 || exits == 0)
		parser_error_handler(5, game, NULL);
}

void	check_walls(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map_size.y)
		if (game->map[i][0] != '1')
			parser_error_handler(2, game, NULL);
	i = -1;
	while (++i < game->map_size.y)
		if (game->map[i][game->map_size.x - 1] != '1')
			parser_error_handler(2, game, NULL);
	i = -1;
	while (++i < game->map_size.x - 1)
		if (game->map[0][i] != '1')
			parser_error_handler(2, game, NULL);
	i = -1;
	while (++i < game->map_size.x - 1)
		if (game->map[game->map_size.y - 1][i] != '1')
			parser_error_handler(2, game, NULL);
}

void	parse_players_position(t_game *game)
{
	int	x;
	int	y;
	int	i;

	game->players_p = malloc(sizeof(t_Vector2) * game->players);
	x = 1;
	y = 1;
	i = 0;
	while (y < game->map_size.y - 1)
	{
		x = 1;
		while (x < game->map_size.x - 1)
		{
			if (game->map[y][x] == 'P')
			{
				game->players_p[i].x = x;
				game->players_p[i].y = y;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	get_map(t_game *game, char *path)
{
	int			fd;
	char		*line;
	int			i;

	game->map = malloc(sizeof(char **) * (game->map_size.y + 1));
	game->map[game->map_size.y] = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parser_error_handler(4, game, NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		game->map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
