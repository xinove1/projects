#include <stdio.h>
#include <stdlib.h>


typedef struct Fila{
    int numero;
    char *pedido;
    struct Fila *prox;
}Fila;

Fila *cria_fila() {
    Fila *tmp = malloc(sizeof(Fila));
    tmp->prox = NULL;
    tmp->numero = 0;
    tmp->pedido = NULL;
    return (tmp);
}

void enfileira(int numero, char *pedido, Fila *fila){
    Fila *novo_pedido = cria_fila();
    novo_pedido->numero = numero;
    novo_pedido->pedido = pedido;

	Fila *i = fila->prox;
	if (i == NULL)
    {
		fila->prox = novo_pedido;
        return ;
    }
	while (i->prox)
        i = i->prox;
    i->prox = novo_pedido;
}

Fila *desenfileira(Fila *fila){
    Fila *pedido = fila->prox;
    fila->prox = pedido->prox;
    pedido->prox = NULL;
    return (pedido);
}

void imprime_fila(Fila *fila){
    Fila *i = fila->prox;

    if (i == NULL)
    {
        printf("Fila vazia\n");
        return ;
    }
	printf("Pedidos: \n");
    while (i != NULL)
    {
        printf("\tNumero: %d, pedido: %s\n", i->numero, i->pedido);
        i = i->prox;
    }
}

void limpa_fila(Fila *fila){
    Fila *i = fila->prox;
    fila->prox = NULL;

    while (i != NULL)
    {
        Fila *tmp = i->prox;
        free(i);
        i = tmp;
    }
}

int main() {
    Fila *fila = cria_fila();
	enfileira(1, "frango", fila);
	enfileira(3, "batata", fila);
	enfileira(6, "fritas", fila);
	imprime_fila(fila);
	free(desenfileira(fila));
	enfileira(12, "Carne de panela", fila);
	imprime_fila(fila);
	limpa_fila(fila);
	imprime_fila(fila);
    free(fila);
}
