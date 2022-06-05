#include <stdlib.h>
#include <stdio.h>

struct no
{
    struct no *ant;
    int val;
    struct no *prox;
};

struct doublylinkedlist
{
    struct no *cabeca;
    struct no *cauda;
    int qtdade;
};

struct doublylinkedlist *inicializar()
{
    struct doublylinkedlist *lista = (struct doublylinkedlist *)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no *alocarNovoNo(int valor)
{
    struct no *novo = (struct no *)malloc(sizeof(struct no));
    novo->val = valor;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

void inserirElementoNoInicio(struct doublylinkedlist *lista, int valor)
{
    struct no *tmp = alocarNovoNo(valor);

    if (lista->cabeca == NULL)
    {
        lista->cabeca = tmp;
        lista->cauda = tmp;
    }
    else
    {
        lista->cabeca->ant = tmp;
        tmp->prox = lista->cabeca;
        lista->cabeca = tmp;
    }

    lista->qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist *lista, int valor)
{
    struct no *tmp = alocarNovoNo(valor);

    if (lista->cabeca == NULL)
    {
        lista->cauda = tmp;
        lista->cabeca = tmp;
    }
    else
    {
        lista->cauda->prox = tmp;
        tmp->ant = lista->cauda;
        lista->cauda = tmp;
    }

    lista->qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist *lista, int valor, int posicao)
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
                struct no *tmp = alocarNovoNo(valor);
                struct no *aux = lista->cabeca;

                for (int i = 1; i < posicao; i++)
                {
                    aux = aux->prox;
                }
                if (aux == lista->cauda)
                {
                    lista->cauda = tmp;
                }
                else
                {
                    tmp->prox = aux->prox;
                    aux->prox->ant = tmp;
                }

                tmp->ant = aux;
                aux->prox = tmp;
                lista->qtdade++;
            }
        }
    }
}

int obterElementoEmPosicao(struct doublylinkedlist *lista, int posicao)
{
    if (posicao >= 0 && posicao <= lista->qtdade)
    {
        if (lista->cabeca != NULL)
        {
            struct no *aux = lista->cabeca;

            for (int i = 0; i < posicao; i++)
            {
                aux = aux->prox;
            }

            return aux->val;
        }
    }

    return -1;
}

void removerElementoEmPosicao(struct doublylinkedlist *lista, int posicao)
{
    if (posicao >= 0 && posicao <= lista->qtdade)
    {
        struct no *tmp = lista->cabeca;

        if (lista->cabeca != NULL)
        {
            for (int i = 0; i < posicao; i++)
            {
                tmp = tmp->prox;
            }

            if (tmp == lista->cabeca)
            {
                lista->cabeca = lista->cabeca->prox;
            }
            else
            {
                tmp->ant->prox = tmp->prox;
            }

            if (tmp == lista->cauda)
            {
                lista->cauda = tmp->ant;
            }
            else
            {
                tmp->prox->ant = tmp->ant;
            }
        }
    }

    lista->qtdade--;
}

void imprimirLista(struct no **cabeca)
{
    //usamos o aux para percorrer a lista
    if ((*cabeca) != NULL)
    {
        struct no *aux = (*cabeca);
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