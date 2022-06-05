#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <climits>

struct no
{
    int val;
    struct no *prox;
};

struct linkedqueue
{
    struct no *frente;
    struct no *tras;
    int qtdade;
};

struct linkedqueue *inicializar()
{
    struct linkedqueue *fila = (struct linkedqueue *)malloc(sizeof(struct linkedqueue));
    fila->frente = NULL;
    fila->tras = NULL;
    fila->qtdade = 0;
    return fila;
}

struct no *alocarNovoNo(int valor)
{
    struct no *novo = (struct no *)malloc(sizeof(struct no));
    novo->val = valor;
    novo->prox = NULL;
    return novo;
}

bool vazia(struct linkedqueue *fila)
{
    if (fila != NULL && fila->qtdade > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue **fila, int val)
{
    if ((*fila) == NULL)
    {
        (*fila) = inicializar();
    }

    (*fila)->tras = alocarNovoNo(val);
    no *aux = (*fila)->frente;

    if ((*fila)->frente == NULL)
    {
        (*fila)->frente = (*fila)->tras;
    }
    else
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = (*fila)->tras;
    }

    (*fila)->qtdade++;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o nó removido (free)
int desenfileirar(struct linkedqueue *fila)
{
    int aux = INT_MIN;

    if (fila == NULL || fila->qtdade == 0)
    {
        return aux;
    }

    aux = fila->frente->val;

    while (fila->frente != fila->tras)
    {
        fila->frente = fila->frente->prox;
    }

    fila->qtdade--;

    return aux;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct linkedqueue *fila)
{
    if (fila == NULL || fila->qtdade == 0)
    {
        return INT_MIN;
    }

    return fila->frente->val;
}