#ifndef TABELA_H
# define TABELA_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "fcntl.h"
# define STR_SZ 1024

typedef enum e_campus{CURITIBA, RIO_JANEIRO, NATAL, DF} t_campus;

typedef struct s_linha
{
	char		nome[STR_SZ];
	char		curso[STR_SZ];
	t_campus	campus;
	int			semestre;
	double		nota;
}t_linha;

t_linha *alloc_tabela(int sz);
int	checar_args(int argc);
void	escrever_arquivo(char *file, t_linha *tabela, char *flag);
void	ler_arquivo(char *file, t_linha *tabela, char *flag);

#endif
