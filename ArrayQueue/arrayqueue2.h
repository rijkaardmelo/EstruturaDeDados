#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <climits>

struct arrayqueue
{
    int frente;
    int tras;
    int *elementos;
    int tamanho; //tam do array
    int qtdade;  //qtdade de elementos no array
};

struct arrayqueue *inicializar(int tamArray)
{
    struct arrayqueue *fila = (struct arrayqueue *)malloc(sizeof(struct arrayqueue));
    fila->elementos = (int *)calloc(tamArray, sizeof(int));
    fila->frente = 0;
    fila->tras = 0;
    fila->qtdade = 0;
    fila->tamanho = tamArray;
    return fila;
}

//se a fila estiver nula, instancie a fila com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arrayqueue**
//se a fila encher, simplesmente não enfileire
void enfileirar(struct arrayqueue **fila, int val)
{
    if ((*fila) == NULL)
    {
        (*fila) = inicializar(10);
    }

    if ((*fila)->qtdade < (*fila)->tamanho)
    {
        (*fila)->elementos[(*fila)->tras] = val;
        (*fila)->tras++;
        (*fila)->qtdade++;
    }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int desenfileirar(struct arrayqueue *fila)
{
    int aux = INT_MIN;

    if (fila == NULL || fila->qtdade == 0)
    {
        return aux;
    }

    aux = fila->elementos[fila->frente];

    for (int i = 0; i < fila->tras - 1; i++)
    {
        fila->elementos[i] = fila->elementos[i + 1];
    }

    fila->tras--;
    fila->qtdade--;

    return aux;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct arrayqueue *fila)
{

    if (fila == NULL || fila->qtdade == 0)
    {
        return INT_MIN;
    }

    return fila->elementos[fila->frente];
}