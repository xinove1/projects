#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "../../libft/libft.h"
#define MARKER_SIZE 14

int	verify_marker(char *marker);
void	push_marker(char *marker, char c);

int	main()
{
	int 	fd;
	int		i;
	char	*line;
	char	packet[MARKER_SIZE + 1];

	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	packet[MARKER_SIZE] = 0;
	i = -1;
	while (++i < MARKER_SIZE)
		packet[i] = line[i];
	while (line[i])
	{
		if (verify_marker(packet))
		{
			printf("i: %d\n", i);
			break ;
		}
		push_marker(packet, line[i]);
		i++;
	}
	close(fd);
}

void	push_marker(char *marker, char c)
{
	int	i;

	i = 0;
	while (marker[i + 1])
	{
		marker[i] = marker[i + 1];
		i++;
	}
	marker[i] = c;
}

int	verify_marker(char *marker)
{
	int	i;
	int	j;

	i = 0;
	while (marker[i])
	{
		j = i + 1;
		while (marker[j])
		{
			if (marker[j] == marker[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
