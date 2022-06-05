#include <iostream>
#include <vector>
#include <queue>
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
        // IMPLEMENTAR
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i] == rotuloVertice)
                return i;
        return -1;
    }

    /**
     * O argumento indicesVerticesVisitados serve para controlar quais
     * vertices já foram visitados.
     * Lembrando que DFS é uma função recursiva.
     **/
    void dfs(string rotuloVOrigem, bool *indicesVerticesVisitados)
    {
        // IMPLEMENTAR
        int indice = obterIndiceVertice(rotuloVOrigem);

        if (indicesVerticesVisitados[indice])
            return;

        indicesVerticesVisitados[indice] = true;

        for (auto i : arestas[indice])
            dfs(vertices[i.first], indicesVerticesVisitados);
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
        // IMPLEMENTAR
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
        // IMPLEMENTAR
        pair<int, int> aux;
        aux.first = obterIndiceVertice(rotuloVDestino);
        aux.second = peso;
        arestas[obterIndiceVertice(rotuloVOrigem)].push_back(aux);
    }

    /**
     * Verifica se vértice rotuloVOrigem e vértice rotuloVDestino são
     * conectados (vizinhos).
     **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino)
    {
        // IMPLEMENTAR
        for (int i = 0; i < arestas[obterIndiceVertice(rotuloVOrigem)].size(); i++)
            if (obterIndiceVertice(rotuloVDestino) == arestas[obterIndiceVertice(rotuloVOrigem)][i].first)
                return true;
        return false;
    }

    /**
     * Verifica se há algum caminho entre vértice rotuloVOrigem e
     * vértice rotuloVDestino.
     * A melhor forma de fazer isto é reusando a função dfs.
     **/
    bool haCaminho(string rotuloVOrigem, string rotuloVDestino)
    {
        // IMPLEMENTAR
        bool* visitados = (bool*)malloc(sizeof(bool));
        visitados = (bool*)calloc(vertices.size(), sizeof(bool));

        if (rotuloVOrigem == rotuloVDestino)
            if (!saoConectados(rotuloVOrigem, rotuloVDestino))
                return false;

        for (int i = 0; i < vertices.size(); i++)
            visitados[i] = false;

        dfs(rotuloVOrigem, visitados);

        if (visitados[obterIndiceVertice(rotuloVDestino)])
            return true;
        else
            return false;
    }

    /**
     * Muda os rótulos do vértices dos diferentes componentes para
     * nomes que representam cores.
     * Dica: procura componentes partindo do vértice v0 ou v1, em ordem
     * crescente (mas você pode usar outra ordem se desejar).
     * Retorna a quantidade de componentes.
     * A melhor forma de fazer isto é reusando a função dfs.
     **/
    int colorir()
    {
        // IMPLEMENTAR
        int cor = 0;

        bool* visitados = (bool*)malloc(sizeof(bool));
        visitados = (bool*)calloc(vertices.size(), sizeof(bool));

        bool* aux = (bool*)malloc(sizeof(bool));
        aux = (bool*)calloc(vertices.size(), sizeof(bool));

        for (int i = 0; i < vertices.size(); i++)
            visitados[i] = false;

        for (int i = 0; i < vertices.size(); i++)
        {
            for (int i = 0; i < vertices.size(); i++)
                aux[i] = false;

            if (!visitados[i])
            {
                dfs(vertices[i], aux);

                for (int j = 0; j < vertices.size(); j++)
                    if (aux[j])
                    {
                        visitados[j] = aux[j];
                        vertices[j] = cor;
                    }

                cor++;
            }
        }
        return cor;
    }

    /**
     * Usa a abordagem de navegação BFS para listar as distâncias
     * entre o vértice rotuloVOrigem e cada um dos demais vértices.
     * A função BFS consegue listar a menor distância entre um vértice
     * e os demais se o grafo for NÃO-PONDERADO.
     * Retorna um vetor de inteiros com a quantidade de arestas
     * (distância) e o vértice rotuloVOrigem e cada um dos demais vértices.
     * Não é uma função recursiva.
     * É necessário utilizar a ED fila.
     **/
    int *bfs(string rotuloVOrigem)
    {
        // // IMPLEMENTAR
        queue<int> q;
        int indice = obterIndiceVertice(rotuloVOrigem);

        bool* visitados = (bool*)malloc(sizeof(bool));
        visitados = (bool*)calloc(vertices.size(), sizeof(bool));

        int *distancia = (int *)malloc(sizeof(int));
        distancia = (int *)calloc(vertices.size(), sizeof(int));

        for (int i = 0; i < vertices.size(); i++){
            visitados[i] = false;
            distancia[i] = 0;
        }

        visitados[indice] = true;
        q.push(indice);

        while (!q.empty())
        {
            int s = q.front();
            q.pop();

            for (auto u : arestas[s])
                if (!visitados[u.first])
                {
                    visitados[u.first] = true;
                    distancia[u.first] = distancia[s] + 1;
                    q.push(u.first);
                }
        }
        return distancia;
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
