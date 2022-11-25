#include "tabela.h"

int	main(int argc, char **argv)
{
	if (checar_args(argc))
		return (1);

	t_linha	*tabela = alloc_tabela(20);
	ler_arquivo(argv[1], tabela, "r");
	escrever_arquivo(argv[2], tabela, "wb+");
}
