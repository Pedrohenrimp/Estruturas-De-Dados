#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_VETOR 4

void SubconjutosSomaImpar(int *vetor, int *vetorBool, int k, int n);
int SomarElementos(int *vetor, int *vetorBool, int tamanho);

void main(void) {

    int *vetor = (int *) malloc(sizeof(int) * TAMANHO_VETOR);
    bool *vetorBool = (bool *) malloc(sizeof(bool) * TAMANHO_VETOR);
    int i;
    for(i = 0; i < TAMANHO_VETOR; i++) {
        vetor[i] = i + 1;
        vetorBool[i] = false;
    }

    SubconjutosSomaImpar(vetor, vetorBool, 0, TAMANHO_VETOR);
    free(vetor);
    free(vetorBool);
}

void SubconjutosSomaImpar(int *vetor, int *vetorBool, int k, int n) {
    if(k == n) {
        if(SomarElementos(vetor, vetorBool, n) % 2 != 0) {
            printf("{");
            int i;
            for(i = 0; i < n; i++) {
                if(vetorBool[i] == true) {
                    printf(" %d ", vetor[i]);
                }
            }
            printf("}\n");
        }
    }
    else {
        vetorBool[k] = true;
        SubconjutosSomaImpar(vetor, vetorBool, k + 1, n);
        vetorBool[k] = false;
        SubconjutosSomaImpar(vetor, vetorBool, k + 1, n);
    }
}

int SomarElementos(int *vetor, int *vetorBool, int tamanho) {
    int i;
    int soma = 0;
    for(i = 0; i < tamanho; i++) {
        if(vetorBool[i] == true) {
            soma += vetor[i];
        }
    }
    return soma;
}