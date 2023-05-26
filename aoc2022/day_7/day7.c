#include "stdlib.h"
#include "stdio.h"
#include "fcntl.h"
#include "assert.h"
#include "../../libft/libft.h"

typedef struct s_dir
{
	char			*name;
	long			size;
	struct s_dir	*parent;
}t_dir;

/* typedef struct */
/* { */
/* 	size_t			size; */
/* 	t_dir			*dir; */
/* 	struct s_ldir	*next; */
/* }t_ldir; */

t_dir	*root_dir = NULL;
t_dir	*current_dir = NULL;
t_list	*dirs = NULL;

void part_1();
void part_2();
t_dir	*find_dir(char *name);
void	print_dirs(void);
void 	create_dir(char *dir_name);
char	*strjoin3(char *s1, char *s2, char *s3);
void	parse(char *line);

int	main(int argc, char **argv)
{
	int 	fd;
	char	*line;

	if (argc != 2)
	{
		printf("Please provide input file\n");
		exit(1);
	}

	root_dir = malloc(sizeof(t_dir));
	*root_dir = (t_dir){"", 0, NULL};
	ft_lstadd_front(&dirs, ft_lstnew(root_dir));

	current_dir = root_dir;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	free(line); // Jumping first line "$ cd /" cause t_dir / is already created
	line = get_next_line(fd);

	while (line)
	{
		line[ft_strlen(line) - 1] = 0; // Removes \n from the end
		parse(line);
		free(line);
		line = get_next_line(fd);
	}
	print_dirs();
	part_1();
}

void part_1()
{
	// Part One
	t_list	*i = dirs;
	long	total = 0;
	while (i)
	{
		t_dir *tmp = i->content;
		if (tmp->size <= 100000)
            total += tmp->size;
		i = i->next;
	}
	printf("Part one: %d\n", total);

	// Part Two
	const long DISK_USED = root_dir->size;
	const long DISK_TOTAL =  70000000;
	const long DISK_AVAILABLE = DISK_TOTAL - DISK_USED;
	const long DISK_NEEDED = 30000000;

	i = dirs;
	long	min = root_dir->size;
	printf("min: %ld\n", min);
	printf("DISK_TOTAL: %ld\n ", DISK_TOTAL);
	printf("DISK_USED: %ld\n ", DISK_USED);
	printf("DISK_AVAILABLE: %ld\n ", DISK_AVAILABLE);
	printf("DISK_NEEDED: %ld\n", DISK_NEEDED);
	while (i)
	{
		t_dir *tmp = i->content;

		if (DISK_AVAILABLE + tmp->size >= DISK_NEEDED && min > tmp->size)
			min = tmp->size;

		i = i->next;
	}
	printf("Part two: %ld\n", min);
}

void create_dir(char *dir_name)
{
	t_dir *dir = malloc(sizeof(t_dir));
	dir->name = strjoin3(current_dir->name, "/", dir_name);
	dir->size = 0;
	dir->parent = current_dir;
	ft_lstadd_front(&dirs, ft_lstnew(dir));
	//printf("new dir: %s\n", dir->name);
}

t_dir *find_dir(char *name)
{
	t_list *i = dirs;

	//printf("find dir: %s\n", name);
	if (name[0] == 0)
		return (root_dir);

	while (i)
	{
		t_dir *tmp = i->content;
		if (!ft_strncmp(name, tmp->name, ft_strlen(tmp->name)))
			return (tmp);
		i = i->next;
	}
	printf("Error dir:\"%s\" does not exist\n", name);
	exit(1);
}

void print_dirs(void)
{
	t_list *i = dirs;

	while (i)
	{
		t_dir *tmp = i->content;
		if (tmp->name[0] == 0)
			printf("/ | %d\n", tmp->size);
		else
			printf("%s | %d\n", tmp->name, tmp->size);
		i = i->next;
	}
}

void add_size(long n)
{
	t_dir *i = current_dir;

	while (i)
	{
		i->size += n;
		i = i->parent;
	}
}

char	*strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	return (str);
}

void	parse(char *line)
{
	if (!ft_strncmp(line, "$ ls", 4))
		return ;
	else if (!ft_strncmp(line, "$ cd ..", 7))
	{
		/* char *name = current_dir->name; */
		/* int i = ft_strlen(name); */
		/* while (name[i] != '/') */
		/* 	i--; */
		/* char *tmp = malloc(i+1); */
		/* ft_strlcpy(tmp, name, i+1); */
		printf("current dir: %s| previous dir: %s\n", current_dir->name, current_dir->parent->name);
		current_dir = current_dir->parent;
		printf("Cd into ..: %s\n", current_dir->name);
	}
	else if (!ft_strncmp(line, "$ cd", 4))
	{
		char * tmp =strjoin3(current_dir->name, "/", line + 5);
		current_dir = find_dir(tmp);
		printf("Cd into: %s\n", current_dir->name);
	}
	else if (!ft_strncmp(line, "dir ", 4))
	{
		create_dir(line + 4);
	}
	else
	{
		add_size(ft_atoi(line));
//		current_dir->size += ft_atoi(line);
	}
}
