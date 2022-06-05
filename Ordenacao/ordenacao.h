#include <climits>
#include <stdbool.h>
#include <stdlib.h>

void swap(int *v, int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void selectionSortOP(int **v, int tamanho)
{
    int *ordenado = (int *)malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++)
    {
        int iMenor = 0;
        for (int j = 0; j < tamanho; j++)
            if ((*v)[j] < (*v)[iMenor])
                iMenor = j;

        ordenado[i] = (*v)[iMenor];
        (*v)[iMenor] = INT_MAX;
    }

    (*v) = ordenado;
}

void selectionSortIP(int *v, int tamanho)
{
    for (int i = 0; i < (tamanho - 1); i++)
    {
        int iMenor = i;

        for (int j = i + 1; j < tamanho; j++)
            if (v[j] < v[iMenor])
                iMenor = j;

        swap(v, i, iMenor);
    }
}

void bubbleSort(int *v, int n)
{
    for (int varredura = 0; varredura < n - 1; varredura++)
    {
        bool trocou = false;

        for (int i = 0; i < n - varredura - 1; i++)
            if (v[i] > v[i + 1])
            {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                trocou = true;
            }

        if (trocou == false)
            return;
    }
}

void insertionSortOP(int **v, int tamanho)
{
    int *ordenado = (int *)malloc(tamanho * sizeof(int));
    ordenado[0] = (*v)[0];

    for (int i = 1; i < tamanho; i++)
    {
        int j;

        for (j = 0; j < i; j++)
        {
            if (ordenado[j] > (*v)[i])
            {
                for (int k = j; k < i; k++)
                    ordenado[k + 1] = ordenado[k];
                break;
            }
        }

        ordenado[j] = (*v)[i];
    }

    (*v) = ordenado;
}

void insertionSortIPV1(int *v, int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        int j;

        for (j = 0; j < i; j++)
            if (v[j] > v[i])
            {
                for (int k = j; k < i; k++)
                    v[k + 1] = v[k];
                break;
            }

        v[j] = v[i];
    }
}

void insertionSortIPV2(int *v, int tamanho)
{
    for (int i = 1; i < tamanho; i++)
        for (int j = i; j > 0; j--)
        {
            if (v[j - 1] > v[j])
            {
                int temp = v[j - 1];
                v[j - 1] = v[j];
                v[j] = temp;
            }
            else
                break;
        }
}

void insertionSortIPV3(int *v, int tamanho)
{
    for (int i = 1; i < tamanho; i++)
        for (int j = i; j > 0 && v[j - 1] > v[j]; j--)
        {
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
        }
}

void insertionSortIPV4(int *v, int tamanho)
{
    for (int i = 1; i < tamanho; i++)
        for (int j = i; j > 0 && v[j - 1] > v[j]; j--)
        {
            int temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
        }
}

void insertionSortIPV5(int *v, int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        int valor = v[i];
        int j;

        for (j = i; j > 0 && v[j - 1] > valor; j--)
            v[j] = v[j - 1];

        v[j] = valor;
    }
}

void merge(int *v, int tamV, int *e, int tamE, int *d, int tamD)
{
    int indexV = 0;
    int indexE = 0;
    int indexD = 0;

    while (indexE < tamE && indexD < tamD)
    {
        if (e[indexE] <= d[indexD])
        {
            v[indexV] = e[indexE];
            indexE++;
        }
        else
        {
            v[indexV] = d[indexD];
            indexD++;
        }

        indexV++;
    }

    while (indexE < tamE)
    {
        v[indexV] = e[indexE];
        indexE++;
        indexV++;
    }

    while (indexD < tamD)
    {
        v[indexV] = d[indexD];
        indexD++;
        indexV++;
    }
}

void mergeSort(int *v, int tamV)
{
    if (tamV > 1)
    {
        int meio = tamV / 2;
        int tamV1 = meio;
        int *v1 = (int *)malloc(tamV1 * sizeof(int));

        for (int i = 0; i < meio; i++)
            v1[i] = v[i];

        int tamV2 = tamV - meio;
        int *v2 = (int *)malloc(tamV2 * sizeof(int));

        for (int i = meio; i < tamV; i++)
            v2[i - meio] = v[i];

        mergeSort(v1, tamV1);
        mergeSort(v2, tamV2);
        merge(v, tamV, v1, tamV1, v2, tamV2);

        free(v1);
        free(v2);
    }
}

int particiona(int *v, int ini, int fim)
{
    int pIndex = ini;
    int pivo = v[fim];

    for (int i = ini; i < fim; i++)
        if (v[i] <= pivo)
        {
            swap(v, i, pIndex);
            pIndex++;
        }

    swap(v, pIndex, fim);

    return pIndex;
}

void quickSort(int *v, int ini, int fim)
{
    if (fim > ini)
    {
        int indexPivo = particiona(v, ini, fim);
        quickSort(v, ini, indexPivo - 1);
        quickSort(v, indexPivo + 1, fim);
    }
}

int particionaRP(int *v, int ini, int fim)
{
    int sorteado = ini + (rand() % (fim - ini));
    int pIndex = ini;
    int pivo = v[fim];

    swap(v, sorteado, fim);

    for (int i = ini; i < fim; i++)
        if (v[i] <= pivo)
        {
            swap(v, i, pIndex);
            pIndex++;
        }

    swap(v, pIndex, fim);

    return pIndex;
}

void quickSortRP(int *v, int ini, int fim)
{
    if (fim > ini)
    {
        int indexPivo = particiona(v, ini, fim);
        quickSort(v, ini, indexPivo - 1);
        quickSort(v, indexPivo + 1, fim);
    }
}

void countingSort(int **v, int tam)
{
    int iMenorValor = 0;
    int iMaiorValor = 0;
    int *ordenado = (int *)malloc(tam * sizeof(int));
    bool *adicionado = (bool *)calloc(tam, sizeof(bool));

    for (int i = 0; i < tam; i++)
    {
        if ((*v)[i] < (*v)[iMenorValor])
            iMenorValor = i;
        if ((*v)[i] > (*v)[iMaiorValor])
            iMaiorValor = i;
    }

    int tamContagem = (*v)[iMaiorValor] - (*v)[iMenorValor] + 1;
    int *contagem = (int *)calloc(tamContagem, sizeof(int));

    for (int i = 0; i < tam; i++)
    {
        int indiceEmContagem = (*v)[i] - (*v)[iMenorValor];
        contagem[indiceEmContagem]++;
    }

    for (int i = 1; i < tamContagem; i++)
        contagem[i] += contagem[i - 1];

    for (int i = 0; i < tam; i++)
    {
        int indiceOrdenado = contagem[(*v)[i] - (*v)[iMenorValor]] - 1;

        while (adicionado[indiceOrdenado])
            indiceOrdenado--;

        ordenado[indiceOrdenado] = (*v)[i];
        adicionado[indiceOrdenado] = true;
    }

    (*v) = ordenado;
}
