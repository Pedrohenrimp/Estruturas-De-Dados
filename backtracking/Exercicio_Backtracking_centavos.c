#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct elemento {
    int um;
    int cinco;
    int dez;
    int vinteCinco;
    int cinquenta;
    struct elemento *anterior, *proximo;
};

void ImprimirCombinacoesCentavos(int *vetor, int posicao, int valor, int vetorNumeros[]);
int SomarElementos(int *vetor, int tamanho);

int main(void) {
    int vetorNumeros[5] = {1, 5, 10, 25, 50};
    int valor = 6;
    int *vetor = (int *) malloc(sizeof(int) * valor);
    ImprimirCombinacoesCentavos(vetor, 0, valor, vetorNumeros);
    free(vetor);
}

void ImprimirCombinacoesCentavos(int *vetor, int posicao, int valor, int vetorNumeros[]) {
    int i;
    if(posicao > 0 && SomarElementos(vetor, posicao) == valor) {
        for(i = 0; i < posicao; i++) {
            printf("%d ", vetor[i]);
        }
        printf(" \n");
    }
    
    if(posicao <= valor) {
        for(i = 0; i < 5; i++) {
            vetor[posicao] = vetorNumeros[i];
            ImprimirCombinacoesCentavos(vetor, posicao + 1, valor, vetorNumeros);
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
