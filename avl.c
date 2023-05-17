#include "avl.h"
#include "libfila.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct aluno* getAluno1() {
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        exit(1);
    retorno->nome = malloc(sizeof("Luiz Henrique Murback Wiedmer"));//sizeof conta o \0
    if(!retorno->nome)
        exit(1);

    retorno->nomeDinf = malloc(sizeof("lhmw22"));
    if(!retorno->nomeDinf) {
        exit(1);
    }

    strcpy(retorno->nome, "Luiz Henrique Murback Wiedmer");
    strcpy(retorno->nomeDinf, "lhmw22");
    retorno->grr = 20221234;

    return retorno;
}

struct aluno* getAluno2() {
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        exit(1);
    retorno->nome = malloc(sizeof("Eduardo Giehl"));//sizeof conta o \0
    if(!retorno->nome)
        exit(1);

    retorno->nomeDinf = malloc(sizeof("eg22"));
    if(!retorno->nomeDinf) {
        exit(1);
    }

    strcpy(retorno->nome, "Eduardo Giehl");
    strcpy(retorno->nomeDinf, "eg22");
    retorno->grr = 20221222;

    return retorno;
}

void imprimirDadosAlunos() {
    struct aluno* aluno = getAluno1();

    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if(!aluno)
        return;

    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

//Aloca o espaco de uma struct nodo e a retorna.
struct nodo* criaNodo(int chave) {
    struct nodo* nodo = malloc(sizeof(*nodo));
    if (nodo == NULL)
        exit(1);
    nodo->chave = chave;
    nodo->fe = NULL;
    nodo->fd = NULL;
    nodo->pai = NULL;
    nodo->balanco = 0;
    return nodo;
}

//Faz uma rotacao a direita p.
struct nodo* rotaDir(struct nodo** p) {
    struct nodo* u = (*p)->fe;
    (*p)->fe = u->fd;
    u->fd = (*p);
    if ((*p)->fe != NULL)
        (*p)->fe->pai = (*p);
    u->pai = (*p)->pai;
    (*p)->pai = u;
    if (u->pai != NULL) {
        if (u->pai->fe == (*p))
            u->pai->fe = u;
        else
            u->pai->fd = u;
    }
    if (u->balanco == 0) {
        u->balanco = 1;
        (*p)->balanco = -1;
    } else {
        u->balanco = 0;
        (*p)->balanco = 0;
    }
    (*p) = u;
    return (*p);
}

//Faz uma rotacao a esquerda com base em p.
struct nodo* rotaEsq(struct nodo** p) {
    struct nodo* u = (*p)->fd;
    (*p)->fd = u->fe;
    u->fe = (*p);
    if ((*p)->fd != NULL)
        (*p)->fd->pai = (*p);
    u->pai = (*p)->pai;
    u->fe->pai = u;
    if (u->pai != NULL) {
        if (u->pai->fe == (*p))
            u->pai->fe = u;
        else
            u->pai->fd = u;
    }
    if (u->balanco == 0) {
        u->balanco = -1;
        (*p)->balanco = 1;
    } else {
        u->balanco = 0;
        (*p)->balanco = 0;
    }
    (*p) = u;
    return (*p);
}

//Faz uma rotacao dupla para a esquerda com base em p.
struct nodo* rotaDuplaEsq(struct nodo** p) {
    struct nodo* u = (*p)->fe;
    struct nodo* v = u->fd;
    u->fd = v->fe; v->fe = u;
    (*p)->fe = v->fd; v->fd = (*p);
    v->pai = (*p)->pai; (*p)->pai = v; u->pai = v;
    if ((*p)->fe != NULL)
        (*p)->fe->pai = (*p);
    if (u->fd != NULL)
        u->fd->pai = u;
    if (v->pai != NULL) {
        if (v->pai->fe == (*p))
            v->pai->fe = v;
        else
            v->pai->fd = v;
    }
    if (v->balanco == 0) {
        (*p)->balanco = 0;
        u->balanco = 0;
    } else {
        if (v->balanco == -1) {
            (*p)->balanco = 1;
            u->balanco = 0;
        } else {
            (*p)->balanco = 0;
            u->balanco = -1;
        }
    }
    v->balanco = 0;
    (*p) = v;
    return (*p);
}

//Faz uma rotacao dupla para a direita com base em p.
struct nodo* rotaDuplaDir(struct nodo** p) {
    struct nodo* u = (*p)->fd;
    struct nodo* v = u->fe;
    u->fe = v->fd; v->fd = u;
    (*p)->fd = v->fe; v->fe = (*p);
    v->pai = (*p)->pai; (*p)->pai = v; u->pai = v;
    if ((*p)->fd != NULL)
        (*p)->fd->pai = (*p);
    if (u->fe != NULL)
        u->fe->pai = u;
    if (v->pai != NULL) {
        if (v->pai->fe == (*p))
            v->pai->fe = v;
        else
            v->pai->fd = v;
    }
    if (v->balanco == 0) {
        (*p)->balanco = 0;
        u->balanco = 0;
    } else {
        if (v->balanco == -1) {
            (*p)->balanco = 0;
            u->balanco = 1;
        } else {
            (*p)->balanco = -1;
            u->balanco = 0;
        }
    }
    v->balanco = 0;
    (*p) = v;
    return (*p);
}

//Escolhe e faz a rotacao ideal para corrigir a avl no nodo passado como parâmetro.
struct nodo* corrigeAvl(struct nodo** nodo) {
    if ((*nodo)->balanco == 2) {
        if ((*nodo)->fd->balanco == -1) {
            return rotaDuplaDir(nodo);
        }
        return rotaEsq(nodo);
    }
    if ((*nodo)->fe->balanco == 1) {
        return rotaDuplaEsq(nodo);
    }
    return rotaDir(nodo);
}

//Atualiza balanco após a insercao de um novo nodo.
struct nodo* atualizaBalancoInserir(struct nodo *nodo) {
    struct nodo* pai = nodo->pai;
    if (nodo->pai->fe == nodo)
        pai->balanco--;
    else
        pai->balanco++;
    while ((pai->pai != NULL) && (pai->balanco != -2) && (pai->balanco != 2)) {
        nodo = pai;
        pai = nodo->pai;
        if (nodo->balanco == 0)
            return NULL;
        if (nodo->pai->fe == nodo)
            pai->balanco--;
        else	
            pai->balanco++;
    }
    if ((pai->balanco == 2) || (pai->balanco == -2)) {
        return pai;
    }
    return NULL;
}

//Cria um nodo com a chave passada como parâmetro, o insere na arvore
//de acordo com as regras da arvore de busca binaria, e o retorna.
//Nao aceita duplicatas, entao, retorna NULL se o nodo ja esta presente na arvore.
struct nodo* inserirBinario(struct nodo** raiz, int chave) {
    struct nodo *nodoAux = criaNodo(chave);
    if (nodoAux == NULL)
        return NULL;
    struct nodo *x = *raiz;
    struct nodo *y = NULL;
    while (x != NULL) {
        y = x;
        if (nodoAux->chave < x->chave)
            x = x->fe;
        else
            x = x->fd;
    }
    nodoAux->pai = y;
    if (y == NULL) {
        (*raiz) = nodoAux;
        return nodoAux;
    }
    if (nodoAux->chave == y->chave) {
        free(nodoAux);
        return NULL;
    }
    if (nodoAux->chave < y->chave) 
        y->fe = nodoAux;
    else
        y->fd = nodoAux;
    return nodoAux;
}

struct nodo* inserir(struct nodo** raiz, int chave) {
    struct nodo* inserido = inserirBinario(raiz, chave);
    if (inserido == NULL)
        return NULL;
    if (inserido->pai == NULL)
        return inserido;
    struct nodo* aux = atualizaBalancoInserir(inserido);
    if (aux != NULL) {
        if (aux->pai == NULL)
            corrigeAvl(raiz);
        else
            corrigeAvl(&aux);
    }
    return inserido;
}

//Encontra o nodo de maior valor na arvore com raiz passada no parâmetro nodo.
struct nodo* maximo(struct nodo *nodo) {
    while (nodo->fd != NULL) {
        nodo = nodo->fd;
    }
    return nodo;
}

//Trasplanta v para a posicao de u e desconecta u da arvore.
void transplante(struct nodo** raiz, struct nodo* u, struct nodo* v) {
    if (u->pai == NULL) {
        *raiz = v;
    } else {
        if (u == u->pai->fe)
            u->pai->fe = v;
        else
            u->pai->fd = v;
    }
    if (v != NULL) {
        if (v->pai != NULL) {
            if (v->pai->fe == v)
                v->pai->fe = NULL;
            else
                v->pai->fd = NULL;
        }
        v->pai = u->pai;
    }
}

//Atualiza o balanco da arvore a partir do nodo passado como parametro.
//Para quando encontra um nodo com balanco 1,-1,2,-2 ou a raiz.
//Se parar porque encontrou um nodo com balanco 2 ou -2, retorna ele, em outros casos retorna NULL. 
struct nodo* atualizaBalancoExcluir(struct nodo* nodo) {
    if ((nodo->balanco == 2) || (nodo->balanco == -2)) 
        return nodo;
    if ((nodo->balanco == 1) || (nodo->balanco == -1))
        return NULL;
    if (nodo->pai == NULL)
        return NULL;
    struct nodo* pai = nodo->pai;
    if (pai->fe == nodo)
        pai->balanco++;
    else
        pai->balanco--;
    if ((pai->balanco == 1) || (pai->balanco == -1))
        return NULL;
    while ((pai->pai != NULL) && (pai->balanco != 2) && (pai->balanco != -2)) {
        nodo = pai;
        pai = nodo->pai;
        if (pai->fe == nodo)
            pai->balanco++;
        else	
            pai->balanco--;
        if ((pai->balanco == 1) || (pai->balanco == -1))
            return NULL;
    }
    if ((pai->balanco == 2) || (pai->balanco == -2)) {
        return pai;
    }
    return NULL;
}

//Realiza o ccaso da exclusao em que o nodo nao tem filhos
struct nodo* casoNulo(struct nodo** raiz, struct nodo* nodoAux) {
    struct nodo* pai = nodoAux->pai;
    if (pai == NULL) {
        *raiz = NULL;
    } else {
        if (pai->fe == nodoAux) {
            pai->fe = NULL;
            pai->balanco++;
        } else {
            pai->fd = NULL;
            pai->balanco--;
        }
    }
    free(nodoAux);
    nodoAux = NULL;
    return pai;
}

//Realiza o ccaso da exclusao em que o nodo so tem o filho direito
struct nodo* casoDir(struct nodo** raiz, struct nodo* nodoAux) {
    struct nodo* pai = nodoAux->pai;
    struct nodo* fd = nodoAux->fd;
    transplante(raiz, nodoAux, nodoAux->fd);
    if (pai != NULL) {
        if (pai->fe == fd)
            pai->balanco++;
        else
            pai->balanco--;
    }
    free(nodoAux);
    nodoAux = NULL;
    return pai;
}

//Realiza o ccaso da exclusao em que o nodo so tem o filho esquerdo
struct nodo* casoEsq(struct nodo** raiz, struct nodo* nodoAux) {
    struct nodo* pai = nodoAux->pai;
    struct nodo* fe = nodoAux->fe;
    transplante(raiz, nodoAux, nodoAux->fe);
    if (pai != NULL) {
        if (pai->fe == fe)
            pai->balanco++;
        else
            pai->balanco--;
    }
    free(nodoAux);
    nodoAux = NULL;
    return pai;
}

//exclui o nodo com a chave
//caso o nodo nao exista retorna NULL
//caso o nodo tivesse um ou zero filhos, retorna o pai dele
//caso o nodo tivesse dois filhos, existem duas opcoes
//caso o antecessor fosse seu filho esquerdo, retorna o antecessor
//caso nao fosse, retorna o pai do antecessor
struct nodo* excluirBinario(struct nodo** raiz, struct nodo* nodoAux) {
    struct nodo* pai;
    if ((nodoAux->fe == NULL) && (nodoAux->fd == NULL))
        return casoNulo(raiz, nodoAux);
    if (nodoAux->fe == NULL)
        return casoDir(raiz, nodoAux);
    if (nodoAux->fd == NULL)
        return casoEsq(raiz, nodoAux);
    struct nodo *nodoAux2 = maximo(nodoAux->fe);
    if (nodoAux->fe == nodoAux2) {
        nodoAux2->balanco = nodoAux->balanco;
        nodoAux2->balanco++;
        transplante(raiz, nodoAux, nodoAux2);
        nodoAux2->fd = nodoAux->fd;
        nodoAux2->fd->pai = nodoAux2;
        free(nodoAux);
        nodoAux = NULL;
        pai = nodoAux2;
    } else {
        pai = nodoAux2->pai;
        struct nodo* antfe = nodoAux2->fe;
        transplante(raiz, nodoAux, nodoAux2);
        nodoAux2->balanco = nodoAux->balanco;
        nodoAux2->fe = nodoAux->fe; nodoAux2->fe->pai = nodoAux2;
        nodoAux2->fd = nodoAux->fd; nodoAux2->fd->pai = nodoAux2;
        pai->fd = nodoAux;
        nodoAux->pai = pai;
        nodoAux->fe = antfe;
        if (antfe != NULL)
            antfe->pai = nodoAux;
        nodoAux->fd = NULL;
        if (!nodoAux->fe)
            pai = casoNulo(raiz, nodoAux);
        else
            pai = casoEsq(raiz, nodoAux);
    }
    return pai;
}

int excluir(struct nodo** raiz, int chave) {
    struct nodo* nodoAux = buscar(*raiz, chave);
    if (nodoAux == NULL)
        return 0;
    struct nodo* nodo = excluirBinario(raiz, nodoAux);
    if (nodo == NULL)
        return 1;
    struct nodo* aux = atualizaBalancoExcluir(nodo);
    while (aux != NULL) {
        if (aux->pai == NULL) {
            corrigeAvl(raiz);
            aux = NULL;
        } else {
            corrigeAvl(&aux);
            if (aux->balanco == 0)
                aux = atualizaBalancoExcluir(aux);
            else
                aux = NULL;
        }
    }
    return 1;
}

struct nodo* buscar(struct nodo* nodo, int chave) {
    if ((nodo == NULL) || (nodo->chave == chave))
        return nodo;
    if (chave < nodo->chave)
        return buscar(nodo->fe, chave);
    return buscar(nodo->fd, chave);
}

void imprimirEmOrdem(struct nodo* nodo) {
    if (nodo != NULL) {
        imprimirEmOrdem(nodo->fe);
        printf("%d ", nodo->chave);
        imprimirEmOrdem(nodo->fd);
    }
}

void imprimirEmLargura(struct nodo* raiz) {
    if (raiz == NULL) {
        printf("Arvore vazia\n");
        return;
    }
    struct fila* f1 = cria_fila();
    insere_fila(f1, raiz);
    int i = 0;
    int cont = 1;
    int aux = 0;
    printf("[%d]", i);
    while (!(vazia_fila(f1))) {
        retira_fila(f1, &raiz);
        cont--;
        if (raiz->fe) {
            insere_fila(f1, raiz->fe);
            aux++;
        }
        if (raiz->fd) {
            insere_fila(f1, raiz->fd);
            aux++;
        }
        if (cont == 0) {
            printf(" %d(%d)\n", raiz->chave, raiz->balanco);
            i++;
            if (aux > 0)
                printf("[%d]", i);
            cont = aux;
            aux = 0;
        } else {
            printf(" %d(%d)", raiz->chave, raiz->balanco);
        }
    }
    destroi_fila(f1);
    f1 = NULL;
}

void destroiArvore(struct nodo* nodo) {
    if (nodo != NULL) {
        destroiArvore(nodo->fe);
        destroiArvore(nodo->fd);
        free(nodo);
    }
}