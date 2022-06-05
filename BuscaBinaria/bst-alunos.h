#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct noBst
{
    int val;
    struct noBst *esq;
    struct noBst *dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL. 
 **/
struct noBst *alocarNovoNo(int val)
{
    struct noBst *no = (struct noBst *)malloc(sizeof(struct noBst));
    no->val = val;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

/**
 * Funcao que recebe a raiz de uma BST, e 
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz são passados por referência.
 **/
void inserir(struct noBst **raiz, int val, int *tamanho)
{
    if ((*raiz) == NULL)
    {
        (*raiz) = alocarNovoNo(val);
        (*tamanho)++;
    }
    else
    {
        if (val > (*raiz)->val)
            inserir(&(*raiz)->dir, val, tamanho++);
        else
            inserir(&(*raiz)->esq, val, tamanho++);
    }
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * verifica se a mesma contém um dado valor.
 **/
bool buscar(struct noBst *raiz, int val)
{
    if (raiz == NULL)
        return false;

    if (raiz->val == val)
        return true;
    else if (raiz->val < val)
        return buscar(raiz->dir, val);
    else if (raiz->val > val)
        return buscar(raiz->esq, val);

    return false;
}

/**
 * Funcao que retorna o maior valor de uma BST.
 **/
int max(struct noBst *raiz)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->dir != NULL)
        return max(raiz->dir);

    return raiz->val;
}

/**
 * Funcao que retorna o menor valor de uma BST.
 **/
int min(struct noBst *raiz)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->esq != NULL)
        return min(raiz->esq);

    return raiz->val;
}

/**
 * Funcao que retorna a altura de uma BST.
 * A altura de uma BST é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 **/
int altura(struct noBst *raiz)
{
    if (raiz == NULL || (raiz->esq == NULL && raiz->dir == NULL))
        return 0;
    else
    {
        int aEsq = altura(raiz->esq);
        int aDir = altura(raiz->dir);

        if (aEsq > aDir)
            return (aEsq + 1);
        else
            return (aDir + 1);
    }
}

/**
 * Funcao que navega em-ordem na BST e
 * imprime seus elementos.
 **/
void emOrdem(struct noBst *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esq);
        printf("%i ", raiz->val);
        emOrdem(raiz->dir);
    }
}

/**
 * Funcao que navega pre-ordem na BST e
 * imprime seus elementos.
 **/
void preOrdem(struct noBst *raiz)
{
    if (raiz != NULL)
    {
        printf("%i ", raiz->val);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

/**
 * Funcao que navega pos-ordem na BST e
 * imprime seus elementos.
 **/
void posOrdem(struct noBst *raiz)
{
    if (raiz != NULL)
    {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%i ", raiz->val);
    }
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * remove o no que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho é passado por referência.
 **/
struct noBst *remover(struct noBst *raiz, int val, int *tamanho)
{
    if (raiz == NULL)
        return raiz;

    if (raiz->val > val)
    {
        raiz->esq = remover(raiz->esq, val, tamanho--);
        return raiz;
    }
    else if (raiz->val < val)
    {
        raiz->dir = remover(raiz->dir, val, tamanho--);
        return raiz;
    }

    noBst *temp = NULL;

    if (raiz->esq == NULL)
    {
        temp = raiz->dir;
        delete raiz;
        return temp;
    }
    else if (raiz->dir == NULL)
    {
        temp = raiz->esq;
        delete raiz;
        return temp;
    }
    else
    {
        temp = raiz;
        noBst *prox = raiz->dir;

        while (prox->esq != NULL)
        {
            temp = prox;
            prox = prox->esq;
        }

        if (temp != raiz)
            temp->esq = prox->dir;
        else
            temp->dir = prox->dir;

        raiz->val = prox->val;

        delete prox;
        return raiz;
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}