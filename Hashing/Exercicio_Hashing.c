#include <stdio.h>
#include <stdlib.h>

#define QUANTIDADE_REGISTROS 31

typedef struct aluno {
    int matricula;
    char nome[50];
    char curso[30];
} Aluno;

typedef struct registro {
    Aluno info;
    int disponibilidade; // 0 - em uso  /  1 - disponivel
} Registro;

int Hash(char key[30], int size);
void InicializarArquivo(char nomeArquivo[]);
void InserirNoArquivo(char nomeArquivo[], Aluno aluno);
int AcharPosicao(char nomeArquivo[], Aluno aluno);
void ImprimirAluno(char nomeArquivo[], int matricula);
void ImprimirArquivo(char nomeArquivo[]);


int main(void) {
    char nomeArquivo[] = "hashing.bin";
    InicializarArquivo(nomeArquivo);
    int opcao = 0;
    while(opcao != 4) {
        printf("\n\n--------       MENU       --------\n\n");
        printf("Escolha uma das opcoes a seguir:\n");
        printf("1) Inserir Novo Aluno\n");
        printf("2) Imprimir Aluno Especifico\n");
        printf("3) Imprimir Todos os Alunos\n");
        printf("4) Sair\n");
        scanf(" %d", &opcao);

        if(opcao == 1) {
            Aluno aluno;
            printf("\nDigite o nome do Aluno que deseja Inserir:\n");
            scanf(" %[^\n]s", aluno.nome);
            printf("Digite o numero da Matricula do aluno que deseja Inserir:\n");
            scanf(" %d", &aluno.matricula);
            printf("Digite o nome do Curso do aluno que deseja Inserir:\n");
            scanf(" %[^\n]s", aluno.curso);
            InserirNoArquivo(nomeArquivo, aluno);
            printf("Aluno Inserido Com Sucesso!\n");
        }
        else if(opcao == 2) {
            int matricula;
            printf("Digite o numero da Matricula do aluno que deseja Inserir:\n");
            scanf(" %d", &matricula);
            ImprimirAluno(nomeArquivo, matricula);
        }
        else if(opcao == 3) {
            ImprimirArquivo(nomeArquivo);
        }
        else if(opcao == 4) {
            printf("Encerrando...\n");
            printf("Encerrado!\n");
        }
        else {
            printf("Digite uma opcao valida!\n");
        }
    }
}


int Hash(char key[30], int size) {
    int soma = 0;
    int i;
    for(i = 0; key[i] != '\0'; i++) {
        soma += key[i];
    }
    return soma % size;
}

void InicializarArquivo(char nomeArquivo[]) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    Registro reg;
    reg.disponibilidade = 1;
    int i;
    for(i = 0; i < QUANTIDADE_REGISTROS; i++) {
        fwrite(&reg, sizeof(Registro), 1, arquivo);
    }
    fclose(arquivo);
}

void InserirNoArquivo(char nomeArquivo[], Aluno aluno) {
    int posicao = AcharPosicao(nomeArquivo, aluno);
    FILE *arquivo = fopen(nomeArquivo, "r+b");
    Registro reg;
    reg.info = aluno;
    reg.disponibilidade = 0;
    fseek(arquivo, posicao * sizeof(Registro), SEEK_SET);
    fwrite(&reg, sizeof(Registro), 1, arquivo);
    fclose(arquivo);
}

int AcharPosicao(char nomeArquivo[], Aluno aluno) {
    int posicao =  Hash(aluno.curso, QUANTIDADE_REGISTROS);
    Registro reg;
    FILE *arquivo = fopen(nomeArquivo, "rb");
    fseek(arquivo, posicao * sizeof(Registro), SEEK_SET);
    fread(&reg, sizeof(Registro), 1, arquivo);
    while(reg.disponibilidade == 0) {
        posicao = (posicao + 1) % QUANTIDADE_REGISTROS;
        fseek(arquivo, posicao * sizeof(Registro), SEEK_SET);
        fread(&reg, sizeof(Registro), 1, arquivo);
    }
    fclose(arquivo);
    return posicao;
}

void ImprimirAluno(char nomeArquivo[], int matricula) {
    Registro reg;
    FILE *arquivo = fopen(nomeArquivo, "rb");
    fread(&reg, sizeof(Registro), 1, arquivo);
    int i;
    for(i = 0; i < QUANTIDADE_REGISTROS; i++) {
        if(reg.info.matricula == matricula) {
            break;
        }
        fread(&reg, sizeof(Registro), 1, arquivo);
    }
    fclose(arquivo);
    if(reg.info.matricula == matricula) {
        printf("\nAluno: %s\nMatricula: %d\nCurso: %s\n", reg.info.nome, reg.info.matricula, reg.info.curso);
    }
    else {
        printf("\nAluno nao encontrado!\n");
    }
}

void ImprimirArquivo(char nomeArquivo[]) {
    Registro reg;
    FILE *arquivo = fopen(nomeArquivo, "rb");
    int i;
    for(i = 0; i < QUANTIDADE_REGISTROS; i++) {
        fread(&reg, sizeof(Registro), 1, arquivo);
        if(reg.disponibilidade == 0) {
            printf("\nAluno: %s\nMatricula: %d\nCurso: %s\n", reg.info.nome, reg.info.matricula, reg.info.curso);
        }
        else {
            printf("\nDisponivel!\n");
        }
    }
    fclose(arquivo);
}