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
        printf("3 - Imprimir Nivel do No\n");
        printf("4 - Imprimir folhas menores que o No\n");
        printf("5 - Inserir um No\n");
        printf("6 - Remover um No\n");
        printf("7 - Sair\n");
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
            printf("Digite o valor do elemento que deseja saber o nivel:\n");
            scanf(" %d", &valor);
            if(VerificarExistencia(arvore, valor)) {
                ImprimirNivelNo(arvore, valor, 0);
            }
            else {
                printf("\nElemento %d nao encontrado na arvore.\n", valor);
            }
            printf("\n");
            break;
        case 4:
            printf("Digite o valor do elemento que deseja consultar:\n");
            scanf(" %d", &valor);
            printf("\n\nNos folhas menores do que %d:\n", valor);
            ImprimirFolhasMenores(arvore, valor);
            break;
        case 5:
            printf("Digite o valor do elemento que deseja inserir:\n");
            scanf(" %d", &valor);
            InserirNo(arvore, valor);
            printf("\n\no No %d foi inserido.\n", valor);
            break;
        case 6:
            printf("Digite o valor do elemento que deseja remover:\n");
            scanf(" %d", &valor);
            if(VerificarExistencia(arvore, valor)) {
                RemoverNo(arvore, valor);
                printf("\n\nElemento %d removido.\n", valor);
            }
            else {
                printf("\n\nO elemento %d nao existe na arvore.\n", valor);
            }
            break;
        case 7:
            printf("\nEncerrando...\n");
            arvore = DestruirArvore(arvore);
            printf("\n\nEncerrado!\n");
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