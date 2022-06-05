#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <climits>

#include <iostream>
using namespace std;

struct arraylist
{
    int *vetor;
    int qtdade;
    int capacidade;
};

struct arraylist *inicializarAL(int capacidade)
{
    struct arraylist *lista = (struct arraylist *)malloc(sizeof(struct arraylist));
    lista->vetor = (int *)calloc(capacidade, sizeof(int));
    lista->qtdade = 0;
    lista->capacidade = capacidade;
    return lista;
}

void duplicarCapacidade(struct arraylist *lista)
{
    lista->vetor = (int *)realloc(lista->vetor, 2 * lista->capacidade * sizeof(int));
    lista->capacidade = 2 * lista->capacidade;
}

void inserirElementoNoFim(struct arraylist *lista, int valor)
{
    if (lista->qtdade == lista->capacidade)
    {
        duplicarCapacidade(lista);
    }
    lista->vetor[lista->qtdade] = valor;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct arraylist *lista, int posicao)
{
    if (posicao >= 0 && posicao < lista->qtdade)
    {
        return lista->vetor[posicao];
    }

    return -1;
}

void inverterArrayList(struct arraylist *lista)
{
    if (lista->qtdade > 0)
    {
        int aux;
        for (int i = 0; i < (lista->qtdade / 2); i++)
        {
            aux = lista->vetor[i];
            lista->vetor[i] = lista->vetor[lista->qtdade - 1 - i];
            lista->vetor[lista->qtdade - 1 - i] = aux;
        }
    }

    //inverte um struct arraylist* in-place
    //in-place significa que não poderá ser usado
    //nenhum array ou lista adicional, além do original
}

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

struct doublylinkedlist *inicializarDLL()
{
    struct doublylinkedlist *lista = (struct doublylinkedlist *)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no *alocarNovoNo(int valor)
{
    struct no *novoNo;
    novoNo = (struct no *)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->ant = NULL;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct doublylinkedlist *lista, int valor)
{
    //aloca espaço na memória e popula novoNo
    struct no *novoNo = alocarNovoNo(valor);

    if (lista->cabeca == NULL)
    {
        //quando a lista é vazia, basta apontar o cabeca e cauda para o novoNo
        lista->cabeca = novoNo;
    }
    else
    {
        //atualizamos o ponteiro novoNo->ant para o antigo último nó
        novoNo->ant = lista->cauda;
        //ponteiro prox do antigo último nó para o novoNo
        lista->cauda->prox = novoNo;
    }
    //uma certeza: inserindo no fim, a cauda apontará para o novoNo
    lista->cauda = novoNo;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct doublylinkedlist *lista, int posicao)
{
    struct no *aux = lista->cabeca;
    for (int i = 0; i < posicao && aux->prox != NULL; i++)
    {
        aux = aux->prox;
    }
    return aux->val;
}

void inverterDoublyLinkedList(struct doublylinkedlist *lista)
{
    //TODO

    //inverte uma struct doublylinkedlist* in-place
    //in-place significa que não poderá ser usado
    //nenhum array ou lista adicional, além da original

    if (lista->qtdade > 0)
    {
        lista->cauda = lista->cabeca;
        no *aux = lista->cauda;
        no *temp = NULL;

        while (aux != NULL)
        {
            temp = aux->ant;
            aux->ant = aux->prox;
            aux->prox = temp;
            aux = aux->ant;
        }

        if (temp != NULL)
            lista->cabeca = temp->ant;
    }
}

void insereOrdenado(struct arraylist *lista, int val)
{
    //TODO

    //deve usar o algoritmo de busca binaria para encontrar o indice
    //dps, abre espaco no array, e insere no local encontrado

    int inicio = 0;
    int meio = -1;
    int fim = lista->qtdade - 1;

    while (inicio <= fim)
    {
        meio = (fim + inicio) / 2;

        if (lista->vetor[meio] == val)
        {
            break;
        }
        else if (val < lista->vetor[meio])
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    if (meio >= 0)
    {
        for (int i = lista->qtdade; i > meio; i--)
        {
            lista->vetor[i] = lista->vetor[i - 1];
        }

        lista->vetor[meio] = val;
        lista->qtdade++;
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
