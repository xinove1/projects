#include "tabela.h"

int	main(int argc, char **argv)
{
	if (checar_args(argc))
		return (1);

	t_linha *tabela = alloc_tabela(20);
	ler_arquivo(argv[1], tabela, "rb");

	printf("Opções: \n help: escreve essa mensagem\n show: mostra a tabela lida\n media: mostra a media geral\n exit: termine o programa\n");
	char line[20];
	while (1)
	{
		printf("->");
		scanf("%s", line);
		if (!strcmp(line, "show"))
		{
			for (int i = 0; i < 20; i++)
			{
				printf("|%s %s %d %d %lf|\n",
					   tabela[i].nome, tabela[i].curso,
					   tabela[i].campus, tabela[i].semestre, tabela[i].nota);
			}
		}
		else if (!strcmp(line, "media"))
		{
			int soma = 0;
			for (int i = 0; i < 20; i++)
			{
				soma += tabela[i].nota;
			}
			printf("Media: %d\n", soma / 20);
		}
		else if (!strcmp(line, "exit"))
			break ;
		else
			printf("Opções: \n help: escreve essa mensagem\n show: mostra a tabela lida\n media: mostra a media geral\n exit: termine o programa\n");
	}
	escrever_arquivo(argv[2], tabela, "w+");
	free(tabela);
	return (0);
}

