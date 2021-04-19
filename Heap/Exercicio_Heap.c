#include <stdio.h>

#define MAX_ELEMENTOS 50
int totalElementos = 0;

int IndiceFilhoEsquerda(int x);
int IndiceFilhoDireita(int x);
int IndicePai(int x);
void InserirElemento(int *heap, int x);
void AjustarSubindo(int *heap, int posicao);
int RemoverElemento(int *heap);
void AjustarDescendo(int *heap, int posicao);
void ImprimirHeap(int *heap);


int main(void) {
    int heap[MAX_ELEMENTOS];

    int opcao = 0;
    while(opcao != 4) {
        printf("\n\n----------    MENU    ----------\n\n");
        printf("1) Inserir Elemento no Heap.\n");
        printf("2) Remover Elemento do Heap.\n");
        printf("3) Imprimir Heap.\n");
        printf("4) Sair.\n");
        scanf(" %d", &opcao);
        if(opcao == 1) {
            int valor;
            printf("Digite o valor do elemento que deseja inserir:\n");
            scanf(" %d", &valor);
            InserirElemento(heap, valor);
            printf("Elemento Inserido Com Sucesso!\n");
        }
        else if(opcao == 2) {
            int valorRemovido = RemoverElemento(heap);
            printf("O valor %d foi removido do Heap com sucesso!\n", valorRemovido);
        }
        else if(opcao == 3) {
                ImprimirHeap(heap);
        }
        else if(opcao == 4) {
            printf("Encerrando...\nEncerrado!");
        }
        else {
            printf("Digite um valor valido!\n");
        }
    }
}

int IndiceFilhoEsquerda(int x) {
    int indice = (2 * x) + 1;
    if(x >= totalElementos || indice >= totalElementos) {
        return -1;
    }
    else {
        return indice;
    }
}

int IndiceFilhoDireita(int x) {
    int indice = (2 * x) + 2;
    if(x >= totalElementos || indice >= totalElementos) {
        return -1;
    }
    else {
        return indice;
    }
}

int IndicePai(int x) {
    int indice = (int) floor((x - 1) / 2);
    if(x <= 0 || x >= totalElementos) {
        return -1;
    }
    else {
        return indice;
    }
}

void InserirElemento(int *heap, int x) {
    heap[totalElementos] = x;
    totalElementos++;
    AjustarSubindo(heap, totalElementos - 1);
}

void AjustarSubindo(int *heap, int posicao) {
    if(posicao != -1) {
        int posicaoPai = IndicePai(posicao);
        if(posicaoPai != -1) {
            if(heap[posicao] < heap[posicaoPai]) {
                int auxiliar = heap[posicao];
                heap[posicao] = heap[posicaoPai];
                heap[posicaoPai] = auxiliar;
                AjustarSubindo(heap, posicaoPai);
            }
        }
    }
}

int RemoverElemento(int *heap) {
    if(totalElementos == 0) {
        return -1;
    }
    else {
        int valorRemovido = heap[0];
        heap[0] = heap[totalElementos - 1];
        totalElementos--;
        AjustarDescendo(heap, 0);
        return valorRemovido;
    }
}

void AjustarDescendo(int *heap, int posicao) {
    if(posicao != -1 && IndiceFilhoEsquerda(posicao) != -1) {
        int indiceMenorFilho = IndiceFilhoEsquerda(posicao);
        if(IndiceFilhoDireita(posicao) != -1 && heap[IndiceFilhoDireita(posicao)] < heap[indiceMenorFilho]) {
            indiceMenorFilho = IndiceFilhoDireita(posicao);
        }
        if(heap[indiceMenorFilho] < heap[posicao]) {
            int auxiliar = heap[posicao];
            heap[posicao] = heap[indiceMenorFilho];
            heap[indiceMenorFilho] = auxiliar;
            AjustarDescendo(heap, indiceMenorFilho);
        }
    }
}

void ImprimirHeap(int *heap) {
    if(totalElementos == 0) {
        printf("\nHeap Vazio.");
    }
    else {
        printf("\n");
        int i;
        for(i = 0; i < totalElementos; i++) {
            printf("%d ", heap[i]);
        }
    }
}