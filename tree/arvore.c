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

// --> Recursivo
int    obterAltura_rec(Arvore);                 // Devolve a altura da árvore, recursivamente
int    contarNos_rec(Arvore);                   // Devolve a quantidade de nós da árvore, recursivo
void   mostrarArvore_rec_eRd(Arvore);           // Mostra uma árvore recursivamente pelo caminhamento eRd
void   mostrarArvore_rec_edR(Arvore);           // Mostra uma árvore recursivamente pelo caminhamento edR
void   mostrarArvore_rec_Red(Arvore);           // Mostra uma árvore recursivamente pelo caminhamento Red
No    *buscar_rec(Arvore, int);                 // Devolve o nó que contém o valor dado, busca recursivamente

// --> Não recursivo
int    obterAltura(Arvore);                     // Devolve a altura da árvore, não recursivamente
int    contarNos(Arvore ap);                    // Devolve a quantidade de nós da árvore
void   mostrarArvore_eRd(Arvore ap);            // Mostra uma árvore não recursivamente pelo caminhamento eRd
void   mostrarArvore_Red(Arvore);               // Mostra uma árvore não recursivamente pelo caminhamento Red
void   mostrarArvore_bfs(Arvore);               // Mostra uma árvore pelo caminhamento bfs usando fila auxiliar
void   mostrarPrimeiro_eRd(Arvore);             // Mostra o primeiro nó visitado numa árvore binária pelo caminhamento eRd
void   mostrarUltimo_eRd(Arvore);               // Mostra o último nó visitado numa árvore binária pelo caminhamento eRd
No    *obterSeguinte_eRd(Arvore, int);          // Devolve o nó seguinte do nó que contém o valor dado
// ARRUMAR obteraltura, obterseguinteerd



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



int obterAltura_rec(Arvore ap) {
    int altura;
    if (ap != NULL) {
        int aEsq, aDir;
        aEsq = obterAltura_rec(ap->esq);
        aDir = obterAltura_rec(ap->dir);
        // A altura esquerda é maior que a direita? Soma a maior altura à var altura
        if (aEsq > aDir) {
            altura = aEsq;
        } else {
            altura = aDir;
        }
        altura++; // Soma 1 à altura
    } else { // Árvore vazia
        altura = -1;
    }
    return altura;
}

int obterAltura(Arvore ap) { // Não recursivamente, usando o caminhamento BFS !!!!!!!!!!!!!!
    int altura = 0;
    if (ap != NULL) {
        Fila f; criarFilaVazia(&f);
        int numNosNivel; // Número de nós no nível
        No *n = ap; pushFila(&f,n); // Cria uma nova fila e insere o nó raiz da árvore
        do {
            altura++;
            n = acessarFila(&f); // O nó p se torna o primeiro elemento da fila
            popFila(&f); // Retira o primeiro elemento da fila, mas o nó p ainda é o mesmo
            if (n->esq != NULL) { // Se o nó tem filho esquerdo
                pushFila(&f, n->esq); // Adiciona ao fim da fila
            }
            if (n->dir != NULL) { // Se o nó tem filho direito
                pushFila(&f, n->dir); // Adiciona ao fim da fila
            }
        } while (!verificarFilaVazia(&f)); // Até que a fila esteja vazia
    }
    return altura;
}

int contarNos_rec(Arvore ap) {
    int quantidadeNos; // A quantidade de nós = quantidade de nós esquerdos + direitos + o nó atual
    if (ap != NULL) {
        quantidadeNos = 1 + contarNos_rec(ap->esq) + contarNos_rec(ap->dir);
    } else {
        quantidadeNos = 0; // Árvore vazia tem 0 nós
    }
    return quantidadeNos;
}

int contarNos(Arvore ap) {
    int quantidadeNos = 0; // A quantidade de nós = quantidade de nós esquerdos + direitos + o nó atual
    if (ap != NULL) {
        No *p = ap;
        Fila f; criarFilaVazia(&f); pushFila(&f, p);
        do {
            p = acessarFila(&f);
            popFila(&f);
            quantidadeNos++;

            if (p->esq != NULL) {
                pushFila(&f, p->esq);
            }
            if (p->dir != NULL) {
                pushFila(&f, p->dir);
            }
        } while (!verificarFilaVazia(&f));
    }
    return quantidadeNos;
}

int contarFolhas_rec (Arvore ap) {
    int numFolhas;
    if (ap == NULL) {
        numFolhas = 0;
    } else if (ap->esq == NULL && ap->dir == NULL) {
        numFolhas = 1;
    } else {
        numFolhas = contarFolhas_rec(ap->esq) + contarFolhas_rec(ap->dir);
    }
    return numFolhas;
}



void mostrarArvore_rec_eRd(Arvore ap) {
    if (ap != NULL) { // Se o apontador não for vazio
        mostrarArvore_rec_eRd(ap->esq);
        printf("%d ", ap->elemento);
        mostrarArvore_rec_eRd(ap->dir);
    }
}

void mostrarArvore_eRd(Arvore ap) { // Mostra a árvore no caminhamento eRd não recursivamente
    if (ap != NULL) {
        Pilha p; No *no = ap;
        criarPilhaVazia(&p);
        do {
            while (no != NULL) { // Encontrar o elemento mais para a esquerda
                pushPilha(&p, no); // 1. Adiciona na pilha
                no = no -> esq; // 2. Vai para a esquerda
            }
            no = acessarTopo(&p); // ap, que estava vazio, agora apontará para o topo da pilha
            popPilha(&p);
            printf("%d ", no->elemento); // Remove o último da pilha e imprime
            no = no->dir; // Vai um para a direita e repete
        } while (!verificarPilhaVazia(&p) && no != NULL); // repita até que não haja elementos na pilha e que o apontador seja vazio
    }
}

void mostrarArvore_rec_Red(Arvore ap) {
    if (ap != NULL) { // Se o apontador não for vazio
        printf("%d ", ap->elemento);
        mostrarArvore_rec_Red(ap->esq);
        mostrarArvore_rec_Red(ap->dir);
    }
}

void mostrarArvore_Red(Arvore ap) { // Mostra a árvore no caminhamento Red não recursivamente
    Pilha s; No *p = ap;
    if (p != NULL) {
        criarPilhaVazia(&s);
        pushPilha(&s, p);
        do {
            p = acessarTopo(&s);
            printf("%d ", p->elemento);
            popPilha(&s);

            if (p->dir != NULL) {
                pushPilha(&s, p->dir);
            }
            if (p->esq != NULL) {
                pushPilha(&s, p->esq);
            }
        } while (!verificarPilhaVazia(&s));
    }
}

void mostrarArvore_rec_edR(Arvore ap) {
    if (ap != NULL) { // Se o apontador não for vazio
        mostrarArvore_rec_edR(ap->esq);
        mostrarArvore_rec_edR(ap->dir);
        printf("%d ", ap->elemento);
    }
}

void mostrarArvore_bfs(Arvore ap) {
    if (ap != NULL) { // Se o apontador não for vazio
        No *p;  Fila f;
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

void mostrarPrimeiro_eRd(Arvore ap) { // Vai tudo pra esquerda até encontrar o primeiro elemento
    if (ap != NULL) {
        No *p;
        p = ap;
        while (p->esq != NULL) {
            p = p->esq;
        }
        printf("%d", p->elemento);
    }
}

void mostrarUltimo_eRd(Arvore ap) { // Vai tudo pra direita até encontrar o último elemento
    if (ap != NULL) {
        No *p;
        p = ap;
        while (p->dir != NULL) {
            p = p->dir;
        }
        printf("%d", p->elemento);
    }

}



No *buscar_rec(Arvore ap, int el) {
    No *p;
    if (ap == NULL || ap->elemento == el) { // Se o elemento for a raiz da árvore ou a árvore for vazia
        p = ap;
    } else {
        p = buscar_rec(ap->esq,el); // Busca o elemento na esquerda da árvore
        if (p == NULL) { // Se o elemento não estiver presente na esquerda da árvore
            p = buscar_rec(ap->dir,el); // Busca o elemento na direita da árvore
        }
    }
    return p;
}

No *buscar(Arvore ap, int el) {
    No *p; Fila f;
    if (ap == NULL || ap->elemento == el) { // Se o elemento for a raiz da árvore ou a árvore for vazia
        p = ap;
    } else {
        p = ap;
        criarFilaVazia(&f); pushFila(&f,p);
        do {
            p = acessarFila(&f);
            popFila(&f);
            if (p->esq!=NULL) pushFila(&f,p->esq);
            if (p->dir!=NULL) pushFila(&f,p->dir);
        } while (!verificarFilaVazia(&f) || p->elemento != el);
        p = buscar_rec(ap->esq,el); // Busca o elemento na esquerda da árvore
        if (p == NULL) { // Se o elemento não estiver presente na esquerda da árvore
            p = buscar_rec(ap->dir,el); // Busca o elemento na direita da árvore
        }
    }
    return p;
}

No *obterSeguinte_eRd(Arvore ap, int el) { // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    No *no = ap;
    No *ant;
    if (ap != NULL) {
        Pilha p;
        criarPilhaVazia(&p);
        do {
            while (no != NULL) { // Encontrar o elemento mais para a esquerda
                pushPilha(&p, no); // 1. Adiciona na pilha
                ant = no;
                no = no -> esq; // 2. Vai para a esquerda
            }
            no = acessarTopo(&p); // ap, que estava vazio, agora apontará para o topo da pilha
            popPilha(&p);
            if (no->elemento == el) {

            }
            ant = no;
            no = no->dir; // Vai um para a direita e repete
        } while (!verificarPilhaVazia(&p) || no != NULL); // repita até que não haja elementos na pilha e que o apontador seja vazio
    }
    return no;
}



// Implementação

int main () {
    Arvore a;
    a = construirExemplo();
    printf("Altura da árvore A: %d", obterAltura_rec(a));
    printf("Quantidade de nós A: %d", contarNos_rec(a));
    printf("\nCaminhamento eRd recursivo A: \n");
    mostrarArvore_rec_eRd(a); // Esperado: 4,2,5,1,6,3,7
    printf("\nPrimeiro elemento eRd A: \n");
    mostrarPrimeiro_eRd(a);  // Esperado: 4
    printf("\nCaminhamento Red recursivo A: \n");
    mostrarArvore_rec_Red(a); // Esperado: 1,2,4,5,3,6,7
    printf("\nCaminhamento edR recursivo A: \n");
    mostrarArvore_rec_edR(a); // Esperado: 4,5,2,6,7,3,1
    printf("\nCaminhamento bfs com fila auxiliar A: \n");
    mostrarArvore_bfs(a);    // Esperado: 1,2,3,4,5,6,7
    printf("\nBusca recursiva do elemento %d: \n%d", 7, buscar_rec(a, 7)->elemento);
    free(a);

    Arvore b;
    srand(time(NULL)); // Inicia o gerador de números aleatórios para construirArvoreRam
    b = construirArvoreRam(15);
    if (b != NULL) {
        printf("\n\nAltura da árvore B: %d", obterAltura_rec(b));
        printf("\nQuantidade de nós B: %d", contarNos_rec(b));
        printf("\nCaminhamento eRd recursivo B: \n");
        mostrarArvore_rec_eRd(b);
        printf("\nPrimeiro elemento eRd B: \n");
        mostrarPrimeiro_eRd(b);
        printf("\nCaminhamento Red recursivo B: \n");
        mostrarArvore_rec_Red(b);
        printf("\nCaminhamento edR recursivo B: \n");
        mostrarArvore_rec_edR(b);
        printf("\nCaminhamento bfs com fila auxiliar B: \n");
        mostrarArvore_bfs(b);
        free(b);
    }
    return 0;
}


