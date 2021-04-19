#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_VETOR 100

struct fila {
    int vetor[TAMANHO_VETOR];
    int final;
    int inicio;
};

Fila InicializarFila() {
    Fila novaFila = (Fila) malloc(sizeof(struct fila));
    novaFila->inicio = 0;   // posicao primeiro elemento
    novaFila->final = -1;    // posicao ultimo elemento
    return novaFila;
}

//funcao auxiliar
bool filaCheia(Fila fila) {
    if(fila->final == TAMANHO_VETOR) {
        return true;
    }
    else {
        return false;
    }
}

int Enfileirar(Fila fila, int valor) {
    if(filaCheia(fila)) {
        return 0;
    }
    else {
        fila->final++;
        fila->vetor[fila->final] = valor;
        return 1;
    }
}

// funcao auxiliar
bool filaVazia(Fila fila) {
    if(fila->final == -1) {
        return true;
    }
    else {
        return false;
    }
}

int Desenfileirar(Fila fila, int *endereco) {
    if(filaVazia(fila)) {
        return 0;
    }
    else {
        *endereco = fila->vetor[0];
        int i;
        for(i = 0; i < fila->final; i++) {
            fila->vetor[i] = fila->vetor[i + 1];
        }
        fila->final--;
        return 1;
    }
}

void ImprimirFila(Fila fila) {
    printf("\nElementos: ");
    int i;
    for(i = 0; i <= fila->final; i++) {
        printf("%d ", fila->vetor[i]);
    }
}

Fila DestruirFila(Fila fila) {
    free(fila);
    return NULL;
}