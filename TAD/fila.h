#ifndef Fila_h
#define Fila_h

typedef struct fila *Fila;

Fila InicializarFila();
int Enfileirar(Fila fila, int valor);
int Desenfileirar(Fila fila, int *endereco);
void ImprimirFila(Fila fila);
Fila DestruirFila(Fila fila);

#endif