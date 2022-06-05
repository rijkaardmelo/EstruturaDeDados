#include <stdlib.h>
#include <stdio.h>

struct no
{
    int val;
    struct no *prox;
};

struct linkedlist
{
    struct no *cabeca;
    int qtdade;
};

struct linkedlist *inicializar()
{
    struct linkedlist *lista = (struct linkedlist *)malloc(sizeof(struct linkedlist));
    lista->cabeca = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no *alocarNovoNo(int valor)
{
    struct no *novo = (struct no *)malloc(sizeof(struct no));
    novo->val = valor;
    novo->prox = NULL;
    return novo;
}

void inserirElementoNoFim(struct linkedlist *lista, int valor)
{
    no *temp = alocarNovoNo(valor);
    no *aux = NULL;
    if (lista->cabeca == NULL)
    {
        lista->cabeca = temp;
    }
    else
    {
        aux = lista->cabeca;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = temp;
    }
    lista->qtdade++;
}

void inserirElementoNoInicio(struct linkedlist *lista, int valor)
{
    no *tmp = alocarNovoNo(valor);
    if (lista->cabeca == NULL)
    {
        lista->cabeca = tmp;
    }
    else
    {
        tmp->prox = lista->cabeca;
        lista->cabeca = tmp;
    }
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist *lista, int valor, int posicao)
{
    if (posicao >= 0 && posicao <= lista->qtdade)
    {
        if (posicao == 0)
        {
            inserirElementoNoInicio(lista, valor);
        }
        else
        {
            if (lista->cabeca != NULL)
            {
                no *tmp = alocarNovoNo(valor);
                no *aux = lista->cabeca;
                for (int i = 1; i < posicao; i++)
                {
                    aux = aux->prox;
                }
                tmp->prox = aux->prox;
                aux->prox = tmp;
            }
            lista->qtdade++;
        }
    }
}

int obterElementoEmPosicao(struct linkedlist *lista, int posicao)
{
    if (posicao >= 0 && posicao <= lista->qtdade)
    {
        if (lista->cabeca != NULL)
        {
            no *aux = lista->cabeca;
            for (int i = 0; i < posicao; i++)
            {
                aux = aux->prox;
            }
            return aux->val;
        }
    }
    return -1;
}

void removerElementoEmPosicao(struct linkedlist *lista, int posicao)
{
    if (posicao >= 0 && posicao < lista->qtdade)
    {
        if (posicao == 0)
        {
            lista->cabeca = lista->cabeca->prox;
        }
        else if (posicao == (lista->qtdade - 1))
        {
            no *aux = lista->cabeca;
            while (aux->prox->prox != NULL)
            {
                aux = aux->prox;
            }
            aux->prox = NULL;
        }
        else
        {
            if (lista->cabeca != NULL)
            {
                no *aux = lista->cabeca;
                for (int i = 1; i < posicao; i++)
                {
                    aux = aux->prox;
                }
                aux->prox = aux->prox->prox;
            }
        }
    }
    lista->qtdade--;
}

void imprimirLista(struct linkedlist *lista)
{
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL)
    {
        struct no *aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do
        {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL)
            {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else
    {
        printf("A lista está vazia!");
    }
}