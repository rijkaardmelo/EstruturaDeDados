#include <iostream>
#include <vector>
#include <queue>
#include "stdbool.h"

using namespace std;

class GrafoListaAdj
{
private:
    vector<string> vertices;

    // first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;

    /**
     * A principio nao temos nenhuma ordenacao usando os rotulos.
     * Portanto, usaremos busca linear.
     **/
    int obterIndiceVertice(string rotuloVertice)
    {
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i] == rotuloVertice)
                return i;
        return -1;
    }

public:
    /**
     * Lembrem-se:
     *       1) nao podemos inserir vertices com mesmo rotulo
     *       2) toda vez que inserirmos um novo vértice, precisaremos
     *          inserir um vetor para representar as conexões daquele
     *          vértice na lista de adjacências
     **/
    void inserirVertice(string rotuloVertice)
    {
        if (obterIndiceVertice(rotuloVertice) == -1)
        {
            vertices.push_back(rotuloVertice);
            vector<pair<int, int>> aux;
            arestas.push_back(aux);
        }
    }

    /**
     * Sempre que o grafo for não ponderado, adicionaremos o peso 1,
     * por conveniência.
     **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
    }

    /**
     * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
     * especificado.
     **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        pair<int, int> aux;
        aux.first = obterIndiceVertice(rotuloVDestino);
        aux.second = peso;
        arestas[obterIndiceVertice(rotuloVOrigem)].push_back(aux);
    }

    // Grupo do union-find
    class Grupo
    {
    public:
        int pai;
        int tamanho;
    };

    // encontrar raiz
    // pode ser com ou sem path compression
    int encontrarRaiz(Grupo *grupos, int i)
    {
        if (i == grupos[i].pai)
            return i;
        return grupos[i].pai = encontrarRaiz(grupos, grupos[i].pai);
    }

    bool mesmoGrupo(Grupo *grupos, int a, int b)
    {
        return encontrarRaiz(grupos, a) == encontrarRaiz(grupos, b);
    }

    int tamanhoGrupo(Grupo *grupos, int a)
    {
        return grupos[a].tamanho;
    }

    void unirGrupos(Grupo *grupos, int a, int b)
    {
        a = encontrarRaiz(grupos, a);
        b = encontrarRaiz(grupos, b);

        if (grupos[a].tamanho < grupos[b].tamanho)
            swap(a, b);
        grupos[a].tamanho += grupos[b].tamanho;
        grupos[b].pai = a;
    }

    // criei essa classe pra facilitar a ordenacao
    // das arestas com menor peso (que faz parte do
    // algoritmo de Kruskal)
    class Aresta
    {
    public:
        int origem;
        int destino;
        int peso;
        Aresta(int origem, int destino, int peso)
            : origem(origem), destino(destino), peso(peso)
        {
        }
    };

    // sobrescrever operator< para que a priority_queue
    // ordene como desejamos
    friend bool operator<(const Aresta &a1, const Aresta &a2)
    {
        return a1.peso > a2.peso;
    }

    GrafoListaAdj *KruskalMST()
    {
        GrafoListaAdj *mst = new GrafoListaAdj();

        Grupo *gp = (Grupo *)malloc(sizeof(Grupo));
        gp = (Grupo *)calloc(vertices.size(), sizeof(Grupo));

        for (int i = 0; i < vertices.size(); i++)
        {
            gp[i].pai = i;
            gp[i].tamanho = 1;

            vector<pair<int, int>> aux;
            mst->arestas.push_back(aux);
        }

        priority_queue<Aresta> arestasMenorPeso;

        for (int i = 0; i < vertices.size(); i++)
            for (auto j : arestas[i])
                arestasMenorPeso.push(Aresta(i, j.first, j.second));

        while (!arestasMenorPeso.empty())
        {
            if (!mesmoGrupo(gp, arestasMenorPeso.top().origem, arestasMenorPeso.top().destino))
            {
                pair<int, int> aux;

                aux.first = arestasMenorPeso.top().destino;
                aux.second = arestasMenorPeso.top().peso;
                mst->arestas[arestasMenorPeso.top().origem].push_back(aux);

                aux.first = arestasMenorPeso.top().origem;
                aux.second = arestasMenorPeso.top().peso;
                mst->arestas[arestasMenorPeso.top().destino].push_back(aux);

                unirGrupos(gp, arestasMenorPeso.top().origem, arestasMenorPeso.top().destino); // faz a união
            }
            arestasMenorPeso.pop();
        }
        return mst;
    }

    vector<string> getVertices()
    {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas()
    {
        return arestas;
    }
};
