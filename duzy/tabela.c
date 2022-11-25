#include "tabela.h"

t_linha *alloc_tabela(int sz)
{
	return (malloc(sizeof(t_linha) * sz));
}

int	checar_args(int argc)
{
	if (argc > 3 || argc < 3)
	{
		printf("ERROR: porfavor insira somente o nome do arquivo a ser lido e o nome do arquivo de saida.\n");
		return (1);
	}
	return (0);
}

void	escrever_arquivo(char *file, t_linha *tabela, char *flag)
{
	FILE *file_bin = fopen(file, flag);
	int i = 0;
	while(i < 20)
	{
		fprintf(file_bin, "%s %s %d %d %lf\n",
			    tabela[i].nome, tabela[i].curso,
				tabela[i].campus, tabela[i].semestre, tabela[i].nota);
		i++;
	}
	fclose(file_bin);
}

void	ler_arquivo(char *file, t_linha *tabela, char *flag)
{
	FILE 	*fd = fopen(file, flag);
	int		quit = 2;
	int 	i = 0;

	if (!file)
	{
		perror(file);
		exit(1);
	}
	while(i < 20 && quit > 0)
	{
		quit = fscanf(fd, "%s %s %d %d %lf",
			    tabela[i].nome, tabela[i].curso,
				&tabela[i].campus, &tabela[i].semestre, &tabela[i].nota);
		if (quit != 5)
		{
			printf("Arquivo não está formatado de forma correta.\n");
			exit(1);
		}
		i++;
	}
	if (i != 20)
	{
		printf("Arquivo não tem 20 linhas validas.\n");
		exit(1);
	}
	fclose(fd);
};
