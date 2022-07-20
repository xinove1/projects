/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:38:48 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/16 17:33:37 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keys(t_game *game)
{
	if (IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_H))
		move(game, (t_Vector2){-1, 0});
	else if (IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT)||IsKeyPressed(KEY_L))
		move(game, (t_Vector2){1, 0});
	else if (IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_K))
		move(game, (t_Vector2){0, -1});
	else if (IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_J))
		move(game, (t_Vector2){0, 1});
	else if (IsKeyPressed(KEY_ESCAPE))
		exit_game(game);
	return (0);
}

void	move(t_game *game, t_Vector2 dir)
{
	char		new_pos;
	int			i;
	t_Vector2	*current_pos;

	current_pos = game->players_p;
	i = 0;
	while (i < game->players)
	{
		new_pos = game->map[current_pos[i].y + dir.y][current_pos[i].x + dir.x];
		if (new_pos == '0')
			change_player_pos(game, i, dir);
		else if (new_pos == 'E' && game->collected == game->collectables)
			exit_game(game);
		else if (new_pos == 'C')
		{
			change_player_pos(game, i, dir);
			game->collected++;
		}
		i++;
	}
	game->moves++;
	game->player_state = -game->player_state;
	game->map_changed = 1;
}

void	change_player_pos(t_game *game, int i, t_Vector2 dir)
{
	change_map(game, add_vec2(game->players_p[i], dir), 'P');
	change_map(game, game->players_p[i], '0');
	game->players_p[i] = add_vec2(game->players_p[i], dir);
}

void	change_map(t_game *game, t_Vector2 target, char c)
{
	game->map[target.y][target.x] = c;
}
