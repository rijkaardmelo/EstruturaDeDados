#include <stdio.h>
#include <stdlib.h>

struct arraylist {
    int* vetor;
    int qtdade;
    int capacidade;
};

struct arraylist* inicializar(int capacidade) {
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));
    lista->vetor = (int*)calloc(capacidade, sizeof(int));
    lista->qtdade = 0;
    lista->capacidade = capacidade;
    return lista;
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
    int p;
    if(posicao >= 0 && posicao < lista->qtdade){
        p = lista->vetor[posicao];
    }
    return p;
}

void duplicarCapacidade(struct arraylist* lista) {
    lista->vetor = (int*)realloc(lista->vetor, 2*lista->capacidade*sizeof(int));
    lista->capacidade *= 2;
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
    if(lista->capacidade == lista->qtdade){
        duplicarCapacidade(lista);
    }
    lista->vetor[lista->qtdade] = valor;
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
    if(posicao >= 0 && posicao <= lista->qtdade){    
        if(lista->capacidade == lista->qtdade){
            duplicarCapacidade(lista);
        }
        for(int i = lista->qtdade; i > posicao; i--){
            lista->vetor[i] = lista->vetor[i-1];
        }
        lista->vetor[posicao] = valor;
        lista->qtdade++;
    }
}

void atualizarElemento(struct arraylist* lista, int valor, int posicao) {
     if(posicao >= 0 && posicao < lista->qtdade){    
        lista->vetor[posicao] = valor;
    }
}

void removerElementoNoFim(struct arraylist* lista) {
    lista->qtdade--;
}

void removerElementoEmPosicao(struct arraylist* lista, int posicao) {
    if(posicao >= 0 && posicao < lista->qtdade){    
        for(int i = posicao; i < lista->qtdade; i++){
            lista->vetor[i] = lista->vetor[i+1];
        }
        lista->qtdade--;
    }
}
void exibirLista(struct arraylist* lista) {
    printf("[");
    for (int i = 0; i < lista->qtdade; i++) {
        printf("%d", lista->vetor[i]);
        if (i < lista->qtdade - 1) {
            printf(", ");
        }
    }
    printf("]");
}
