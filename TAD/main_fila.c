#include "fila.h"
#include <stdio.h>

int main(void) {
    Fila fila = InicializarFila();

    int valor, resposta;
    int opcao = 0;
    while(opcao != 4) {
        printf("\n\n--------    MENU    --------\n\n");
        printf("Escolha uma das opcoes a seguir:\n\n");
        printf("1) Enfileirar elemento\n");
        printf("2) Desenfileirar elemento\n");
        printf("3) Imprimir Fila\n");
        printf("4) Sair.\n\n");
        scanf(" %d", &opcao);
        
        if(opcao == 1) {
            printf("Digite o valor que deseja Enfileirar:\n");
            scanf(" %d", &valor);
            resposta = Enfileirar(fila, valor);
            if(resposta == 1) {
                printf("Valor %d Enfileirado com sucesso!\n", valor);
            }
            else {
                printf("Fila cheia! nao foi possivel Enfileirar!\n");
            }
        }
        else if(opcao == 2) {
            resposta = Desenfileirar(fila, &valor);
            if(resposta == 1) {
                printf("Valor %d Desenfileirado com sucesso!\n", valor);
            }
            else {
                printf("Fila vazia! nao foi possivel Desenfileirar!\n");
            }
        }
        else if(opcao == 3) {
            ImprimirFila(fila);
        }
        else if(opcao == 4) {
            printf("Encerrando...\n");
            DestruirFila(fila);
            printf("Encerrado!");
        }
        else {
            printf("Escolha uma opcao valida!\n");
        }
    }
}