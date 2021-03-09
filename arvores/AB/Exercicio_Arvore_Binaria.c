#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct arvore {
    int info;
    struct arvore *esq;
    struct arvore *dir;
};

FILE *arquivo;
struct arvore *LerArquivo(FILE *arquivo);
void ImprimirPreOrdem(struct arvore *arvore);
void ImprimirEmOrdem(struct arvore *arvore);
void ImprimirPosOrdem(struct arvore *arvore);
bool VerificarExistencia(struct arvore *arvore, int valor);
struct arvore *DestruirArvore(struct arvore *arvore);
int AlturaArvore(struct arvore *arvore);
void ImprimirNivel(struct arvore *arvore, int contador, int nivel);
int QuantidadeNoNivel(struct arvore *arvore, int contador, int nivel);
void ImprimirEmLargura(struct arvore *arvore);
int QuantidadeNaArvore(struct arvore *arvore);
void ImprimirFolhas(struct arvore *arvore);
int AlturaEsquerda(struct arvore *arvore);
int AlturaDireita(struct arvore *arvore);
bool VerificarBalanceamento(struct arvore *arvore);
int Pot(int base, int expoente);
bool VerificarArvoreCheia(struct arvore *arvore);
bool ImprimirQualNivel(struct arvore *arvore, int nivel, int valor);



int main(void) {
    char nome[40];
    printf("Digite o nome do arquivo da arvore que deseja carregar:\n");
    scanf(" %s", nome);
    arquivo = fopen(nome, "rt");
    struct arvore *arvore = LerArquivo(arquivo);
    fclose(arquivo);

    bool executando = true;
    while(executando) {

        int opcao = 0;
        printf("\n\nEscolha Uma das Opcoes Abaixo:\n\n");
        printf("1 - Imprimir arvore\n");
        printf("2 - Verificar se um elemento existe na arvore\n");
        printf("3 - Contar o numero de elementos na arvore\n");
        printf("4 - Imprimir nos folhas da arvore\n");
        printf("5 - Verificar se a arvore esta balanceada\n");
        printf("6 - Verificar se a arvore e cheia\n");
        printf("7 - Imprimir o nivel de um elemento (no)\n");
        printf("8 - Sair\n");
        scanf(" %d", &opcao);

        int tipo, valor, quantidade;
        bool imprimiu;
        switch (opcao)
        {
        case 1:
            printf("\n\nEscolha Uma das Opcoes Abaixo:\n\n");
            printf("1 - Imprimir Pre - Ordem\n");
            printf("2 - Imprimir Em Ordem\n");
            printf("3 - Imprimir Pos - Ordem\n");
            printf("4 - Imprimir Em Largura\n");
            scanf(" %d", &tipo);
            switch (tipo)
            {
            case 1:
                printf("\n\nArvore Pre - Ordem:\n");
                ImprimirPreOrdem(arvore);
                printf("\n");
                break;
            
            case 2:
                printf("\n\nArvore Em Ordem:\n");
                ImprimirEmOrdem(arvore);
                printf("\n");
                break;
            case 3:
                printf("\n\nArvore Pos - Ordem:\n");
                ImprimirPosOrdem(arvore);
                printf("\n");
                break;
            case 4:
                printf("\n\nArvore Em Largura:\n");
                ImprimirEmLargura(arvore);
                printf("\n");
            }
            break;
        
        case 2:
            printf("\n\nDigite o valor do elemento que deseja verificar:\n");
            scanf(" %d", &valor);
            if(VerificarExistencia(arvore, valor)) {
                printf("\nA arvore contem o elemento %d.\n", valor);
            }
            else {
                printf("\nElemento %d nao encontrado na arvore.\n", valor);
            }
            break;
        case 3:
            quantidade = QuantidadeNaArvore(arvore);
            printf("\n\nA arvore possui %d elementos.\n", quantidade);
            break;
        case 4:
            printf("\n\nNos folhas da arvore:\n");
            ImprimirFolhas(arvore);
            break;
        case 5:
            if(VerificarBalanceamento(arvore)) {
                printf("\n\nA arvore esta balanceada.\n");
            }
            else {
                printf("\n\nA arvore nao esta balanceada.\n");
            }
            break;
        case 6:
            if(VerificarArvoreCheia(arvore)) {
                printf("\n\nA arvore e uma arvore cheia.\n");
            }
            else {
                printf("\n\nA arvore nao e uma arvore cheia.\n");
            }
            break;
        case 7:
            printf("\n\nDigite o valor do elemento que deseja imprimir o nivel:\n");
            scanf(" %d", &valor);
            printf("\nNivel do elemento:\n");
            imprimiu = ImprimirQualNivel(arvore, 0, valor);
            if(!imprimiu) {
                printf("\nElemento %d nao encontrado na arvore.\n",  valor);
            }
            break;
        case 8:
            printf("\nEncerrando...\n");
            arvore = DestruirArvore(arvore);
            printf("\n\n\nEncerrado!\n");
            executando = false;
            break;
        }
    }

}

struct arvore *LerArquivo(FILE *arquivo) {
    char caractere;
    int valor;

    fscanf(arquivo, "%c", &caractere);
    fscanf(arquivo, "%d", &valor);

    if(valor == -1) {
        fscanf(arquivo, "%c", &caractere);
        return NULL;
    }
    else {
        struct arvore *arvore = (struct arvore *) malloc(sizeof(struct arvore));
        arvore->info = valor;
        arvore->esq = LerArquivo(arquivo);
        arvore->dir = LerArquivo(arquivo);
        fscanf(arquivo, "%c", &caractere);
        return arvore;
    }

}

void ImprimirPreOrdem(struct arvore *arvore) {
    if(arvore != NULL) {
        printf("%d ", arvore->info);
        ImprimirPreOrdem(arvore->esq);
        ImprimirPreOrdem(arvore->dir);
    }
}

void ImprimirEmOrdem(struct arvore *arvore) {
    if(arvore != NULL) {
        ImprimirEmOrdem(arvore->esq);
        printf("%d ", arvore->info);
        ImprimirEmOrdem(arvore->dir);
    }
}

void ImprimirPosOrdem(struct arvore *arvore) {
    if(arvore != NULL) {
        ImprimirPosOrdem(arvore->esq);
        ImprimirPosOrdem(arvore->dir);
        printf("%d ", arvore->info);
    }
}

bool VerificarExistencia(struct arvore *arvore, int valor) {
    if(arvore == NULL) {
        return false;
    }
    else if(arvore->info == valor) {
        return true;
    }
    else {
        bool retorno = VerificarExistencia(arvore->esq, valor);
        if(retorno == true) {
            return true;
        }
        return VerificarExistencia(arvore->dir, valor);
    }
}

struct arvore *DestruirArvore(struct arvore *arvore) {
    if(arvore != NULL) {
        arvore->esq = DestruirArvore(arvore->esq);
        arvore->dir = DestruirArvore(arvore->dir);
        free(arvore);
    }
    return NULL;
}

int AlturaArvore(struct arvore *arvore) {
    if(arvore == NULL) {
        return 0;
    }
    else {
        int alturaEsq, alturaDir;
        alturaEsq = AlturaArvore(arvore->esq);
        alturaDir = AlturaArvore(arvore->dir);
        
        if(alturaEsq > alturaDir) {
            return alturaEsq + 1;   // mais um da "raiz atual".
        }
        else {
            return alturaDir + 1;   // mais um da "raiz atual".
        }
    }
}

void ImprimirNivel(struct arvore *arvore, int contador, int nivel) {
    if(arvore != NULL) {
        if(contador == nivel) {
            printf("%d ", arvore->info);
        }
        else {
            ImprimirNivel(arvore->esq, contador + 1, nivel);
            ImprimirNivel(arvore->dir, contador + 1, nivel);
        }
    }
}

int QuantidadeNoNivel(struct arvore *arvore, int contador, int nivel) {
    if(arvore == NULL) {
        return 0;
    }
    else {
        if(contador == nivel) {
            return 1;
        }
        else {
            return QuantidadeNoNivel(arvore->esq, contador + 1, nivel) + QuantidadeNoNivel(arvore->dir, contador + 1, nivel);
        }
    }
}

void ImprimirEmLargura(struct arvore *arvore) {
    int altura = AlturaArvore(arvore);
    int i;
    for(i = 0; i < altura; i++) {
        ImprimirNivel(arvore, 0, i);
    }
}

int QuantidadeNaArvore(struct arvore *arvore) {
    int altura = AlturaArvore(arvore);
    int Quantidade = 0;
    int i;
    for(i = 0; i < altura; i++) {
        Quantidade += QuantidadeNoNivel(arvore, 0, i);
    }
    return Quantidade;
}

void ImprimirFolhas(struct arvore *arvore) {
    if(arvore != NULL) {
        if(arvore->esq == NULL && arvore->dir == NULL) {
            printf("%d ", arvore->info);
        }
        else {
            ImprimirFolhas(arvore->esq);
            ImprimirFolhas(arvore->dir);
        }
    }
}

bool VerificarBalanceamento(struct arvore *arvore) {
    if(arvore != NULL) {
        bool balanceada = false;
        int alturaEsq = AlturaArvore(arvore->esq);
        int alturaDir = AlturaArvore(arvore->dir);
        int diferenca = abs(alturaEsq - alturaDir);
        if(diferenca < 2) {
            balanceada = VerificarBalanceamento(arvore->esq);
            if(balanceada == false) {
                return false;
            }
            balanceada = VerificarBalanceamento(arvore->dir);
            if(balanceada == false) {
                return false;
            }

        }
        else {
            return false;
        }
    }
    return true;
}

int Pot(int base, int expoente) {
    int valor = 1;
    int i;
    for(i = 0; i < expoente; i++) {
        valor *= base;
    }
    return valor;
}

bool VerificarArvoreCheia(struct arvore *arvore) {
    if(arvore != NULL) {
        int quantidade = QuantidadeNaArvore(arvore);
        int maximo = Pot(2, AlturaArvore(arvore)) - 1;
        if(quantidade < maximo) {
            return false;
        }
    }
    return true;
}

bool ImprimirQualNivel(struct arvore *arvore, int nivel, int valor) {
    if(arvore != NULL) {
        if(arvore->info == valor) {
            printf("%d ", nivel);
            return true;
        }
        else {
            bool encontrado;
            encontrado = ImprimirQualNivel(arvore->esq, nivel + 1, valor);
            if(encontrado == true) {
                return true;
            }
            encontrado = ImprimirQualNivel(arvore->dir, nivel + 1, valor);
            if(encontrado == true) {
                return true;
            }
        }

    }
    return false;
}