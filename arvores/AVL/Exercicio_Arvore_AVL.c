#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
    int FB;
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
struct arvore *RotacaoEsq(struct arvore *r);
struct arvore *RotacaoEsqSimples(struct arvore *r);
struct arvore *RotacaoEsqDupla(struct arvore *r);
struct arvore *RotacaoDir(struct arvore *r);
struct arvore *RotacaoDirSimples(struct arvore *r);
struct arvore *RotacaoDirDupla(struct arvore *r);
struct arvore *Inserir(struct arvore *r, int x, int *hMudou);
struct arvore *Remover(struct arvore *r, int x, int *hMudou);
struct arvore *DestruirArvore(struct arvore *arvore);

int main(void)
{
    char nome[40];
    printf("Digite o nome do arquivo da arvore que deseja carregar:\n");
    scanf(" %s", nome);
    arquivo = fopen(nome, "rt");
    struct arvore *arvore = LerArquivo(arquivo);
    fclose(arquivo);

    int *hMudou = (int *) malloc(sizeof(int));
    hMudou = 0;

    bool executando = true;
    while (executando)
    {

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
            if (VerificarExistencia(arvore, valor))
            {
                printf("\nA arvore contem o elemento %d.\n", valor);
            }
            else
            {
                printf("\nElemento %d nao encontrado na arvore.\n", valor);
            }
            break;
        case 3:
            printf("Digite o valor do elemento que deseja saber o nivel:\n");
            scanf(" %d", &valor);
            if (VerificarExistencia(arvore, valor))
            {
                ImprimirNivelNo(arvore, valor, 0);
            }
            else
            {
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
            Inserir(arvore, valor, &hMudou);
            printf("\n\no No %d foi inserido.\n", valor);
            break;
        case 6:
            printf("Digite o valor do elemento que deseja remover:\n");
            scanf(" %d", &valor);
            if (VerificarExistencia(arvore, valor))
            {
                Remover(arvore, valor, &hMudou);
                printf("\n\nElemento %d removido.\n", valor);
            }
            else
            {
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

struct arvore *LerArquivo(FILE *arquivo)
{
    char caractere;
    int valor;

    fscanf(arquivo, "%c", &caractere);
    fscanf(arquivo, "%d", &valor);

    if (valor == -1)
    {
        fscanf(arquivo, "%c", &caractere);
        return NULL;
    }
    else
    {
        struct arvore *arvore = (struct arvore *)malloc(sizeof(struct arvore));
        arvore->info = valor;
        arvore->esq = LerArquivo(arquivo);
        arvore->dir = LerArquivo(arquivo);
        fscanf(arquivo, "%c", &caractere);
        return arvore;
    }
}

void ImprimirPreOrdem(struct arvore *arvore)
{
    if (arvore != NULL)
    {
        printf("%d ", arvore->info);
        ImprimirPreOrdem(arvore->esq);
        ImprimirPreOrdem(arvore->dir);
    }
}

void ImprimirEmOrdem(struct arvore *arvore)
{
    if (arvore != NULL)
    {
        ImprimirEmOrdem(arvore->esq);
        printf("%d ", arvore->info);
        ImprimirEmOrdem(arvore->dir);
    }
}

void ImprimirPosOrdem(struct arvore *arvore)
{
    if (arvore != NULL)
    {
        ImprimirPosOrdem(arvore->esq);
        ImprimirPosOrdem(arvore->dir);
        printf("%d ", arvore->info);
    }
}

int AlturaArvore(struct arvore *arvore)
{
    if (arvore == NULL)
    {
        return 0;
    }
    else
    {
        int alturaEsq, alturaDir;
        alturaEsq = AlturaArvore(arvore->esq);
        alturaDir = AlturaArvore(arvore->dir);

        if (alturaEsq > alturaDir)
        {
            return alturaEsq + 1; // mais um da "raiz atual".
        }
        else
        {
            return alturaDir + 1; // mais um da "raiz atual".
        }
    }
}

void ImprimirNivel(struct arvore *arvore, int contador, int nivel)
{
    if (arvore != NULL)
    {
        if (contador == nivel)
        {
            printf("%d ", arvore->info);
        }
        else
        {
            ImprimirNivel(arvore->esq, contador + 1, nivel);
            ImprimirNivel(arvore->dir, contador + 1, nivel);
        }
    }
}

void ImprimirEmLargura(struct arvore *arvore)
{
    int altura = AlturaArvore(arvore);
    int i;
    for (i = 0; i < altura; i++)
    {
        ImprimirNivel(arvore, 0, i);
    }
}

bool VerificarExistencia(struct arvore *arvore, int valor)
{
    if (arvore == NULL)
    {
        return false;
    }
    else if (arvore->info == valor)
    {
        return true;
    }
    else if (arvore->info > valor)
    {
        return VerificarExistencia(arvore->esq, valor);
    }
    else
    {
        return VerificarExistencia(arvore->dir, valor);
    }
}

void ImprimirNivelNo(struct arvore *arvore, int valor, int nivel)
{
    if (arvore != NULL)
    {
        if (arvore->info == valor)
        {
            printf("Nivel: %d", nivel);
        }
        else if (arvore->info > valor)
        {
            ImprimirNivelNo(arvore->esq, valor, nivel + 1);
        }
        else
        {
            ImprimirNivelNo(arvore->dir, valor, nivel + 1);
        }
    }
}

bool ImprimirFolhasMenores(struct arvore *arvore, int valor)
{
    if (arvore == NULL)
    {
        return false;
    }
    else if (arvore->info < valor)
    {
        if (arvore->esq == NULL && arvore->dir == NULL)
        {
            printf("%d ", arvore->info);
            return true;
        }
        else
        {
            ImprimirFolhasMenores(arvore->esq, valor);
            ImprimirFolhasMenores(arvore->dir, valor);
        }
    }
    else
    {
        ImprimirFolhasMenores(arvore->esq, valor);
    }
    return false;
}

//Rotação a esquerda geral
struct arvore *RotacaoEsq(struct arvore *r)
{
    if (r->dir->FB == -1)
        r = RotacaoEsqDupla(r);
    else
        r = RotacaoEsqSimples(r);
    return r;
}

//Rotação a esquerda simples
struct arvore *RotacaoEsqSimples(struct arvore *r)
{
    //Os nós a e b serão aqueles com FB modificados.
    struct arvore *a = r;
    struct arvore *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    if (b->FB == 1)
    {
        a->FB = 0;
        b->FB = 0;
    }
    else
    {
        a->FB = 1;
        b->FB = -1;
    }
    r = b;
    return r;
}

//Rotação a esquerda dupla
struct arvore *RotacaoEsqDupla(struct arvore *r)
{
    //Os nós a, b, c serão aqueles com FBs modificados
    struct arvore *a = r;
    struct arvore *c = a->dir;
    struct arvore *b = c->esq; //O nó b será a nova raiz
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    //Setando os valores dos FBs de acordo
    //com FB da nova raiz.
    switch (b->FB)
    {
    case -1:
        a->FB = 0;
        c->FB = 1;
        break;
    case 0:
        a->FB = 0;
        c->FB = 0;
        break;
    case +1:
        a->FB = -1;
        c->FB = 0;
        break;
    }
    b->FB = 0;
    r = b;
    return r;
}

//Rotação a direita geral
struct arvore *RotacaoDir(struct arvore *r)
{
    if (r->esq->FB == 1)
        r = RotacaoDirDupla(r);
    else
        r = RotacaoDirSimples(r);
    return r;
}

//Rotação a direita simples
struct arvore *RotacaoDirSimples(struct arvore *r)
{
    //Os nós a e b serão aqueles com FB modificados.
    struct arvore *a = r->esq;
    struct arvore *b = r;
    b->esq = a->dir;
    a->dir = b;
    if (a->FB == -1)
    {
        a->FB = 0;
        b->FB = 0;
    }
    else
    {
        a->FB = 1;
        b->FB = -1;
    }
    r = a;
    return r;
}

//Rotação a direita dupla
struct arvore *RotacaoDirDupla(struct arvore *r)
{
    //Os nós a, b, c serão aqueles com FBs modificados
    struct arvore *c = r;
    struct arvore *a = c->esq;
    struct arvore *b = a->dir;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    //Setando os valores dos FBs de acordo com FB da nova raiz.
    switch (b->FB)
    {
    case -1:
        a->FB = 0;
        c->FB = 1;
        break;
    case 0:
        a->FB = 0;
        c->FB = 0;
        break;
    case +1:
        a->FB = -1;
        c->FB = 0;
        break;
    }
    b->FB = 0;
    r = b;
    return r;
}

//Insere um valor x na árvore AVL
//hMudou informa se a altura mudou
struct arvore *Inserir(struct arvore *r, int x, int *hMudou)
{
    if (r == NULL) //Momento de inserir
    {
        r = (struct arvore *)malloc(sizeof(struct arvore));
        r->info = x;
        r->esq = NULL;
        r->dir = NULL;
        r->FB = 0;
        *hMudou = 1;
    }
    else
    {
        if (x <= r->info)

        {
            r->esq = Inserir(r->esq, x, hMudou);
            if (*hMudou == 1)
            {

                switch (r->FB)

                {
                case -1:
                    r = RotacaoDir(r);
                    *hMudou = 0;
                    break;
                case 0:
                    r->FB = -1;
                    *hMudou = 1;
                    break;
                case +1:
                    r->FB = 0;
                    *hMudou = 0;
                    break;
                }
            }
        }
        else
        {
            r->dir = Inserir(r->dir, x, hMudou);
            if (*hMudou == 1)

            {
                switch (r->FB)
                {
                case -1:

                    r->FB = 0;
                    *hMudou = 0;
                    break;
                case 0:
                    r->FB = +1;
                    *hMudou = 1;
                    break;
                case +1:
                    r = RotacaoEsq(r);
                    *hMudou = 0;
                    break;
                }
            }
        }
    }
    return r;
}

struct arvore *Remover(struct arvore *r, int x, int *hMudou)
{
    if (r != NULL)
    {
        if (r->info == x)

        {
            //Verificar se é folha
            if (r->esq == NULL && r->dir == NULL)
            {
                free(r);
                *hMudou = 1;
                return NULL;
            }
            //Verificar se um dos filhos é nulo
            else if (r->esq == NULL || r->dir == NULL)
            {
                struct arvore *aux;
                if (r->esq == NULL)
                    aux = r->dir;
                else
                    aux = r->esq;
                *hMudou = 1;
                return aux;
            }
            //Nenhum filho nulo
            else
            {
                struct arvore *maiorEsq = r->esq;
                while (maiorEsq->dir != NULL)
                    maiorEsq = maiorEsq->dir;
                r->info = maiorEsq->info;
                r->esq = Remover(r->esq, r->info, hMudou);
                if (*hMudou == 1)
                {
                    switch (r->FB)
                    {
                    case -1:
                        r->FB = 0;
                        *hMudou = 1;
                        break;
                    case 0:
                        r->FB = 1;

                        *hMudou = 0;
                        break;
                    case +1:
                    {
                        int aux = r->dir->FB;
                        r = RotacaoEsq(r);
                        if (aux == 0)
                            *hMudou = 0;
                        else
                            *hMudou = 1;
                        break;
                    }
                    }
                }
            }
        }
        else if (x < r->info)
        {
            r->esq = Remover(r->esq, x, hMudou);
            if (*hMudou == 1)
            {
                switch (r->FB)
                {
                case -1:
                    r->FB = 0;
                    *hMudou = 1;
                    break;
                case 0:
                    r->FB = 1;
                    *hMudou = 0;
                    break;
                case +1:
                {
                    int aux = r->dir->FB;
                    r = RotacaoEsq(r);
                    if (aux == 0)
                        *hMudou = 0;
                    else
                        *hMudou = 1;
                    break;
                }
                }
            }
        }

        else
        {
            r->dir = Remover(r->dir, x, hMudou);
            if (*hMudou == 1)
            {
                switch (r->FB)
                {
                case +1:
                    r->FB = 0;
                    *hMudou = 1;
                    break;
                case 0:
                    r->FB = -1;
                    *hMudou = 0;
                    break;
                case -1:
                {
                    int aux = r->esq->FB;
                    r = RotacaoDir(r);
                    if (aux == 0)
                        *hMudou = 0;
                    else
                        *hMudou = 1;
                    break;
                }
                }
            }
        }
        return r;
    }
}
struct arvore *DestruirArvore(struct arvore *arvore)
{
    if (arvore != NULL)
    {
        arvore->esq = DestruirArvore(arvore->esq);
        arvore->dir = DestruirArvore(arvore->dir);
        free(arvore);
    }
    return NULL;
}