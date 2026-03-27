#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "avl.h"

// Função auxiliar para retornar o maior entre dois valores inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Retorna a altura de um nó, ou 0 se ele for NULL
int altura(No* n) {
    return (n == NULL) ? 0 : n->altura;
}

// Cria um novo nó com a chave fornecida, sem filhos e com altura 1
No* novoNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->esq = no->dir = NULL;
    no->altura = 1;  // Um nó recém-criado sempre começa com altura 1
    return no;
}

// Calcula o fator de balanceamento de um nó
// FB = altura(esquerda) - altura(direita)
int fatorBalanceamento(No* n) {
    if (n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

// Rotação simples à direita
No* rotacaoDireita(No* y) {
    No* x = y->esq;      // x será a nova raiz da subárvore
    No* T2 = x->dir;     // T2 é a subárvore que será movida

    // Realiza a rotação
    x->dir = y;
    y->esq = T2;

    // Atualiza as alturas dos nós envolvidos
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;  // x agora é a nova raiz da subárvore
}

// Rotação simples à esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->dir;      // y será a nova raiz da subárvore
    No* T2 = y->esq;     // T2 é a subárvore que será movida

    // Realiza a rotação
    y->esq = x;
    x->dir = T2;

    // Atualiza as alturas
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;  // y agora é a nova raiz da subárvore
}

// Função para balancear um nó da árvore após inserção ou remoção
No* balancear(No* raiz) {
    int fb = fatorBalanceamento(raiz);

    // Caso 1: desbalanceado à esquerda (FB > 1)
    if (fb > 1) {
        // Subcaso: rotação dupla (esquerda-direita)
        if (fatorBalanceamento(raiz->esq) < 0)
            raiz->esq = rotacaoEsquerda(raiz->esq);

        // Rotação simples à direita
        return rotacaoDireita(raiz);
    }

    // Caso 2: desbalanceado à direita (FB < -1)
    if (fb < -1) {
        // Subcaso: rotação dupla (direita-esquerda)
        if (fatorBalanceamento(raiz->dir) > 0)
            raiz->dir = rotacaoDireita(raiz->dir);

        // Rotação simples à esquerda
        return rotacaoEsquerda(raiz);
    }

    // Se estiver balanceado, não faz nada
    return raiz;
}

// Função para inserir um novo nó na árvore AVL
No* inserir(No* raiz, int chave) {
    if (raiz == NULL)  // Caso base: árvore vazia
        return novoNo(chave);

    // Inserção normal de BST
    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    else
        return raiz;  // Ignora duplicatas

    // Atualiza a altura do nó atual
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    // Balanceia a subárvore enraizada em raiz
    return balancear(raiz);
}

// Encontra o nó com o menor valor na árvore (usado para remoção)
No* encontrarMinimo(No* raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

// Remove um nó com a chave fornecida da árvore AVL
No* remover(No* raiz, int chave) {
    if (raiz == NULL)
        return NULL;

    // Caminha pela árvore para encontrar o nó
    if (chave < raiz->chave)
        raiz->esq = remover(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = remover(raiz->dir, chave);
    else {
        // Nó com um ou nenhum filho
        if (raiz->esq == NULL || raiz->dir == NULL) {
            No* temp = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz);  // Libera memória
            return temp;
        }

        // Nó com dois filhos: substitui pela menor chave da subárvore direita
        No* temp = encontrarMinimo(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = remover(raiz->dir, temp->chave);
    }

    // Atualiza a altura e balanceia
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
    return balancear(raiz);
}

// Imprime os nós da árvore em pré-ordem (raiz, esquerda, direita)
void imprimirPreOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d, ", raiz->chave);
        imprimirPreOrdem(raiz->esq);
        imprimirPreOrdem(raiz->dir);
    }
}

// Busca por uma chave na árvore e retorna o nó correspondente
No* pesquisar(No* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return pesquisar(raiz->esq, chave);
    else
        return pesquisar(raiz->dir, chave);
}

// Encontra o sucessor de uma chave (o menor valor maior que a chave)
int encontrarSucessor(No* raiz, int chave) {
    No* atual = pesquisar(raiz, chave);
    if (!atual) return -1;  // Chave não encontrada

    if (atual->dir)
        return encontrarMinimo(atual->dir)->chave;

    // Se não há filho à direita, sobe pela árvore para achar o sucessor
    No* sucessor = NULL;
    No* antecessor = raiz;

    while (antecessor != NULL && antecessor != atual) {
        if (chave < antecessor->chave) {
            sucessor = antecessor;
            antecessor = antecessor->esq;
        } else {
            antecessor = antecessor->dir;
        }
    }

    return sucessor ? sucessor->chave : -1;
}

// Verifica se um número é primo
int ehPrimo(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2)
        if (num % i == 0)
            return 0;
    return 1;
}

// Conta quantos nós da árvore têm valor primo
int contarPrimos(No* raiz) {
    if (!raiz) return 0;

    int cont = ehPrimo(raiz->chave) ? 1 : 0;
    return cont + contarPrimos(raiz->esq) + contarPrimos(raiz->dir);
}

