#include <stdio.h>
#include <stdlib.h>

void ImprimirCombinacoesComMaisAs(char *vetor, int posicao, int tamanho, char vetorLetras[]);
int ContarOcorrencias(char *vetor, char letra, int tamanho);

int main(void) {
    char vetorLetras[3];
    vetorLetras[0] = 'a';
    vetorLetras[1] = 'e';
    vetorLetras[2] = 'i';
    int tamanho = 5;
    char *vetor = (char *) malloc(sizeof(char) * tamanho);
    ImprimirCombinacoesComMaisAs(vetor, 0, tamanho, vetorLetras);
    free(vetor);
}

void ImprimirCombinacoesComMaisAs(char *vetor, int posicao, int tamanho, char vetorLetras[]) {
    int i;
    if(posicao == tamanho) {
        if(ContarOcorrencias(vetor, vetorLetras[0], tamanho) > tamanho / 2) {
            for(i = 0; i < tamanho; i++) {
                printf("%c", vetor[i]);
            }
            printf(" \n");
        }
    }
    else {
        for(i = 0; i < 3; i++) {
            vetor[posicao] = vetorLetras[i];
            ImprimirCombinacoesComMaisAs(vetor, posicao + 1, tamanho, vetorLetras);
        }
    }
}

int ContarOcorrencias(char *vetor, char letra, int tamanho) {
    int i;
    int contador = 0;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i] == letra) {
            contador++;
        }
    }
    return contador;
}