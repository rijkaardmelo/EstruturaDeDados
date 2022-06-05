#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

#define POS_INF 1000000000
#define NEG_INF -1000000000

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

    /**
     * O argumento indicesVerticesVisitados serve para controlar quais
     * vertices já foram visitados.
     * Lembrando que DFS é uma função recursiva.
     **/
    void dfs(string rotuloVOrigem, bool *indicesVerticesVisitados)
    {
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

    /**
     * Verifica se vértice rotuloVOrigem e vértice rotuloVDestino são
     * conectados (vizinhos).
     **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino)
    {
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
        bool *visitados = (bool *)malloc(sizeof(bool));
        visitados = (bool *)calloc(vertices.size(), sizeof(bool));

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

        bool *visitados = (bool *)malloc(sizeof(bool));
        visitados = (bool *)calloc(vertices.size(), sizeof(bool));

        bool *aux = (bool *)malloc(sizeof(bool));
        aux = (bool *)calloc(vertices.size(), sizeof(bool));

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
        queue<int> q;
        int indice = obterIndiceVertice(rotuloVOrigem);

        bool *visitados = (bool *)malloc(sizeof(bool));
        visitados = (bool *)calloc(vertices.size(), sizeof(bool));

        int *distancia = (int *)malloc(sizeof(int));
        distancia = (int *)calloc(vertices.size(), sizeof(int));

        for (int i = 0; i < vertices.size(); i++)
        {
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

    /**
     * Usamos o BellmanFord para encontrar menor caminho
     * em grafos com arestas com pesos negativos.
     * O BellmanFord consegue detectar ciclos negativos
     * e atribuir o valor NEG_INF (constante definida nesse arquivo)
     * aos vértices que pertençam ao ciclo.
     * POS_INF deve ser atribuído aos vértices inalcançáveis.
     * O aspecto negativo é sua complexidade de tempo: O(V*E).
     * Isto acontece pois, como possui arestas negativas, cada vértice
     * do grafo precisa ser processado V vezes.
     * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#bellman-ford
     **/
    int *bellmanFord(string rotuloVOrigem)
    {
        int *distance = (int *)malloc(sizeof(int));
        distance = (int *)calloc(vertices.size(), sizeof(int));

        for (int i = 0; i < vertices.size(); i++)
            distance[i] = POS_INF;

        distance[obterIndiceVertice(rotuloVOrigem)] = 0;

        for (int i = 1; i <= vertices.size() - 1; i++)
            for (int j = 0; j < arestas.size(); j++)
                for (auto k : arestas[j])
                    distance[k.first] = min(distance[k.first], distance[j] + k.second);

        for (int j = 0; j < arestas.size(); j++)
            for (auto k : arestas[j])
                if (distance[j] + k.second < distance[k.first])
                    distance[k.first] = NEG_INF;

        return distance;
    }

    /**
     * Usamos o Dijkstra para encontrar menor caminho
     * em grafos sem arestas com pesos negativos.
     * O Dijkstra retorna respostas incorretas caso o grafo
     * possua arestas negativas, e portanto não consegue
     * detectar ciclos negativos. Este é o aspecto negativo.
     * POS_INF deve ser atribuído aos vértices inalcançáveis.
     * O aspecto positivo é sua complexidade de tempo: O(V+E).
     * Isto acontece pois, como o grafo não possui arestas negativas,
     * cada vértice do grafo precisa ser processado apenas 1 vez.
     * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#dijkstra
     * Ilustração: https://docs.google.com/drawings/d/1NmkJPHpcg8uVcDZ24FQiYs3uHR5n-rdm1AZwD74WiMY/edit?usp=sharing
     **/
    int *dijkstra(string rotuloVOrigem)
    {
        queue<pair<int, int>> q;

        bool *visitados = (bool *)malloc(sizeof(bool));
        visitados = (bool *)calloc(vertices.size(), sizeof(bool));

        int *distancia = (int *)malloc(sizeof(int));
        distancia = (int *)calloc(vertices.size(), sizeof(int));

        for (int i = 0; i < vertices.size(); i++)
        {
            distancia[i] = POS_INF;
            visitados[i] = false;
        }

        distancia[obterIndiceVertice(rotuloVOrigem)] = 0;
        q.push({0, obterIndiceVertice(rotuloVOrigem)});

        while (!q.empty())
        {
            int a = q.front().second;
            q.pop();

            if (visitados[a])
                continue;
            visitados[a] = true;

            for (auto u : arestas[a])
            {
                int b = u.first, w = u.second;
                if (distancia[a] + w < distancia[b])
                {
                    distancia[b] = distancia[a] + w;
                    q.push({-distancia[b], b});
                }
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
