#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

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
bool Existe(int *vetor, int valor, int n);
void Caminhos(struct lista **grafo, int destino, int *vetor, int posicao);
void CaminhoMaisCurto(struct lista **grafo, int destino, int *vetor, int posicao, int **vetorCaminhos, int *posicaoVetorCaminhos);
void ImprimirCaminhoMaisCurto(int **vetorCaminhos, int tamanhoVetor);
void CaminhoMenorCusto(struct lista **grafo, int destino, struct caminho *vetor, int posicao, struct caminho **vetorCaminhos, int *posicaoVetorCaminhos);
bool ExisteCaminho(struct caminho *vetor, int valor, int n);
void ImprimirCaminhoMenorCusto(struct caminho **vetorCaminhos, int tamanhoVetor);
void DestruirGrafo(struct lista **grafo, int numeroDeNos);

void main(void) {
    int numeroDeNos = 4;
    struct lista **grafo = (struct lista *) malloc(sizeof(struct lista *) * (numeroDeNos + 1));
    InicializarGrafo(grafo, numeroDeNos);
    // gerar dados para o grafo.
    int i;
    for(i = 1; i < numeroDeNos; i++) {
        grafo[i] = InserirLista(grafo[i], i + 1, i);
    }
    grafo[4] = InserirLista(grafo[4], 3, 3);
    InserirAresta(grafo, 3, 2, 2);
    InserirAresta(grafo, 3, 1, 1);
    InserirAresta(grafo, 4, 1, 1);
    InserirAresta(grafo, 1, 3, 1);
    InserirAresta(grafo, 1, 4, 1);
    InserirAresta(grafo, 2, 1, 1);
    InserirAresta(grafo, 2, 4, 1);
    InserirAresta(grafo, 4, 2, 1);

    int opcao = 0;
    while(opcao != 9) {
        printf("\n--------    MENU    --------\n");
        printf("1) Inserir Aresta\n");
        printf("2) Remover Aresta\n");
        printf("3) Imprimir Grafo\n");
        printf("4) Imprimir Graus de Entrada e Saida\n");
        printf("5) Verificar Se o Grafo e Completo\n");
        printf("6) Imprimir Caminhos Entre Origem e Destino\n");
        printf("7) Imprimir Caminho Mais Curto entre Origem e Destino\n");
        printf("8) Imprimir Caminho com Menor Custo Entre a Origem e o Destino\n");
        printf("9) Sair\n");
        printf("\nDigite a opcao Desejada:\n");
        scanf(" %d", &opcao);

        int origem, destino, custo;
        int i;
        switch (opcao)
        {
        case 1:
            printf("Digite a Origem: ");
            scanf(" %d", &origem);
            printf("Digite o Destino: ");
            scanf(" %d", &destino);
            printf("Digite o Custo: ");
            scanf(" %d", &custo);
            InserirAresta(grafo, origem, destino, custo);
            printf("\nAresta Inserida com Sucesso!\n");
            break;
        
        case 2:
            printf("Digite a Origem: ");
            scanf(" %d", &origem);
            printf("Digite o Destino: ");
            scanf(" %d", &destino);
            RemoverAresta(grafo, origem, destino);
            printf("\nAresta Removida com Sucesso!\n");
            break;
        case 3:
            ImprimirGrafo(grafo, numeroDeNos);
            break;
        case 4:
            printf("Digite o Vertice: ");
            scanf(" %d", &origem);
            ImprimirGraus(grafo, origem, numeroDeNos);
            break;
        case 5:
            if(VerificarGrafoCompleto(grafo, numeroDeNos)) {
                printf("\nO Grafo e Completo!\n");
            }
            else {
                printf("\nO Grafo nao e Completo!\n");
            }
            break;
        case 6:
            printf("Digite a Origem: ");
            scanf(" %d", &origem);
            printf("Digite o Destino: ");
            scanf(" %d", &destino);
            int *vetor = (int *) malloc(sizeof(int) * numeroDeNos);
            vetor[0] = origem;
            Caminhos(grafo, destino, vetor, 1);
            free(vetor);
            break;
        case 7:
            printf("Digite a Origem: ");
            scanf(" %d", &origem);
            printf("Digite o Destino: ");
            scanf(" %d", &destino);
            int tamanhoVetorCaminhos = numeroDeNos * numeroDeNos;
            int **vetorCaminhos = (int *) malloc(sizeof(int *) * tamanhoVetorCaminhos);
            int *posicaoVetorCaminhos = (int *) malloc(sizeof(int));
            posicaoVetorCaminhos[0] = 0;
            int *vetor2 = (int *) malloc(sizeof(int) * numeroDeNos);
            vetor2[0] = origem;
            CaminhoMaisCurto(grafo, destino, vetor2, 1, vetorCaminhos, posicaoVetorCaminhos);
            ImprimirCaminhoMaisCurto(vetorCaminhos, posicaoVetorCaminhos[0]);
            free(vetor2);
            for(i = 0; i < posicaoVetorCaminhos[0]; i++) {
                free(vetorCaminhos[i]);
            }
            free(vetorCaminhos);
            free(posicaoVetorCaminhos);
            break;
        case 8:
            printf("Digite a Origem: ");
            scanf(" %d", &origem);
            printf("Digite o Destino: ");
            scanf(" %d", &destino);
            int tamanhoVetorCaminhos2 = numeroDeNos * numeroDeNos;
            struct caminho **vetorCaminhos2 = (struct caminho *) malloc(sizeof(struct caminho *) * tamanhoVetorCaminhos2);
            int *posicaoVetorCaminhos2 = (int *) malloc(sizeof(int));
            posicaoVetorCaminhos2[0] = 0;
            struct caminho *vetor3 = (struct caminho *) malloc(sizeof(struct caminho) * numeroDeNos);
            vetor3[0].destino = origem;
            CaminhoMenorCusto(grafo, destino, vetor3, 1, vetorCaminhos2, posicaoVetorCaminhos2);
            ImprimirCaminhoMenorCusto(vetorCaminhos2, posicaoVetorCaminhos2[0]);
            free(vetor3);
            for(i = 0; i < posicaoVetorCaminhos2[0]; i++) {
                free(vetorCaminhos2[i]);
            }
            free(posicaoVetorCaminhos2);
            free(vetorCaminhos2);
            break;
        case 9:
            printf("Encerrando...");
            DestruirGrafo(grafo, numeroDeNos);
            free(grafo);
            printf("\nEncerrado!");
            break;
        }
    }
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

bool Existe(int *vetor, int valor, int n) {
    int i;
    for(i = 0; i < n; i++) {
        if(vetor[i] == valor) {
            return true;
        }
    }
    return false;
}

void Caminhos(struct lista **grafo, int destino, int *vetor, int posicao) {
    if(vetor[posicao - 1] == destino) {
        printf("\n");
        int i;
        for(i = 0; i < posicao; i++) {
            printf("%d ", vetor[i]);
        }
    }
    else {
        struct lista *ponteiro = grafo[vetor[posicao - 1]];
        while(ponteiro != NULL) {
            if(!Existe(vetor, ponteiro->destino, posicao)) {
                vetor[posicao] = ponteiro->destino;
                Caminhos(grafo, destino, vetor, posicao + 1);
            }
            ponteiro = ponteiro->proximo;
        }
    }
}

void CaminhoMaisCurto(struct lista **grafo, int destino, int *vetor, int posicao, int **vetorCaminhos, int *posicaoVetorCaminhos) {
    if(vetor[posicao - 1] == destino) {
        int *vetorCaminho = (int *) malloc(sizeof(int) * posicao);
        int i;
        for(i = 0; i < posicao; i++) {
            vetorCaminho[i] = vetor[i];
        }
        vetorCaminhos[posicaoVetorCaminhos[0]] = vetorCaminho;
        posicaoVetorCaminhos[0]++;
    }
    else {
        struct lista *ponteiro = grafo[vetor[posicao - 1]];
        while(ponteiro != NULL) {
            if(!Existe(vetor, ponteiro->destino, posicao)) {
                vetor[posicao] = ponteiro->destino;
                CaminhoMaisCurto(grafo, destino, vetor, posicao + 1, vetorCaminhos, posicaoVetorCaminhos);
            }
            ponteiro = ponteiro->proximo;
        }
    }
}

void ImprimirCaminhoMaisCurto(int **vetorCaminhos, int tamanhoVetor) {
    int indiceMaisCurto;
    int tamanhoMaisCurto = 100000000;
    int i;
    for(i = 0; i < tamanhoVetor; i++) {
        if(_msize(vetorCaminhos[i]) / sizeof(int) < tamanhoMaisCurto) {
            indiceMaisCurto = i;
            tamanhoMaisCurto = _msize(vetorCaminhos[i]) / sizeof(int);
        }
    }
    printf("\nCaminho Mais Curto: ");
    for(i = 0; i < tamanhoMaisCurto; i++) {
        printf("%d ", vetorCaminhos[indiceMaisCurto][i]);
    }
}

void CaminhoMenorCusto(struct lista **grafo, int destino, struct caminho *vetor, int posicao, struct caminho **vetorCaminhos, int *posicaoVetorCaminhos) {
    if(vetor[posicao - 1].destino == destino) {
            vetor[0].custo = posicao; // guardar o tamanho do vetor no campo custo da posição zero do vetor.
            vetorCaminhos[posicaoVetorCaminhos[0]] = vetor;
            posicaoVetorCaminhos[0]++;
    }
    else {
        struct lista *ponteiro = grafo[vetor[posicao - 1].destino];
        while(ponteiro != NULL) {
            if(!ExisteCaminho(vetor, ponteiro->destino, posicao)) {
                vetor[posicao].destino = ponteiro->destino;
                vetor[posicao].custo = ponteiro->custo;
                CaminhoMenorCusto(grafo, destino, vetor, posicao + 1, vetorCaminhos, posicaoVetorCaminhos);
            }
            ponteiro = ponteiro->proximo;
        }
    }
}

bool ExisteCaminho(struct caminho *vetor, int valor, int n) {
    int i;
    for(i = 0; i < n; i++) {
        if(vetor[i].destino == valor) {
            return true;
        }
    }
    return false;
}

void ImprimirCaminhoMenorCusto(struct caminho **vetorCaminhos, int tamanhoVetor) {
    int indiceMenorCusto;
    int menorCusto = 100000000;
    int i, j;
    for(i = 0; i < tamanhoVetor; i++) {
        int somaCusto = 0;
        for(j = 1; j < vetorCaminhos[i][0].custo; j++) {
            somaCusto += vetorCaminhos[i][j].custo;
        }
        if(somaCusto < menorCusto) {
            menorCusto = somaCusto;
            indiceMenorCusto = i;
        }
    }
    printf("\nCaminho de Menor Custo: ");
    for(i = 0; i < vetorCaminhos[indiceMenorCusto][0].custo; i++) {
        printf("%d ", vetorCaminhos[indiceMenorCusto][i].destino);
    }
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

