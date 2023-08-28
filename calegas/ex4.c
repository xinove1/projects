#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    novo_pedido->pedido = malloc(strlen(pedido));
    strcpy(novo_pedido->pedido, pedido);

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

void buscar(int numero, Fila *fila)
{
    Fila *i = fila->prox;

    while (i)
    {
        if (i->numero == numero)
        {
            printf("Numero do pedido: %d, Descricao: %s\n", i->numero, i->pedido);
            return ;
        }
        i = i->prox;
    }
    printf("Pedido nao encontrado\n");
}

void buscar_desc(char *desc, Fila *fila)
{
    Fila *i = fila->prox;

    while (i)
    {
        if (!strcmp(desc, i->pedido))
        {
            printf("Numero do pedido: %d, Descricao: %s\n", i->numero, i->pedido);
            return ;
        }
        i = i->prox;
    }
    printf("Pedido nao encontrado\n");
}

void alterar_desc(int numero, char *desc, Fila *fila)
{
    Fila *i = fila->prox;

    while (i)
    {
        if (i->numero == numero)
        {
            free(i->pedido);
            i->pedido = malloc(strlen(desc));
            strcpy(i->pedido, desc);
            return ;
        }
        i = i->prox;
    }
    printf("Pedido nao encontrado\n");
}

void remover(int numero, Fila *fila)
{
    Fila *i = fila->prox;
    Fila *prev = fila;

    while (i->prox)
    {
        if (i->numero == numero)
        {
            prev->prox = i->prox;
            free(i->pedido);
            free(i);
            return ;
        }
        prev = i;
        i = i->prox;
    }
    printf("Pedido nao encontrado\n");
}


int main() {
    Fila *fila = cria_fila();
    int escolha =  0;

    while (1)
    {

        printf("\n1 - Criar uma fila de pedidos\n2 - Enfileirar um pedido\n3 - Desenfileirar um pedido\n4 - Imprimir todos os pedidos na fila\n5 - Buscar um pedido por número\n6 - Buscar pedidos por descrição\n7 - Remover um pedido da fila\n8 - Alterar a descrição de um pedido\n0 - Sair\n");
        scanf("%d", &escolha);
        if (escolha == 1)
            continue ;
        else if (escolha == 2)
        {
            int numero;
            char desc[100] = {0};
            printf("Enfileirar pedido\n");
            printf("Numero do pedido:");
            scanf("%d", &numero);
            printf("Descricao do pedido: ");
            scanf ("%s", desc);
            //printf("numero: %d, descricao:|%s|\n", numero, desc);
            enfileira(numero, desc, fila);
        }
        else if (escolha == 3)
        {
            Fila *tmp = desenfileira(fila);
            if (tmp)
            {
                free(tmp->pedido);
                free(tmp);
            }
        }
        else if (escolha == 4)
            imprime_fila(fila);
        else if (escolha == 5)
        {
            int numero;
            printf("Buscar pedido por numero\n");
            printf("Numero do pedido:");
            scanf("%d", &numero);
            buscar(numero, fila);
        }
        else if (escolha == 6)
        {
            char desc[100] = {0};
            printf("Buscar pedido por descricao\n");
            printf("Descricao do pedido: ");
            scanf ("%s", desc);
            buscar_desc(desc, fila);
        }
        else if (escolha == 7)
        {
            int numero;
            printf("Buscar pedido por numero\n");
            printf("Numero do pedido:");
            scanf("%d", &numero);
            remover(numero, fila);
        }
        else if (escolha == 8)
        {
            int numero;
            char desc[100] = {0};
            printf("Alterar descricao de pedido\n");
            printf("Numero do pedido:");
            scanf("%d", &numero);
            printf("Nova descricao do pedido: ");
            scanf ("%s", desc);
            alterar_desc(numero, desc, fila);
        }
        else if (escolha == 0)
            break ;
        else
            printf("Escolha invalida\n");
    }
    free(fila);
}
