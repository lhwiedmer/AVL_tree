#include <stdio.h>
#include <stdlib.h>
#include "avl.h"



int main() {
    imprimirDadosAlunos();
    struct nodo *raiz = NULL;
    char x;
    scanf("%1c", &x);
    while (x != 'f') {
        struct nodo *nodoAux = NULL;
        int chave;
        switch (x) {
            case 'i':
                scanf("%15d", &chave);
                nodoAux = inserir(&raiz, chave);
                if (!nodoAux)
                    printf("Falha ao inserir\n");
                break;

            case 'r':
                scanf("%15d", &chave);
                int i = excluir(&raiz, chave);
                if (!i)
                    printf("Falha ao remover %d\n", chave);
                break;

            case 'b':
                scanf("%15d", &chave);
                nodoAux = buscar(raiz, chave);
                if (!nodoAux)
                    printf("Nao encontrado %d\n", chave);
                else
                    printf("Encontrado %d\n", nodoAux->chave);
                break;

            case 'e':
                if (raiz == NULL)
                    printf("Arvore vazia");
                else
                    imprimirEmOrdem(raiz);
                printf("\n");
                break;

            case 'l':
                imprimirEmLargura(raiz);
                break;

            default:
				break;
        }
        scanf("%1c", &x);
    }
    destroiArvore(raiz);
    return 0;
}
