#include "libfila.h"

#include <stdlib.h>

struct fila* cria_fila() {
    struct fila* f = malloc(sizeof(*f));
    if (!f)
        exit(1);
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

struct fila* destroi_fila(struct fila* f) {
    struct nodo_f* nodo;
    if (vazia_fila(f))
    {
        free(f);
        return NULL;
    }
    nodo = f->ini;
    while (nodo->prox != NULL)
    {
        nodo = nodo->prox;
        free(f->ini);
        f->ini = nodo;
    }
    free(f->fim);
    free(f);
    return NULL;
}

int vazia_fila(struct fila* f) {
    if (f->ini == NULL)
        return 1;
    return 0;
}

void insere_fila(struct fila* f, struct nodo* n_avl) {
    struct nodo_f* nodo = malloc(sizeof(*nodo));
    if (!nodo)
        exit(1);
    nodo->n_avl = n_avl;
    nodo->prox = NULL;
    if (vazia_fila(f))
    {
        f->ini = nodo;
        f->fim = nodo;
    }
    else
    {
        (f->fim)->prox = nodo;
        f->fim = nodo;
    }
}

int retira_fila(struct fila* f, struct nodo** n_avl) {
    struct nodo_f* nodo;
    if (vazia_fila(f))
        return 0;
    nodo = f->ini;
    f->ini = nodo->prox;
    *n_avl = nodo->n_avl;
    free(nodo);
    return 1;
}

void imprime_fila(struct fila* f) {
    struct nodo_f* nodo = f->ini;
    while (nodo->prox != NULL) {
        printf("%d ", nodo->n_avl->chave);
        nodo = nodo->prox;
    }
    printf("%d\n", nodo->n_avl->chave);
}