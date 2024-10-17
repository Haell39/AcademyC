#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *prox; //ponteiro
} No; //para o proximo nó

typedef struct {
    No * cabeca;
} Lista_Encadeada;

//Inicializando a Linked List

void inilinkedList(Lista_Encadeada *lista) {
    lista->cabeca = NULL; //inicializa a cabeça como NULL
}

// Adding elements (inserção no inicio)

void addElementEncaded(Lista_Encadeada *lista, int item) {
    No *novo_no = (No*)malloc(sizeof(No)); //aloca mem para um novo nó
    novo_no -> dado = item; // define o valor do nó
    novo_no -> prox = lista->cabeca; // define o proximo nó
    lista->cabeca = novo_no; // atualiza cabeça para o novo nó
    printf("%d added to the linked list\n", item);
    
}
