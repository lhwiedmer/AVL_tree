#ifndef LIBFILA
#define LIBFILA

#include "avl.h" 
#include <stdio.h>

struct nodo_f {
	struct nodo* n_avl;
    struct nodo_f* prox;
};

struct fila {
    struct nodo_f* ini;
    struct nodo_f* fim;
};

//Cria uma fila vazia e a retorna, se falhar retorna NULL. 
struct fila* cria_fila();

//Remove todos os elementos da fila e libera o espaco alocado.
struct fila* destroi_fila(struct fila* f);

//Retorna 1 se a fila esta vazia e 0 caso contrario. 
int vazia_fila(struct fila* f);

//Insere o elemento no final da fila (politica FIFO).
//Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. 
void insere_fila(struct fila* f, struct nodo* n_avl);

//Remove o elemento do inicio da fila (politica FIFO) e o retorna
//no parametro *n_avl. Retorna 1 se a operacao foi bem sucedida
//e 0 caso contrario. 
int retira_fila(struct fila* f, struct nodo** n_avl);

//Imprime a fila.
void imprime_fila(struct fila* f);

#endif //LIBFILA