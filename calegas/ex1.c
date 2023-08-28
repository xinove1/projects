#include <stdio.h>
#include <stdlib.h>


typedef enum Naipe {ouros, copas, espadas, paus} Naipe;
char *NAIPES_STR[]  = {"Ouros", "Copas", "Espadas", "Paus"};
typedef struct Pilha{
    int carta;
    Naipe naipe;
    struct Pilha *prox;
}Pilha;

Pilha *cria_pilha() {
    Pilha *tmp = malloc(sizeof(Pilha));
    tmp->prox = NULL;
    tmp->carta = 0;
    tmp->naipe = 0;
    return (tmp);
}

void empilha(int numero, Naipe naipe, Pilha *pilha){
    Pilha *nova_carta = cria_pilha();   
    nova_carta->carta = numero;
    nova_carta->naipe = naipe;
    nova_carta->prox = pilha->prox;

    pilha->prox = nova_carta;
}

Pilha *desempilha(Pilha *pilha){
    if (pilha->prox == NULL)
        return NULL;
    Pilha *carta = pilha->prox;
    pilha->prox = carta->prox;
    carta->prox = NULL;
    return (carta);
}

void imprime_pilha(Pilha *pilha){
    Pilha *i = pilha->prox;

    if (i == NULL)
    {
        printf("Pilha vazia\n");
        return ;
    }
    while (i != NULL)
    {
        printf("|numero: %d, naipe: %s| ", i->carta, NAIPES_STR[i->naipe]);
        i = i->prox;
    }
    printf("\n");
}

void limpa_pilha(Pilha *pilha){
    Pilha *i = pilha->prox;
    pilha->prox = NULL;

    while (i != NULL)
    {
        Pilha *tmp = i->prox;
        free(i);
        i = tmp;
    }
}

int main() {
    Pilha *pilha = cria_pilha();
    empilha(3, ouros, pilha);
    empilha(5, espadas, pilha);
    empilha(9, espadas, pilha);
    imprime_pilha(pilha);
    free(desempilha(pilha));
    empilha(12, copas, pilha);
    imprime_pilha(pilha);
    limpa_pilha(pilha);
    imprime_pilha(pilha);
    free(pilha);
}
