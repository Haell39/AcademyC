#include <stdio.h>
#include <stdlib.h>

#define TAM 5

typedef struct {
    int id;
    char marca[50];
    char modelo[50];
    int ano;
    char cor[20];
    float quilometragem;
    float valor;
    char categoria[30];
    char disponibilidade; // 'D' para disponível, 'N' para não disponível
} Carro;

typedef struct {
    int id; // quantidade de elementos
    Carro *elementos; // vetor de carros
} Lista;

// Funções implementadas
int atualizarCarro(Lista*, int, Carro);
int buscarCarro(Lista*, int);
Lista* criarLista();
Lista* excluirLista(Lista*);
void imprimirCarros(Lista*);
int inserirCarro(Lista*, Carro);
int inserirCarroID(Lista*, Carro, int);
int inserirCarroInicio(Lista*, Carro);
int removerCarro(Lista*, int);

// Funções para carregar e salvar dados
void carregarDados(Lista*);
void salvarDados(Lista*);

int main() {
    Lista *lista = criarLista();
    
    // Carregar dados do arquivo
    carregarDados(lista);
    
    // Exemplo de chamada das funções
    imprimirCarros(lista);

    Carro carro1 = {1, "Toyota", "Corolla", 2020, "Preto", 15000.0, 95000.0, "Sedan", 'D'};
    Carro carro2 = {2, "Honda", "Civic", 2021, "Branco", 5000.0, 105000.0, "Sedan", 'D'};
    Carro carro3 = {3, "Ford", "Fiesta", 2019, "Vermelho", 30000.0, 65000.0, "Hatch", 'D'};
    
    inserirCarro(lista, carro1);
    inserirCarro(lista, carro2);
    inserirCarro(lista, carro3);

    imprimirCarros(lista);

    removerCarro(lista, 2);
    imprimirCarros(lista);

    int busca = buscarCarro(lista, 1);
    if (busca != -1) {
        printf("Carro encontrado: %s %s\n", lista->elementos[busca].marca, lista->elementos[busca].modelo);
    } else {
        printf("Carro nao encontrado\n");
    }

    carro1.valor = 90000.0; // Atualizando o valor do carro
    atualizarCarro(lista, 1, carro1);
    imprimirCarros(lista);

    Carro carro4 = {4, "Chevrolet", "Onix", 2022, "Azul", 0.0, 78000.0, "Hatch", 'D'};
    inserirCarroInicio(lista, carro4);
    imprimirCarros(lista);

    // Salvar dados antes de excluir a lista
    salvarDados(lista);
    lista = excluirLista(lista);
    
    return 0;
}

void carregarDados(Lista *lista) {
    FILE *file = fopen("C:/Users/User/c/Carros.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    Carro carro;
    while (fscanf(file, "%d %49s %49s %d %19s %f %f %29s %c",
                  &carro.id, carro.marca, carro.modelo, 
                  &carro.ano, carro.cor, &carro.quilometragem, 
                  &carro.valor, carro.categoria, &carro.disponibilidade) != EOF) {
        inserirCarro(lista, carro);
    }
    fclose(file);
}

void salvarDados(Lista *lista) {
    FILE *file = fopen("C:/Users/User/c/Carros.txt", "w");
    if (file == NULL) {
        printf("Erro ao salvar arquivo.\n");
        return;
    }
    
    for (int i = 0; i < lista->id; ++i) {
        Carro *p = &lista->elementos[i];
        fprintf(file, "%d %s %s %d %s %.2f %.2f %s %c\n", 
                p->id, p->marca, p->modelo, p->ano, p->cor, 
                p->quilometragem, p->valor, p->categoria, p->disponibilidade);
    }
    fclose(file);
}


int atualizarCarro(Lista *lista, int id, Carro carro) {
    int i;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    for (i = 0; i < lista->id; ++i) {
        if (lista->elementos[i].id == id) {
            lista->elementos[i] = carro;
            return 1;
        }
    }
    return 0;
}

int buscarCarro(Lista *lista, int id) {
    int i;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return -1;
    }

    for (i = 0; i < lista->id; ++i) {
        if (lista->elementos[i].id == id) {
            return i;
        }
    }

    return -1;
}

Lista* criarLista() {
    Lista nova = (Lista)malloc(sizeof(Lista));

    if (nova == NULL) {
        printf("Nao tem espaco\n");
        return NULL;
    }
    nova->id = 0; 
    nova->elementos = (Carro*)malloc(TAM * sizeof(Carro));
    
    if (nova->elementos == NULL) {
        printf("Nao tem espaco\n");
        free(nova);
        return NULL;
    }

    return nova;
}




/parte de wesley/

Lista* excluirLista(Lista *lista) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return NULL;
    }

    free(lista->elementos);
    free(lista);
    return NULL;
}

void imprimirCarros(Lista *lista) {
    int i;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return;
    }

    if (lista->id == 0) {
        printf("Lista vazia\n");
        return;
    }

    for (i = 0; i < lista->id; ++i) {
        printf("ID: %d, Marca: %s, Modelo: %s, Ano: %d, Cor: %s, Quilometragem: %.2f, Valor: %.2f, Categoria: %s, Disponibilidade: %c\n",
            lista->elementos[i].id, lista->elementos[i].marca, lista->elementos[i].modelo,
            lista->elementos[i].ano, lista->elementos[i].cor, lista->elementos[i].quilometragem,
            lista->elementos[i].valor, lista->elementos[i].categoria, lista->elementos[i].disponibilidade);
    }
}

int inserirCarro(Lista *lista, Carro carro) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    
    if (lista->id < TAM) {
        lista->elementos[lista->id] = carro;
        ++(lista->id);
    } else {
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}

int inserirCarroID(Lista *lista, Carro carro, int posicao) {
    int i;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    if (lista->id < TAM) {
        if (posicao < lista->id) {
            for (i = lista->id; i > posicao; --i) {
                lista->elementos[i] = lista->elementos[i - 1];
            }
            lista->elementos[posicao] = carro;
            ++(lista->id);
        } else {
            printf("Posicao fora do intervalo permitido\n");
        }
    } else {
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}

int inserirCarroInicio(Lista *lista, Carro carro) {
    int i;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    if (lista->id < TAM) {
        for (i = lista->id; i > 0; --i) {
            lista->elementos[i] = lista->elementos[i - 1];
        }
        lista->elementos[0] = carro;
        ++(lista->id);
    } else {
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}





int removerCarro(Lista *lista, int id) {
    int i, j;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    for (i = 0; i < lista->id; ++i) {
        if (lista->elementos[i].id == id) {
            for (j = i; j < lista->id - 1; ++j) {
                lista->elementos[j] = lista->elementos[j + 1];
            }
            --(lista->id);
            return 1;
        }
    }
    
    return 0;
}