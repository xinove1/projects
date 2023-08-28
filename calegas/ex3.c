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
        return (NULL);
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


void busca(int numero, Naipe naipe, Pilha *pilha){
    Pilha *i = pilha->prox;
    int	pos = 0;

    if (i == NULL)
    {
        printf("Pilha vazia\n");
        return ;
    }
    while (i != NULL)
    {
        if (i->carta == numero && i->naipe == naipe) {
            printf("Posição: %d, naipe: %s \n", pos+1, NAIPES_STR[i->naipe]);
            return ; 
        }
        pos++;
        i = i->prox;
    }
    printf("Não existe no baralho");
}

void busca_numero(int numero, Pilha *pilha){
    Pilha *i = pilha->prox;
    int	pos = 0;
    int flag = 0;

    if (i == NULL)
    {
        printf("Pilha vazia\n");
        return ;
    }
    while (i != NULL)
    {
        if (i->carta == numero) {
            printf("Posição: %d, naipe: %s \n", pos+1, NAIPES_STR[i->naipe]);
            flag = 1;
        }
        pos++;
        i = i->prox;
    }
    if (!flag)
        printf("Não existe no baralho");
}

void busca_naipe(Naipe naipe, Pilha *pilha){
    Pilha *i = pilha->prox;
    int	pos = 0;
    int flag = 0;

    if (i == NULL)
    {
        printf("Pilha vazia\n");
        return ;
    }
    while (i != NULL)
    {
        if (i->naipe == naipe) {
            printf("Posição: %d, numero: %d \n", pos+1, i->carta);
            flag = 1;
        }
        pos++;
        i = i->prox;
    }
    if (!flag)
        printf("Não existe no baralho");
}

void retirar_carta(int numero, Naipe naipe, Pilha *pilha){
    Pilha *i = pilha->prox;
    Pilha *carta_anterior = pilha;

    if (i == NULL)
    {
        printf("Pilha vazia\n");
        return ;
    }
    while (i != NULL)
    {
        if (i->carta == numero && i->naipe == naipe) {
            carta_anterior->prox = i->prox;
            free(i);
            return ; 
        }
        carta_anterior = i;
        i = i->prox;
    }
    printf("Não existe no baralho");
}

void inverter(Pilha *pilha){
    if (pilha->prox == NULL)
        return ;
    Pilha *nova_pilha = cria_pilha();
    Pilha *topo = pilha->prox;    
    pilha->prox = topo->prox;
    topo->prox = NULL;
    while (topo)
    {
        topo->prox = nova_pilha->prox;
        nova_pilha->prox = topo;
        topo = pilha->prox;
        if (topo == NULL)
            break ; 
        pilha->prox = topo->prox;
        topo->prox = NULL;
    }
    if (pilha->prox != NULL)
    {
        printf("Error\n");
        exit(1);
    }
    pilha->prox = nova_pilha->prox;
    free(nova_pilha);
}

int main() {
    Pilha *pilha = cria_pilha();
    int escolha =  0;

    while (1)
    {

        printf("\n1-Criar baralho \n2-Empilhar carta \n3-Desempilhar carta \n4-Imprimir baralho \n5-Buscar carta por número e naipe \n6-Buscar cartas por número \n7-Buscar cartas por naipe \n8-Retirar uma carta \n9-Inverter baralho \n0-Sair\n");
        scanf("%d", &escolha);
        if (escolha == 1)
            continue ;
        else if (escolha == 2)
        {
            int numero, naipe;
            printf("Empilhando a carta\n");
            printf("Numero da carta (1-12): ");
            scanf("%d", &numero);
            printf("1 - Ouros, 2 - Copas, 3 - Espadas, 4 - paus\n");
            printf("Naipe da carta: ");
            scanf("%d", &naipe);
            if ( numero > 12 || numero < 1 || naipe < 1 || naipe > 4)
            {
                printf("Erro, porfavor somente inserir numeros permitidos\n");
                continue;
            }
            empilha(numero, naipe - 1, pilha);
        }
        else if (escolha == 3)
        {
            Pilha *tmp = desempilha(pilha);
            if (tmp)
                free(tmp);
        }
        else if (escolha == 4)
            imprime_pilha(pilha);
        else if (escolha == 5)
        {
            int numero, naipe;
            printf("Buscar Carta\n");
            printf("Numero da carta (1-12): ");
            scanf("%d", &numero);
            printf("1 - Ouros, 2 - Copas, 3 - Espadas, 4 - paus\n");
            printf("Naipe da carta: ");
            scanf("%d", &naipe);
            if ( numero > 12 || numero < 1 || naipe < 1 || naipe > 4)
            {
                printf("Erro, porfavor somente inserir numeros permitidos\n");
                continue;
            }
            busca(numero, naipe - 1, pilha);
        }
        else if (escolha == 6)
        {
            int numero;
            printf("Buscar por numero\n");
            printf("Numero da carta (1-12): ");
            scanf("%d", &numero);
            if ( numero > 12 || numero < 1)
            {
                printf("Erro, porfavor somente inserir numeros permitidos\n");
                continue;
            }
            busca_numero(numero, pilha);
        }
        else if (escolha == 7)
        {
            int naipe;
            printf("Buscar por Naipe\n");
            printf("1 - Ouros, 2 - Copas, 3 - Espadas, 4 - paus\n");
            printf("Naipe da carta: ");
            scanf("%d", &naipe);
            if (naipe < 1 || naipe > 4)
            {
                printf("Erro, porfavor somente inserir numeros permitidos\n");
                continue;
            }
            busca_naipe(naipe - 1, pilha);
        }
        else if (escolha == 8)
        {
            int numero, naipe;
            printf("Retirar uma Carta\n");
            printf("Numero da carta (1-12): ");
            scanf("%d", &numero);
            printf("1 - Ouros, 2 - Copas, 3 - Espadas, 4 - paus\n");
            printf("Naipe da carta: ");
            scanf("%d", &naipe);
            if ( numero > 12 || numero < 1 || naipe < 1 || naipe > 4)
            {
                printf("Erro, porfavor somente inserir numeros permitidos\n");
                continue;
            }
            retirar_carta(numero, naipe - 1, pilha);
        }
        else if (escolha == 9)
            inverter(pilha);
        else if (escolha == 0)
            break ;
        else
            printf("Escolha invalida\n");
    }
    free(pilha);
}
