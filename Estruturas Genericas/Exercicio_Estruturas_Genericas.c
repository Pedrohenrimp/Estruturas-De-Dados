#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_VETOR 100


typedef struct professor {
    int matricula;
    char nome[30];
    float salario;

} Professor;

typedef struct aluno {
    int matricula;
    char nome[30];
    char curso[20];
    int ingresso; // ano de ingresso.
} Aluno;

typedef struct entidade {
    int tipo; // professor: 1;  aluno: 2
    void *objeto;
} Entidade;


void InicializarVetor(Entidade *vetor, int tamanho);
int ProcurarPosicaoVazia(Entidade *vetor, int tamanho);
void InserirEntidade(Entidade *vetor, int posicao, void *informacao, int tipo);
bool RemoverEntidade(Entidade *vetor, int tamanho, int matricula);
bool BuscarEntidade(Entidade *vetor, int tamanho, int matricula);
void ImprimirEntidade(Entidade *vetor, int tamanho, int matricula);
int QuantidadeNoCurso(Entidade *vetor, int tamanho, char curso[]);
bool ImprimirProfessoresMaiorSalario(Entidade *vetor, int tamanho);
void DestruirEntidades(Entidade *vetor, int tamanho);


int main(void) {
    Entidade vetorDeEntidades[TAMANHO_VETOR];
    InicializarVetor(vetorDeEntidades, TAMANHO_VETOR);
    int opcao = 0;
    while(opcao != 6) {
        printf("\n--------    MENU    --------\n\n");
        printf("Escolha uma das opcoes:\n");
        printf("1) Inserir Entidade\n");
        printf("2) Remover Entidade\n");
        printf("3) Buscar Entidade\n");
        printf("4) Consultar Quantidade de Alunos em um Curso\n");
        printf("5) Consultar Professores com Maior Salario\n");
        printf("6) Sair\n");
        scanf(" %d", &opcao);
        printf("\n\n");
        if(opcao == 1) {
            int posicaoVazia = ProcurarPosicaoVazia(vetorDeEntidades, TAMANHO_VETOR);
            printf("Digite o Tipo de Entidade que deseja Inserir:\n");
            printf("1) Professor\n");
            printf("2) Aluno\n");
            scanf(" %d", &opcao);
            if(opcao == 1) {
                Professor *professor = (Professor *) malloc(sizeof(Professor));
                printf("Digite o Nome do Professor:\n");
                scanf(" %[^\n]s", professor->nome);
                printf("Digite a Matricula do Professor:\n");
                scanf(" %d", &professor->matricula);
                printf("Digite o Salario do Professor:\n");
                scanf(" %f", &professor->salario);
                if(BuscarEntidade(vetorDeEntidades, TAMANHO_VETOR, professor->matricula)) {
                    printf("O Cadastro do Professor com Matricula %d ja Existe! Nao foi possivel Inserir!\n", professor->matricula);
                }
                else {
                    InserirEntidade(vetorDeEntidades, posicaoVazia, professor, 1);
                    printf("Professor Inserido com Sucesso!\n");
                }
            }
            else if(opcao == 2) {
                Aluno *aluno = (Aluno *) malloc(sizeof(Aluno));
                printf("Digite o Nome do Aluno:\n");
                scanf(" %[^\n]s", aluno->nome);
                printf("Digite a Matricula do Aluno:\n");
                scanf(" %d", &aluno->matricula);
                printf("Digite o Curso do Aluno:\n");
                scanf(" %[^\n]s", aluno->curso);
                printf("Digite o Ano de Ingresso do Aluno:\n");
                scanf(" %d", &aluno->ingresso);
                if(BuscarEntidade(vetorDeEntidades, TAMANHO_VETOR, aluno->matricula)) {
                    printf("O Cadastro do Aluno com Matricula %d ja Existe! Nao foi possivel Inserir!\n", aluno->matricula);
                }
                else {
                    InserirEntidade(vetorDeEntidades, posicaoVazia, aluno, 2);
                    printf("Aluno Inserido com Sucesso!\n");
                }
            }
        }
        else if(opcao == 2) {
            int matricula;
            printf("Digite a Matricula da Entidade que Deseja Remover:\n");
            scanf(" %d", &matricula);
            printf("\n");
            if(RemoverEntidade(vetorDeEntidades, TAMANHO_VETOR, matricula)) {
                printf("Entidade Removida com Sucesso!\n");
            }
            else {
                printf("Matricula nao Encontrada! Nao foi Possivel Remover!\n");
            }
        }
        else if(opcao == 3) {
            int matricula;
            printf("Digite a Matricula da Entidade que Deseja Buscar:\n");
            scanf(" %d", &matricula);
            if(BuscarEntidade(vetorDeEntidades, TAMANHO_VETOR, matricula)) {
                ImprimirEntidade(vetorDeEntidades, TAMANHO_VETOR, matricula);
            }
            else {
                printf("Entidade nao Encontrada!\n");
            }
        }
        else if(opcao == 4) {
            char curso[20];
            printf("Digite o Nome do Curso que Deseja Consultar:\n");
            scanf(" %[^\n]s", curso);
            int quantidade = QuantidadeNoCurso(vetorDeEntidades, TAMANHO_VETOR, curso);
            printf("O Curso %s possui %d aluno(s)!\n", curso, quantidade);
        }
        else if(opcao == 5) {
            ImprimirProfessoresMaiorSalario(vetorDeEntidades, TAMANHO_VETOR);
        }
        else if(opcao == 6) {
            printf("Encerrando...\n");
            DestruirEntidades(vetorDeEntidades, TAMANHO_VETOR);
            printf("Encerrado!\n");
        }
    }
}


void InicializarVetor(Entidade *vetor, int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++) {
        vetor[i].tipo = 0;
        vetor[i].objeto = NULL;
    }
}

int ProcurarPosicaoVazia(Entidade *vetor, int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i].tipo == 0) {
            return i;
        }
    }
    return -1;
}

void InserirEntidade(Entidade *vetor, int posicao, void *informacao, int tipo) {
    vetor[posicao].tipo = tipo;
    vetor[posicao].objeto = informacao;
}

bool RemoverEntidade(Entidade *vetor, int tamanho, int matricula) {
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i].tipo == 1) {
            Professor *professor = (Professor *) vetor[i].objeto;
            if(professor->matricula == matricula) {
                vetor[i].tipo = 0;
                free(vetor[i].objeto);
                vetor[i].objeto = NULL;
                return true;
            }
        }
        else if(vetor[i].tipo == 2) {
            Aluno *aluno = (Aluno *) vetor[i].objeto;
            if(aluno->matricula == matricula) {
                vetor[i].tipo = 0;
                free(vetor[i].objeto);
                vetor[i].objeto = NULL;
                return true;
            }
        }
    }
    return false;
}

bool BuscarEntidade(Entidade *vetor, int tamanho, int matricula) {
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i].tipo == 1) {
            Professor *professor = (Professor *) vetor[i].objeto;
            if(professor->matricula == matricula) {
                return true;
            }
        }
        else if(vetor[i].tipo == 2) {
            Aluno *aluno = (Aluno *) vetor[i].objeto;
            if(aluno->matricula == matricula) {
                return true;
            }
        }
    }
    return false;
}

void ImprimirEntidade(Entidade *vetor, int tamanho, int matricula) {
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i].tipo == 1) {
            Professor *professor = (Professor *) vetor[i].objeto;
            if(professor->matricula == matricula) {
                printf("Tipo: Professor\nNome: %s\nMatricula: %d\nSalario: %.2f\n\n", professor->nome, professor->matricula, professor->salario);
            }
        }
        else if(vetor[i].tipo == 2) {
            Aluno *aluno = (Aluno *) vetor[i].objeto;
            if(aluno->matricula == matricula) {
                printf("Tipo: Aluno\nNome: %s\nMatricula: %d\nCurso: %s\nAno de Ingresso: %d\n\n", aluno->nome, aluno->matricula, aluno->curso, aluno->ingresso);
            }
        }
    }
}

int QuantidadeNoCurso(Entidade *vetor, int tamanho, char curso[]) {
    int quantidade = 0;
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i].tipo == 2) {
            Aluno *aluno = (Aluno *) vetor[i].objeto;
            if(strcmp(aluno->curso, curso) == 0) {
                quantidade++;
            }
        }
    }
    return quantidade;
}

bool ImprimirProfessoresMaiorSalario(Entidade *vetor, int tamanho) {
    int maiorSalario = 0;
    bool temProfessor = false;
    int i;
    for(i = 0; i < tamanho; i++) {
        if(vetor[i].tipo == 1) {
            temProfessor = true;
            Professor *professor = (Professor *) vetor[i].objeto;
            if(professor->salario > maiorSalario) {
                maiorSalario = professor->salario;
            }
        }
    }
    if(temProfessor) {
        for(i = 0; i < tamanho; i++) {
            if(vetor[i].tipo == 1) {
                Professor *professor = (Professor *) vetor[i].objeto;
                if(professor->salario == maiorSalario) {
                    printf("Nome: %s\nMatricula: %d\nSalario: %.2f\n\n", professor->nome, professor->matricula, professor->salario);
                }
            }
        }
    }
    else {
        printf("Nao existe nenhum professor cadastrado!");
    }
    return temProfessor;
}

void DestruirEntidades(Entidade *vetor, int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++) {
        free(vetor[i].objeto);
    }
}

