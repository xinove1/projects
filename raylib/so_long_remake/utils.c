/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:39:03 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/16 12:15:48 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_Vector2	add_vec2(t_Vector2 p1, t_Vector2 p2)
{
	t_Vector2	result;

	result.x = p1.x + p2.x;
	result.y = p1.y + p2.y;
	return (result);
}

void	init_values(t_game *game)
{
	game->map = NULL;
	game->players_p = NULL;
	game->collected = 0;
	game->collectables = 0;
	game->players = 0;
	game->player_state = 1;
	game->moves = 0;
	game->map_changed = 1;
}

void	print_credits(void)
{
	ft_printf("===============================================\n\n");
	ft_printf("So Long by nthomas-\n");
	ft_printf("Art by kenney at kenney.nl\n");
	ft_printf("\n===============================================\n");
}

t_Vector2	get_map_size(char *path, t_game *game)
{
	int			fd;
	t_Vector2	size;
	char		*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		parser_error_handler(4, game, NULL);
	line = get_next_line(fd);
	if (!line)
		parser_error_handler(3, game, line);
	size.x = ft_strlen(line);
	size.y = 0;
	while (line)
	{
		if ((int)ft_strlen(line) != size.x)
			size.y = -42424242;
		size.y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (size.y < 0)
		parser_error_handler(1, game, NULL);
	size.x--;
	return (size);
}
