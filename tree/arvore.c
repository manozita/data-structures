#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "/Users/manoela/Documents/data-structures/stack-queue/FilaPointer.h"
#include "/Users/manoela/Documents/data-structures/stack-queue/PilhaPointer.h"

//
// Created by Manoela Macchion Martedi on 04/09/24.
//
typedef struct No {
    int elemento;
    struct No *esq;
    struct No *dir;
} No;
typedef No *Arvore;

// Interface
Arvore criarArvoreVazia();                      // Cria uma árvore vazia
Arvore construirArvore(int, Arvore, Arvore);    // Constrói uma árvore com raiz e os seus dois filhos
Arvore construirExemplo();                      // Constrói um exemplo de árvore
Arvore construirArvoreRam(int);                 // Constrói árvore perfeitamente balanceada

int    obterAltura(Arvore);                     // Devolve a altura da árvore
int    contarNos(Arvore);                       // Devolve a quantidade de nós da árvore

void   mostrarArvore_eRd(Arvore ap);            // Mostra uma árvore não recursivamente pelo caminhamento eRd

void   mostrarArvore_Rec_eRd(Arvore);           // Mostra uma árvore recursivamente pelo caminhamento eRd
void   mostrarArvore_Rec_Red(Arvore);           // Mostra uma árvore recursivamente pelo caminhamento Red
void   mostrarArvore_Rec_edR(Arvore);           // Mostra uma árvore recursivamente pelo caminhamento edR
void   mostrarArvore_bfs(Arvore);               // Mostra uma árvore pelo caminhamento bfs usando fila auxiliar

void   mostrarPrimeiro_eRd(Arvore);             // Mostra o primeiro nó visitado numa árvore binária pelo caminhamento eRd



Arvore criarArvoreVazia() {
    Arvore ap;
    ap = NULL; // Inicializa um apontador para árvore com valor vazio
    return ap;
}

Arvore construirArvore(int el, Arvore a, Arvore b) {
    Arvore c;
    c = (Arvore) malloc(sizeof(No));
    c -> elemento = el;
    c -> esq = a;
    c -> dir = b;
    return c;
}

Arvore construirExemplo() {
    Arvore a,b,c;
    a = construirArvore(4, NULL, NULL);
    c = construirArvore(5, NULL, NULL);
    a = construirArvore(2, a, c);

    b = construirArvore(6, NULL, NULL);
    c = construirArvore(7, NULL, NULL);
    c = construirArvore(3, b, c);

    b = construirArvore(1, a, c);
    return b;
}

Arvore construirArvoreRam(int n) {
    Arvore a;
    if (n != 0) {
        int n1, n2, el; // Tamanho dos nós filhos
        n1 = n/2; n2 = n - n1 -1;
        el = rand()%50;
        a = construirArvore(el, construirArvoreRam(n1), construirArvoreRam(n2));
    } else {
        a = NULL;
    }
    return a;
}



int obterAltura(Arvore ap) {
    int altura;
    if (ap != NULL) {
        altura = 1 + (obterAltura(ap->esq) > obterAltura(ap->dir) ? obterAltura(ap->esq) : obterAltura(ap->dir));
        // A altura esquerda é maior que a direita? Soma a maior altura à var altura
    } else { // Árvore vazia
        altura = -1;
    }
    return altura;
}

int contarNos(Arvore ap) {
    int quantidadeNos; // A quantidade de nós = quantidade de nós esquerdos + direitos + o nó atual
    if (ap != NULL) {
        quantidadeNos = 1 + contarNos(ap->esq) + contarNos(ap->dir);
    } else {
        quantidadeNos = 0; // Árvore vazia tem 0 nós
    }
    return quantidadeNos;
}



void mostrarArvore_Rec_eRd(Arvore ap) {
    if (ap != NULL) { // Se o apontador não for vazio
        mostrarArvore_Rec_eRd(ap->esq);
        printf("%d ", ap->elemento);
        mostrarArvore_Rec_eRd(ap->dir);
    }
}

void mostrarArvore_eRd(Arvore ap) {
    Pilha p;
    if (ap != NULL) {
        criarPilhaVazia(&p);
        do {
            while (ap -> dir != NULL) {
                ap = ap -> dir;
            }
            pushPilha(&p, &ap->elemento);
        } while (!verificarPilhaVazia(&p));
    }
}

void mostrarArvore_Rec_Red(Arvore ap) {
    if (ap != NULL) { // Se o apontador não for vazio
        printf("%d ", ap->elemento);
        mostrarArvore_Rec_Red(ap->esq);
        mostrarArvore_Rec_Red(ap->dir);
    }
}

void mostrarArvore_Rec_edR(Arvore ap) {
    if (ap != NULL) { // Se o apontador não for vazio
        mostrarArvore_Rec_edR(ap->esq);
        mostrarArvore_Rec_edR(ap->dir);
        printf("%d ", ap->elemento);
    }
}

void mostrarArvore_bfs(Arvore ap) {
    No *p;  Fila f;
    if (ap != NULL) { // Se o apontador não for vazio
        criarFilaVazia(&f); p = ap; pushFila(&f,p); // Cria uma nova fila e insere o nó raiz da árvore
        do {
            p = acessarFila(&f); // O nó p se torna o primeiro elemento da fila
            printf("%d ", p->elemento);
            popFila(&f); // Retira o primeiro elemento da fila, mas o nó p ainda é o mesmo
            if (p->esq != NULL) { // Se o nó tem filho esquerdo
                pushFila(&f, p->esq); // Adiciona ao fim da fila
            }
            if (p->dir != NULL) { // Se o nó tem filho direito
                pushFila(&f, p->dir); // Adiciona ao fim da fila
            }
        } while (verificarFilaVazia(&f) == FALSE); // Até que todos os itens da fila tenham sido impressos
    }
}

void   mostrarPrimeiro_eRd(Arvore ap) { // Vai tudo pra esquerda até encontrar o primeiro elemento
    No *p;
    if (ap != NULL) {
        p = ap;
        while (p->esq != NULL) {
            p = p->esq;
        }
        printf("%d", p->elemento);
    }
}



// Implementação

int main () {
    Arvore a;
    a = construirExemplo();
    printf("Altura da árvore A: %d", obterAltura(a));
    printf("Quantidade de nós A: %d", contarNos(a));
    printf("\nCaminhamento eRd recursivo A: \n");
    mostrarArvore_Rec_eRd(a); // Esperado: 4,2,5,1,6,3,7
    printf("\nPrimeiro elemento eRd A: \n");
    mostrarPrimeiro_eRd(a);  // Esperado: 4
    printf("\nCaminhamento Red recursivo A: \n");
    mostrarArvore_Rec_Red(a); // Esperado: 1,2,4,5,3,6,7
    printf("\nCaminhamento edR recursivo A: \n");
    mostrarArvore_Rec_edR(a); // Esperado: 4,5,2,6,7,3,1
    printf("\nCaminhamento bfs com fila auxiliar A: \n");
    mostrarArvore_bfs(a);    // Esperado: 1,2,3,4,5,6,7
    free(a);

    Arvore b;
    srand(time(NULL)); // Inicia o gerador de números aleatórios para construirArvoreRam
    b = construirArvoreRam(15);
    if (b != NULL) {
        printf("\n\nAltura da árvore B: %d", obterAltura(b));
        printf("\nQuantidade de nós B: %d", contarNos(b));
        printf("\nCaminhamento eRd recursivo B: \n");
        mostrarArvore_Rec_eRd(b);
        printf("\nPrimeiro elemento eRd B: \n");
        mostrarPrimeiro_eRd(b);
        printf("\nCaminhamento Red recursivo B: \n");
        mostrarArvore_Rec_Red(b);
        printf("\nCaminhamento edR recursivo B: \n");
        mostrarArvore_Rec_edR(b);
        printf("\nCaminhamento bfs com fila auxiliar B: \n");
        mostrarArvore_bfs(b);
        free(b);
    }
    return 0;
}


