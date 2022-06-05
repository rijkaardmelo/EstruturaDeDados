#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <climits>

struct no
{
    int val;
    struct no *prox;
};

struct linkedstack
{
    struct no *topo;
    int qtdade;
};

struct linkedstack *inicializar()
{
    struct linkedstack *pilha = (struct linkedstack *)malloc(sizeof(struct linkedstack));
    pilha->topo = NULL;
    pilha->qtdade = 0;
    return pilha;
}

struct no *alocarNovoNo(int valor)
{
    struct no *novo = (struct no *)malloc(sizeof(struct no));
    novo->val = valor;
    novo->prox = NULL;
    return novo;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct linkedstack *pilha)
{
    if (pilha != NULL && pilha->qtdade > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack **pilha, int valor)
{
    if ((*pilha) == NULL)
    {
        (*pilha) = inicializar();
    }

    no *temp = alocarNovoNo(valor);
    no *aux = NULL;

    if ((*pilha)->topo == NULL)
    {
        (*pilha)->topo = temp;
    }
    else
    {
        aux = (*pilha)->topo;

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = temp;
    }

    (*pilha)->qtdade++;
}

//decrementar qtdade se a pilha não estiver nula ou vazia
void desempilhar(struct linkedstack *pilha)
{
    if (pilha != NULL && pilha->qtdade > 0)
    {
        pilha->qtdade--;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack *pilha)
{
    if (pilha != NULL && pilha->qtdade > 0)
    {
        no *aux = pilha->topo;
        desempilhar(pilha);

        for (int i = 1; i < pilha->qtdade; i++)
        {
            aux = aux->prox;
        }
        return aux->val;
    }
    else
    {
        return INT_MIN;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack *pilha)
{
    if (pilha == NULL)
    {
        return INT_MIN;
    }
    else if (pilha->qtdade > 0)
    {
        no *aux = pilha->topo;
        
        for (int i = 1; i < pilha->qtdade; i++)
        {
            aux = aux->prox;
        }
        return aux->val;
    }

    return INT_MIN;
}

void exibirPilha(struct linkedstack *pilha)
{
    //usamos o aux para percorrer a lista
    if (!vazia(pilha))
    {
        struct no *aux = pilha->topo;
        //navega partindo do topo até chegar NULL
        printf("_\n");
        do
        {
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_");
    }
    else
    {
        printf("A pilha está vazia!");
    }
}