#include "frogame.h"

static Vector2	count_map_size(char **map);
static char	**fill_map(char *file);
static int	check_line(char *line);

t_map parse_map(char *file)
{
	t_map	map;

	map.map = fill_map(file);
	if (!map.map)
		return ((t_map){{0,0}, NULL});
	map.sz = count_map_size(map.map);
	if (map.sz.x <= 0 || map.sz.y <= 0)
	{
		ft_printf("file: %s.\n", file);
		return ((t_map){{0,0}, NULL});
	}
	return (map);
}

static char	**fill_map(char *file)
{
	char	buf[1024];
	int		fd;
	int		red;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(NULL);
		return (NULL);
	}
	red = read(fd, buf, 1023);
	if (red == 0)
	{
		ft_printf("File map empty: %s.\n", file);
		return(NULL);
	}
	buf[red] = 0;
	close(fd);
	return (ft_split(buf, '\n'));
}

static int	check_line(char *line)
{
	int	i;

	i = -1;
	while (line[i++])
	{
		char c = line[i];
		if (c != WALL && c != NOTHING && c != LIGHT_SWITCH)
		{
			ft_printf("Unknow character on map: %c.\n", c);
			return (0);
		}
	}
	return (1);
}

static Vector2	count_map_size(char **map)
{
	Vector2	size;
	int		i;

	i = -1;
	size.x = ft_strlen(map[0]);
	size.y = 0;
	while (map[++i])
	{
		if ((int)ft_strlen(map[i]) != size.x)
		{
			ft_printf("File map is not Rectangle.\n");
			return ((Vector2){0, 0});
		}
		if (!check_line(map[i]))
			return ((Vector2){0, 0});
		size.y++;
	}
	return (size);
}

