#include <stdio.h>
#include <stdlib.h>

void ImprimirCombinacoesComSomaPar(int *vetor, int posicao, int tamanho, int vetorNumeros[]);
int SomarElementos(int *vetor, int tamanho);

int main(void) {
    int vetorNumeros[4] = {15, 31, 55, 44};
    int tamanho = 3;
    int *vetor = (int *) malloc(sizeof(int) * tamanho);
    ImprimirCombinacoesComSomaPar(vetor, 0, tamanho, vetorNumeros);
    free(vetor);
}

void ImprimirCombinacoesComSomaPar(int *vetor, int posicao, int tamanho, int vetorNumeros[]) {
    int i;
    if(posicao == tamanho) {
        if((SomarElementos(vetor, tamanho) % 2) == 0) {
            for(i = 0; i < tamanho; i++) {
                printf("%d ", vetor[i]);
            }
            printf(" \n");
        }
    }
    else {
        for(i = 0; i < 4; i++) {
            vetor[posicao] = vetorNumeros[i];
            ImprimirCombinacoesComSomaPar(vetor, posicao + 1, tamanho, vetorNumeros);
        }
    }
}

int SomarElementos(int *vetor, int tamanho) {
    int i;
    int soma = 0;
    for(i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    return soma;
}