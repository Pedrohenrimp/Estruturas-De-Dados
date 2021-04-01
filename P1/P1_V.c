#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_GRAFO 4

struct lista {
    int destino;
    int custo;
    struct lista *proximo;
};

struct caminho {
    int destino;
    int custo;
};

void InicializarGrafo(struct lista **grafo, int numeroDeNos);
struct lista *InserirLista(struct lista *lista, int destino, int custo);
void InserirAresta(struct lista **grafo, int origem, int destino, int custo);
void RemoverAresta(struct lista **grafo, int origem, int destino);
void ImprimirLista(struct lista *lista);
void ImprimirGrafo(struct lista **grafo, int numeroDeNos);
int ContarGrauEntrada(struct lista **grafo, int no, int numeroDeNos);
int ContarGrauSaida(struct lista *lista);
void ImprimirGraus(struct lista **grafo, int no, int numeroDeNos);
bool VerificarGrafoCompleto(struct lista **grafo, int numeroDeNos);
void CaminhosAteCusto(struct lista **grafo, int destino, struct caminho *vetor, int posicao, int valor, int *quantidade);
bool Existe(struct caminho *vetor, int valor, int n);
void DestruirGrafo(struct lista **grafo, int numeroDeNos);

void main(void) {
    int origem = 1;
    int destino = 4;
    int valor = 6;
    int *quantidade = (int *) malloc(sizeof(int));
    quantidade[0] = 0;
    
    struct lista **grafo = (struct lista *) malloc(sizeof(struct lista *) * (TAMANHO_GRAFO + 1));
    InicializarGrafo(grafo, TAMANHO_GRAFO);
    // gerar dados para o grafo.
    int i;
    for(i = 1; i < TAMANHO_GRAFO; i++) {
        grafo[i] = InserirLista(grafo[i], i + 1, i);
    }
    grafo[TAMANHO_GRAFO] = InserirLista(grafo[4], 3, 3);
    InserirAresta(grafo, 3, 2, 2);
    InserirAresta(grafo, 3, 1, 1);
    InserirAresta(grafo, 4, 1, 1);
    InserirAresta(grafo, 1, 3, 1);
    InserirAresta(grafo, 1, 4, 1);
    InserirAresta(grafo, 2, 1, 1);
    InserirAresta(grafo, 2, 4, 1);
    InserirAresta(grafo, 4, 2, 1);
    

    struct caminho *vetor = (struct caminho *) malloc(sizeof(struct caminho) * TAMANHO_GRAFO);
    vetor[0].destino = origem;
    CaminhosAteCusto(grafo, destino, vetor, 1, valor, quantidade);
    printf("%d", quantidade[0]);
    ImprimirGrafo(grafo, TAMANHO_GRAFO);
    free(quantidade);
}

void InicializarGrafo(struct lista **grafo, int numeroDeNos) {
    int i;
    for(i = 0; i <= numeroDeNos; i++) {
        grafo[i] = NULL;
    }
}

struct lista *InserirLista(struct lista *lista, int destino, int custo) {
    struct lista *no = (struct lista *) malloc(sizeof(struct lista));
    no->destino = destino;
    no->custo = custo;
    no->proximo = lista;
    return no;
}

void InserirAresta(struct lista **grafo, int origem, int destino, int custo) {
    grafo[origem] = InserirLista(grafo[origem], destino, custo);
}

void RemoverAresta(struct lista **grafo, int origem, int destino) {
    struct lista *auxiliarFrente = grafo[origem]->proximo;
    struct lista *auxiliarTras = grafo[origem];
    if(auxiliarTras->destino == destino) {
        grafo[origem] = auxiliarFrente;
        free(auxiliarTras);
    }
    else {
        while(auxiliarFrente != NULL) {
            if(auxiliarFrente->destino == destino) {
                auxiliarTras->proximo = auxiliarFrente->proximo;
                free(auxiliarFrente);
                break;
            }
            else {
                auxiliarTras = auxiliarFrente;
                auxiliarFrente = auxiliarFrente->proximo;
            }
        }
    }
}

void ImprimirLista(struct lista *lista) {
    if(lista != NULL) {
        printf("-(%d, %d)", lista->destino, lista->custo);
        ImprimirLista(lista->proximo);
    }
}

void ImprimirGrafo(struct lista **grafo, int numeroDeNos) {
    int i;
    printf("-----  Grafo   -----");
    for(i = 0; i <= numeroDeNos; i++) {
        printf("\n\t%d", i);
        ImprimirLista(grafo[i]);
    }
}

int ContarGrauEntrada(struct lista **grafo, int no, int numeroDeNos) {
    int contador = 0;
    int i;
    for(i = 1; i <= numeroDeNos; i++) {
        struct lista *auxiliar = grafo[i];
        while (auxiliar != NULL) {
            if(auxiliar->destino == no) {
                contador++;
                break;
            }
            else {
                auxiliar = auxiliar->proximo;
            }
        }   
    }
    return contador;
}

int ContarGrauSaida(struct lista *lista) {
    struct lista *auxiliar = lista;
    int contador = 0;
    while(auxiliar != NULL) {
        contador++;
        auxiliar = auxiliar->proximo;
    }
    return contador;
}

void ImprimirGraus(struct lista **grafo, int no, int numeroDeNos) {
    int grauEntrada = ContarGrauEntrada(grafo, no, numeroDeNos);
    int grauSaida = ContarGrauSaida(grafo[no]);
    printf("Vertice: %d\nGrau de Entrada: %d    Grau de Saida: %d\n", no, grauEntrada, grauSaida);
}

bool VerificarGrafoCompleto(struct lista **grafo, int numeroDeNos) {
    bool completo = true;
    int grauEntrada, grauSaida;
    int i;
    for(i = 1; i <= numeroDeNos; i++) {
        grauEntrada = ContarGrauEntrada(grafo, i, numeroDeNos);
        grauSaida = ContarGrauSaida(grafo[i]);
        if( grauEntrada < (numeroDeNos - 1) || grauSaida < (numeroDeNos - 1)) {
            completo = false;
        }
    }
    return completo;
}

void CaminhosAteCusto(struct lista **grafo, int destino, struct caminho *vetor, int posicao, int valor, int *quantidade) {
    if(vetor[posicao - 1].destino == destino) {
        int custoFinal = 0;
        int i;
        for(i = 1; i < posicao; i++) {
            custoFinal += vetor[i].custo;
        }
        if(custoFinal < valor) {
            quantidade[0]++;
        }
    }
    else {
        struct lista *ponteiro = grafo[vetor[posicao - 1].destino];
        while(ponteiro != NULL) {
            if(!Existe(vetor, ponteiro->destino, posicao)) {
                vetor[posicao].destino = ponteiro->destino;
                vetor[posicao].custo = ponteiro->custo;
                CaminhosAteCusto(grafo, destino, vetor, posicao + 1, valor, quantidade);
            }
            ponteiro = ponteiro->proximo;
        }
    }
}

bool Existe(struct caminho *vetor, int valor, int n) {
    int i;
    for(i = 0; i < n; i++) {
        if(vetor[i].destino == valor) {
            return true;
        }
    }
    return false;
}

void DestruirGrafo(struct lista **grafo, int numeroDeNos) {
    int i;
    for(i = 1; i <= numeroDeNos; i++) {
        struct lista *auxiliar = grafo[i];
        while(auxiliar != NULL) {
            RemoverAresta(grafo, i, auxiliar->destino);
            auxiliar = auxiliar->proximo;
        }
        free(grafo[i]);
    }
}

