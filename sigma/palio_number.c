#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int		is_palio(char *palio);
int		copy_palio(char *buffer, char palio[10]);

int	main()
{
	char	*buffer;
	char	*tmp;
	char	palio[21];
	int		qty;
	int		i;
	int		fd;

	int	counter = 0;

	fd = open("test.txt", O_RDONLY); // File with 1 milion pi numbers withot 3. prefix
	buffer = malloc(101);
	qty = read(fd, buffer, 100);
	buffer[qty] = 0;
	while (qty)
	{
		i = 0;
		while (buffer[i] && copy_palio(buffer + i, palio))
		{
			if (is_palio(palio))
				printf("is palindromic prime: %s\n", palio);
			i++;
		}
		if (buffer[i]) // if there still bits in buffer concatenate with bigger buffer before next read
		{
			int sz = strlen(buffer + i);
			tmp = malloc(100 + sz);
			strcpy(tmp, buffer + i);
			free(buffer);
			buffer = tmp;
			qty = read(fd, buffer + sz, 100);
			buffer[qty + sz] = 0;
		}
		else
		{
			qty = read(fd, buffer, 100);
			buffer[qty] = 0;
		}
	}
}

int	copy_palio(char *buffer, char palio[10])
{
	int	i;

	i = -1;
	while(buffer[++i] && i < 20)
		palio[i] = buffer[i];
	if (i != 20)
		return (0);
	return (1);
}

// is it a palindromic prime number
int	is_palio(char *palio)
{
	int number;
	int	i;
	int	sz;

	number = atoi(palio);
	i = 0;
	sz = strlen(palio) - 1;

	while (i < sz)
	{
		if (palio[i] != palio[sz])
			return (0);
		i++;
		sz--;
	}
	i = 2;
	while (i <= number / 2)
	{
		if (number % i == 0)
			return (0);
		i++;
	}
	return (1);
}
