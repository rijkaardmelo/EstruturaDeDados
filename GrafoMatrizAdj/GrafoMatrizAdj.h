#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

struct GrafoMatrizAdj
{
    int **arestas;
    char **rotuloVertices;
    int verticesInseridos;
    int maxNumVertices;
    //faz mais sentido ser apenas numVertices (consertar para a prox turma)
};

/**
 * Se o grafo for ponderado, inicializamos cada posicao da matriz com INT_MAX.
 * Se o grafo for não ponderado, inicializamos cada posicao da matriz com 0.
 **/
struct GrafoMatrizAdj *inicializar(int numVertices, bool ponderado)
{
    struct GrafoMatrizAdj *grafo = (struct GrafoMatrizAdj *)malloc(sizeof(struct GrafoMatrizAdj));
    grafo->arestas = (int **)calloc(numVertices, sizeof(int *));
    grafo->rotuloVertices = (char **)calloc(numVertices, sizeof(char *));

    for (int i = 0; i < numVertices; i++)
    {
        grafo->arestas[i] = (int *)calloc(numVertices, sizeof(int));
        grafo->rotuloVertices[i] = (char *)calloc(numVertices, sizeof(char));
    }

    grafo->verticesInseridos = 0;
    grafo->maxNumVertices = numVertices;

    if (ponderado)
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                grafo->arestas[i][j] = INT_MAX;
    else
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                grafo->arestas[i][j] = 0;

    return grafo;
}

/**
 * A principio nao temos nenhuma ordenacao usando os rotulos.
 * Portanto, usaremos busca linear
 **/
int obterIndiceVertice(struct GrafoMatrizAdj *grafo, char *rotuloVertice)
{
    for (int i = 0; i < grafo->verticesInseridos; i++)
        if (rotuloVertice == grafo->rotuloVertices[i])
            return i;

    return -1;
}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da aresta.
 * Se o grafo for não ponderado, passaremos o valor 1 para a variavel peso, de modo que represente existência da aresta.
 * Se um dos rotulos dos vertices nao existir, simplesmente nao faremos nada.
 **/
void inserirAresta(struct GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino, int peso)
{
    if (obterIndiceVertice(grafo, rotuloVDestino) != -1 && obterIndiceVertice(grafo, rotuloVOrigem) != -1)
    {
        grafo->arestas[obterIndiceVertice(grafo, rotuloVDestino)][obterIndiceVertice(grafo, rotuloVOrigem)] = peso;
        grafo->arestas[obterIndiceVertice(grafo, rotuloVOrigem)][obterIndiceVertice(grafo, rotuloVDestino)] = peso;
    }
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de vertices que ja foi inserido no grafo.
 * Logo, ela pode/deve ser usada para especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(struct GrafoMatrizAdj *grafo, char *rotuloVertice)
{
    if (grafo->verticesInseridos < grafo->maxNumVertices)
    {
        grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
        grafo->verticesInseridos++;
    }
}

/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois vertices em um grafo ponderado,
 * e haver conexão entre dois vertices em um grafo nao-ponderado.
 **/
bool saoConectados(struct GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino)
{
    if (obterIndiceVertice(grafo, rotuloVDestino) != -1 && obterIndiceVertice(grafo, rotuloVOrigem) != -1)
    {
        if ((grafo->arestas[obterIndiceVertice(grafo, rotuloVDestino)][obterIndiceVertice(grafo, rotuloVOrigem)] != 0 &&
             grafo->arestas[obterIndiceVertice(grafo, rotuloVOrigem)][obterIndiceVertice(grafo, rotuloVDestino)] != 0) &&
            (grafo->arestas[obterIndiceVertice(grafo, rotuloVDestino)][obterIndiceVertice(grafo, rotuloVOrigem)] != INT_MAX &&
             grafo->arestas[obterIndiceVertice(grafo, rotuloVOrigem)][obterIndiceVertice(grafo, rotuloVDestino)] != INT_MAX))
        {
            return true;
        }
    }
    return false;
}