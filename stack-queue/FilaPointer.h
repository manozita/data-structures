/* Fila de pointer */
/*
  Arquivo: FilaPointer.h
  Autor: Fub�
  Data: 28/08/24 15:06
  Descri��o: Este programa implementa um pacote de fun��es para o tipo Fila.
  Os elementos da Fila s�o endere�os - tipo pointer "coringa".
  A fila � representada por uma lista ligada simples com cabe�a.
*/
#pragma once
#include "Booleano.h"

typedef struct Celula{
    void *item;          /* item � um pointer */
    struct Celula *next; /* o campo next guarda o endere�o do elemento seguinte da fila */
} Celula;

typedef struct{
    Celula *inicio;      /* inicio tem o endere�o do primeiro da fila */
    Celula *fim;         /* fim guarda o endere�o do ultimo da fila */
} Fila;


// prototipos das fun��es
void criarFilaVazia(Fila *);  /* o construtor cria a fila vazia */

void *acessarFila(Fila *);      /* devolve o primeiro da fila */
bool verificarFilaVazia(Fila *);  /* devolve 1 se a fila estiver vazia */

void pushFila(Fila *, void *);   /* coloca o valor dado no fim da fila */
void popFila(Fila *);           /* retira o primeiro da fila */


// implementa��es
void criarFilaVazia(Fila *fi){
    fi->inicio = NULL;
    fi->fim = NULL;
}
void *acessarFila(Fila *fi){
    Celula *aux;
    void * valor;
    aux = fi->inicio;
    if (aux == NULL) valor = NULL;
    else valor = aux->item;
    return valor;
}
bool verificarFilaVazia(Fila *fi){
    bool vazia;
    Celula *aux;
    aux = fi->inicio;
    if (aux == NULL) vazia = TRUE; else vazia = FALSE;
    return vazia;
}
void pushFila(Fila *fi, void *ap){
    Celula *p, *aux;
    p = (Celula *)malloc(sizeof(Celula));
    p->item = ap; p->next = NULL;
    if (fi->inicio == NULL) fi->inicio = p; else {aux = fi->fim;  aux->next = p;}
    fi->fim = p;
}

void popFila(Fila *fi){
    Celula *seg, *pri;
    pri = fi->inicio;
    if (fi->inicio != NULL){
    	if (fi->inicio == fi->fim) {fi->inicio = NULL; fi->fim = NULL;}
    	else {seg = pri->next; fi->inicio = seg;}
    }
}
