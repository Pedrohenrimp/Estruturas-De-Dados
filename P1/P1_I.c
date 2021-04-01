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
bool VerificarSimilaridade(struct arvore *arvore1, struct arvore *arvore2);


int main(void) {
    char nome[40];
    printf("Digite o nome do arquivo da primeira arvore que deseja carregar:\n");
    scanf(" %s", nome);
    arquivo = fopen(nome, "rt");
    struct arvore *arvore1 = LerArquivo(arquivo);
    fclose(arquivo);
    // strcpy(nome, "");
    // printf("Digite o nome do arquivo da segunda arvore que deseja carregar:\n");
    // scanf(" %s", nome);
    //arquivo = fopen(nome, "rt");
    //struct arvore *arvore2 = LerArquivo(arquivo);
    //fclose(arquivo);
    //struct arvore *arvore1 = NULL;
    struct arvore *arvore2 = NULL;

    if(VerificarSimilaridade(arvore2, arvore1)) {
        printf("Arvores Similares!");
    }
    else {
        printf("Arvores diferentes!");
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

bool VerificarSimilaridade(struct arvore *arvore1, struct arvore *arvore2) {
    if(arvore1 != NULL && arvore2 != NULL) {
        bool igualdade = false;
        int alturaEsq1 = AlturaArvore(arvore1->esq);
        int alturaDir1 = AlturaArvore(arvore1->dir);
        int alturaEsq2 = AlturaArvore(arvore2->esq);
        int alturaDir2 = AlturaArvore(arvore2->dir);
        if(alturaDir1 == alturaDir2 && alturaEsq1 == alturaEsq2) {
            igualdade = VerificarSimilaridade(arvore1->esq, arvore2->esq);
            if(igualdade == false) {
                return false;
            }
            igualdade = VerificarSimilaridade(arvore1->dir, arvore2->dir);
            if(igualdade == false) {
                return false;
            }
            return true;
        }
        else {
            return false;
        }
    }
    else if(arvore1 != NULL) {
        return false;
    }
    else if(arvore2 != NULL) {
        return false;
    }
    else {
        return true;
    }
}