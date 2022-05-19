#include "../gnl/get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

char	common(t_list *list, int i, int least);
int		common2(t_list *list, int i, int least);
void	part1(t_list *list);
void	part2(t_list **list);
void	parse_list(t_list **list, t_list **new, char bit, int i);
void nothing(void *lets){if (lets) return;};

int	main(void)
{
	t_list	*list;
	int		file = open("./input.txt", O_RDONLY);
	char	*line = get_next_line(file);
	list = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(file);
		ft_lstadd_back(&list, ft_lstnew(line));
	}
	part2(&list);
	//part1(list);
	close(file);
	ft_lstclear(&list, free);
}

void	part1(t_list *list)
{
	char	binary[13] = "\0";
	long		most_common;
	for (int i = 0; i < 12; i++)
		binary[i] = common(list, i, 0);

	printf("Binary strtoll most: %ld \n", strtol(binary, 0, 2));
	most_common = strtol(binary, 0, 2);

	for (int i = 0; i < 12; i++)
		binary[i] = common(list, i, 1);

	printf("Binary strtoll most: %ld \n", strtol(binary, 0, 2));


	printf("Most_common: %ld \n", most_common);
	printf("Least_common: %ld \n", strtol(binary, 0, 2));
	printf("Result: %ld \n", most_common * strtol(binary, 0, 2));
}

void	part2(t_list **list)
{
	/* char	binary[13] = "\0"; */
	t_list	*o_list = NULL;
	t_list  *c_list = NULL;
	t_list  **tmp = list;
	int	oxygen = 0;
	int co2 = 0;
	int bit = 0;

	for (int i = 0; i < 12; i++)
	{
		bit = common2(*tmp, i, 1);
		parse_list(tmp, &c_list, bit, i);
		*tmp = c_list;
		c_list = NULL;
	}
	c_list = *tmp;

	bit = common2(*list, 0, 0);
	parse_list(list, &o_list, bit, 0);
	*tmp = o_list;
	for (int i = 1; i < 12; i++)
	{
		bit = common2(o_list, i, 0);
		parse_list(tmp, &o_list, bit, i);
		*tmp = o_list;
		o_list = NULL;
	}
	printf("c List: %s \n", (char *) c_list->content);
	printf("o List: %s \n", (char *) o_list->content);
	*tmp = o_list;
	/* while (tmp) */
	/* { */
	/* 	printf("o List: %s \n", (char *)*tmp->content); */
	/* 	*tmp = *tmp->next; */
	/* } */

	ft_lstclear(&o_list, nothing);
	ft_lstclear(&c_list, nothing);
	printf("Oxygen: %d \n", oxygen);
	printf("CO2: %d \n", co2);
	printf("Result: %d \n", oxygen * co2);
}


void	parse_list(t_list **list, t_list **new, char bit, int i)
{
	t_list *tmp = *list;
	while (tmp->next)
	{
		if (((char *)tmp->content)[i] == bit)
			ft_lstadd_back(new, ft_lstnew(tmp->content));
		tmp = tmp->next;
	}
}

int	common2(t_list *list, int i, int least)
{
	int		ones = 0;
	int		zeros = 0;

	while (list->next)
	{
		if (((char *)list->content)[i] == '0')
			zeros++;
		else
			ones++;
		list = list->next;
	}
	if (ones == zeros)
		return ('2');
	if (least)
	{
		if (ones > zeros)
			return ('0');
		else
			return ('1');
	}
	if (ones > zeros)
		return ('1');
	else
		return ('0');
}

char	common(t_list *list, int i, int least)
{
	int		ones = 0;
	int		zeros = 0;

	while (list->next)
	{
		if (((char *)list->content)[i] == '0')
			zeros++;
		else
			ones++;
		list = list->next;
	}
	if (least)
	{
		if (ones > zeros)
			return ('0');
		else
			return ('1');
	}
	if (ones > zeros)
		return ('1');
	else
		return ('0');
}
