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
int AlturaArvore(struct arvore *arvore);
void ImprimirNivel(struct arvore *arvore, int contador, int nivel);
void ImprimirEmLargura(struct arvore *arvore);
bool VerificarExistencia(struct arvore *arvore, int valor);
void ImprimirNivelNo(struct arvore *arvore, int valor, int nivel);
bool ImprimirFolhasMenores(struct arvore *arvore, int valor);
struct arvore *InserirNo(struct arvore *arvore, int valor);
struct arvore *RemoverNo(struct arvore *arvore, int valor);
struct arvore *DestruirArvore(struct arvore *arvore);
void NosEntreXeY(struct arvore *arvore, int x, int y, int *contador);


int main(void) {
    char nome[40];
    printf("Digite o nome do arquivo da arvore que deseja carregar:\n");
    scanf(" %s", nome);
    arquivo = fopen(nome, "rt");
    struct arvore *arvore = LerArquivo(arquivo);
    fclose(arquivo);

    int *numeroDeNos = (int *) malloc(sizeof(int));
    numeroDeNos[0] = 0;
    NosEntreXeY(arvore, 1, 40, numeroDeNos);
    printf("Distancia: %d", numeroDeNos[0]);
    free(numeroDeNos);
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

void ImprimirEmLargura(struct arvore *arvore) {
    int altura = AlturaArvore(arvore);
    int i;
    for(i = 0; i < altura; i++) {
        ImprimirNivel(arvore, 0, i);
    }
}

bool VerificarExistencia(struct arvore *arvore, int valor) {
    if(arvore == NULL) {
        return false;
    }
    else if(arvore->info == valor) {
        return true;
    }
    else if(arvore->info > valor) {
        return VerificarExistencia(arvore->esq, valor);
    }
    else {
        return VerificarExistencia(arvore->dir, valor);
    }
}

void ImprimirNivelNo(struct arvore *arvore, int valor, int nivel) {
    if(arvore != NULL) {
        if(arvore->info == valor) {
            printf("Nivel: %d", nivel);
        }
        else if(arvore->info > valor) {
            ImprimirNivelNo(arvore->esq, valor, nivel + 1);
        }
        else {
            ImprimirNivelNo(arvore->dir, valor, nivel + 1);
        }
    }
}

bool ImprimirFolhasMenores(struct arvore *arvore, int valor) {
    if(arvore == NULL) {
        return false;
    }
    else if(arvore->info < valor) {
        if(arvore->esq == NULL && arvore->dir == NULL) {
            printf("%d ", arvore->info);
            return true;
        }
        else {
            ImprimirFolhasMenores(arvore->esq, valor);
            ImprimirFolhasMenores(arvore->dir, valor);
        }
    }
    else { 
        ImprimirFolhasMenores(arvore->esq, valor);
    }
    return false;
}

struct arvore *InserirNo(struct arvore *arvore, int valor) {
    if(arvore == NULL) {
        arvore = (struct arvore *) malloc(sizeof(struct arvore));
        arvore->info = valor;
        arvore->esq = NULL;
        arvore->dir = NULL;
    }
    else if(valor <= arvore->info) {
        arvore->esq = InserirNo(arvore->esq, valor);
    }
    else {
        arvore->dir = InserirNo(arvore->dir, valor);
    }
    return arvore;
}

struct arvore *RemoverNo(struct arvore *arvore, int valor) {
    if(arvore != NULL) {
        if(arvore->info == valor) {
            if(arvore->esq == NULL && arvore->dir == NULL) {
                free(arvore);
                return NULL;
            }
            else if(arvore->esq == NULL) {
                struct arvore *auxiliar = arvore->dir;
                free(arvore);
                return auxiliar;
            }
            else if(arvore->dir == NULL) {
                struct arvore *auxiliar = arvore->esq;
                free(arvore);
                return auxiliar;
            }
            else {
                struct arvore *auxiliar = arvore->esq;
                while(auxiliar->dir != NULL) {
                    auxiliar = auxiliar->dir;
                }
                arvore->info = auxiliar->info;
                arvore->esq = RemoverNo(arvore->esq, auxiliar->info);
            }
        }
        else if(valor < arvore->info) {
            arvore->esq = RemoverNo(arvore->esq, valor);
        }
        else {
            arvore->dir = RemoverNo(arvore->dir, valor);
        }
    }
    return arvore;
}

struct arvore *DestruirArvore(struct arvore *arvore) {
    if(arvore != NULL) {
        arvore->esq = DestruirArvore(arvore->esq);
        arvore->dir = DestruirArvore(arvore->dir);
        free(arvore);
    }
    return NULL;
}

void NosEntreXeY(struct arvore *arvore, int x, int y, int *contador) {
    if(arvore != NULL) {
        if(arvore->info < x) {
            NosEntreXeY(arvore->dir, x, y, contador);
        }
        else if(arvore->info > y) {
            NosEntreXeY(arvore->esq, x, y, contador);
        }
        else {
            contador[0]++;
            NosEntreXeY(arvore->dir, x, y, contador);
            NosEntreXeY(arvore->esq, x, y, contador);
        }
    }
}