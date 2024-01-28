#include "game.h"

void	render_ui(ecs_iter_t *it)
{
	Rectangle rrec = (Rectangle){10,100, 40,30};
	if (GuiButton(rrec, "teste"))
		printf("oaeuhaoenuh\n");
}

void	render_tiles(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Tile		*tile = ecs_field(it, Tile, 2);
	Rectangle	rec;
	rec.height = TILE_SZ;
	rec.width  = TILE_SZ;

	for (int i = 0; i < it->count; i++)
	{
		rec.x = tile[i].x * TILE_SZ;
		rec.y = tile[i].y * TILE_SZ;
		DrawTextureRec(data.tilemap, rec, (Vector2) {pos[i].x * TILE_SZ, pos[i].y * TILE_SZ}, WHITE);
	}
}


void	render_health(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Health		*health = ecs_field(it, Health, 2);

	for (int i = 0; i < it->count; i++)
	{
		Position	r_pos = {pos[i].x * TILE_SZ + 1, pos[i].y * TILE_SZ - 9};
		DrawText(TextFormat("%d", health[i]), r_pos.x, r_pos.y, 3, RED);
	}
}

void	flash_color(ecs_iter_t *it)
{
	Position	*pos = ecs_field(it, Position, 1);
	Tile		*tile = ecs_field(it, Tile, 2);
	FlashColor	*colors = ecs_field(it, FlashColor, 3);// TODO better name
	Rectangle	rec;
	rec.height = TILE_SZ;
	rec.width  = TILE_SZ;

	for (int i = 0; i < it->count; i++)
	{
		colors[i].timer += it->delta_time;
		if (colors[i].timer >= colors[i].duration)
			ecs_remove(it->world, it->entities[i], FlashColor);
		rec.x = tile[i].x * TILE_SZ;
		rec.y = tile[i].y * TILE_SZ;
		float	color_alpha = Remap(colors[i].timer, 0, colors[i].duration, 0, 1);
		DrawRectangle(pos[i].x * TILE_SZ, pos[i].y * TILE_SZ, rec.width, rec.height, ColorAlpha(colors[i].color, color_alpha));
	}
}

void	render_colliders_map(ecs_iter_t	*it)
{
	ecs_entity_t	game_map = ecs_lookup(it->world, "GameMap");
	const Arr2D	*map = ecs_get(it->world, game_map, Arr2D);
	if (map->arr == NULL)
	{
		printf("Tryng to render a empty map \n");
		return ;
	}
	for (int y = 0; y < map->size.y; y++)
	{
		for (int x = 0; x < map->size.x; x++)
		{
			if (map->arr[y][x] == 0)
				continue;
			Position	d_pos = (Position) {x * TILE_SZ, y * TILE_SZ};
			DrawRectangle(d_pos.x, d_pos.y, TILE_SZ, TILE_SZ, ColorAlpha(RED, 0.3));
		}
	}
}

void	render_path(ecs_iter_t *it)
{
	Path	*path = ecs_field(it, Path, 1);

	for (int i = 0; i < it->count; i++)
	{
		if (!path[i].current)
			continue;
		List	*lst = path[i].current;
		while (lst)
		{
			Vector2		*v = lst->content;
			Position	d_pos = (Position) {v->x * TILE_SZ, v->y * TILE_SZ};
			DrawRectangle(d_pos.x, d_pos.y, TILE_SZ, TILE_SZ, ColorAlpha(BLUE, 0.3));
			lst = lst->next;
		}
	}
}

void	prepare_draw(ecs_iter_t	*it)
{
	(void) it;
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawFPS(10, 10);
}

void	prepare_draw2D(ecs_iter_t *it)
{
	(void) it;

	BeginMode2D(data.camera);
}

void	end_draw2D(ecs_iter_t *it)
{
	(void) it;

	EndMode2D();
}

void	end_draw(ecs_iter_t *it)
{
	(void) it;

	EndDrawing();
}
