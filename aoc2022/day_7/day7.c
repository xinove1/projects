#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"

typedef struct s_dir
{
	char		*name;
	long		size;
	void		*sub_dirs;
}t_dir;

typedef struct s_ldir
{
	t_dir		*dir;
	struct s_ldir	*next;
}t_ldir;

int	main()
{
	int 	fd;
	char	*line;

	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{

		free(line);
		line = get_next_line(fd);
	}
}
