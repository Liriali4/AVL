#ifndef AVL_H
#define AVL_H

typedef struct No {
    int chave;
    int altura;
    struct No *esq;
    struct No *dir;
} No;

No* inserir(No* raiz, int chave);
No* remover(No* raiz, int chave);
void imprimirPreOrdem(No* raiz);
No* pesquisar(No* raiz, int chave);
int encontrarSucessor(No* raiz, int chave);
int contarPrimos(No* raiz);

#endif

