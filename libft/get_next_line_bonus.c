/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthomas- <nthomas-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:42:25 by nthomas-          #+#    #+#             */
/*   Updated: 2022/01/10 15:05:26 by nthomas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_to_buffer(char *last, char buffer[], char **s, int fd);
static int	process_last(char **s, char last[]);
static char	*append_to_string(char *s, char *src, int src_size);
static char	*get_last(t_last **lasts, int fd);

char	*get_next_line(int fd)
{
	static t_last	*reminders = NULL;
	char			*last;
	char			buffer[BUFFER_SIZE + 1];
	char			*s;

	s = NULL;
	if (fd < 0 || fd > RLIMIT_NOFILE || BUFFER_SIZE < 1 )
		return (NULL);
	last = get_last(&reminders, fd);
	if (last[0] != '\0' && process_last(&s, last))
		return (s);
	while (read_to_buffer(last, buffer, &s, fd))
		;
	if (s == NULL || last[0] == '\0')
		clear_last(&reminders, fd);
	return (s);
}

static int	read_to_buffer(char *last, char buffer[], char **s, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = read(fd, buffer, BUFFER_SIZE);
	if (flag <= 0)
		return (0);
	buffer[flag] = '\0';
	while (buffer[i] && buffer[i] != '\n')
		i++;
	*s = append_to_string(*s, buffer, i + 1);
	if (buffer[i] == '\n' && buffer[i + 1])
		ft_memmove_gnl(last, &buffer[i + 1], BUFFER_SIZE - i);
	if (buffer[i] == '\n')
		return (0);
	return (1);
}

static int	process_last(char **s, char last[])
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (last[i] && last[i] != '\n')
		i++;
	*s = append_to_string(*s, last, i + 1);
	if (last[i] == '\n' && last[i + 1])
	{
		ft_memmove_gnl(last, &last[i + 1], ft_strlen(last) - i);
		flag = 1;
	}
	else if (last[i] == '\n')
	{
		last[0] = '\0';
		flag = 1;
	}
	else
		last[0] = '\0';
	return (flag);
}

static char	*append_to_string(char *s, char *src, int src_size)
{
	int		i;
	char	*tmp;

	if (s == NULL)
	{
		tmp = malloc(src_size + 1);
		if (!tmp)
			return (NULL);
		tmp[0] = '\0';
		i = 0;
	}
	else
	{
		i = ft_strlen(s);
		tmp = malloc(i + src_size + 1);
		if (!tmp)
			return (NULL);
		tmp[0] = '\0';
		ft_strlcat(tmp, s, i + src_size + 1);
		free(s);
	}
	ft_strlcat(tmp, src, i + src_size + 1);
	return (tmp);
}

static char	*get_last(t_last **lasts, int fd)
{
	t_last	*tmp;

	if (!*lasts)
	{
		*lasts = malloc(sizeof(t_last));
		(*lasts)->fd = fd;
		(*lasts)->reminder[0] = '\0';
		(*lasts)->next = NULL;
		return ((*lasts)->reminder);
	}
	tmp = *lasts;
	while (tmp->fd != fd && tmp->next)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp->reminder);
	else
	{
		tmp->next = malloc(sizeof(t_last));
		tmp = tmp->next;
		tmp->fd = fd;
		tmp->reminder[0] = '\0';
		tmp->next = NULL;
		return (tmp->reminder);
	}
}
