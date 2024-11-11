#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definicao da estrutura para Pacote de Viagem */
typedef struct pacote
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
} Pacote;

/* ^^ Aqui é a estrutura do nó da lista */
typedef struct listaNo
{
    Pacote *pacote;
    struct listaNo *prox;
} ListaNo;

typedef struct lista
{
    ListaNo *prim;
} Lista;

/* ^^ ^^ Aqui sao as funcões da lista */
int atualizarPacote(Lista *, int, Pacote *);
ListaNo *buscarPacote(Lista *, int);
Lista *criarLista();
int inserirPacote(Lista *, Pacote *);
void imprimirPacotes(Lista *);
int removerPacote(Lista *, int);
Lista *excluirLista(Lista *);
int salvarLista(Lista *);
int carregarLista(Lista *);

int main()
{
    /* ^^ Aqui tem um ponteiro para a lista de pacotes */
    Lista *lista = criarLista();
    ListaNo *pesquisa = NULL;

    /* ^^ Aqui se tiver pacotes, ele vai carregar */
    carregarLista(lista);

    /* ^^ Aqui sao os pacotes e os dados de cada pacote */
    Pacote pacote1 = {1, "Rio de Janeiro", 1500.0, 5, 'A'};
    Pacote pacote2 = {2, "Sao Paulo", 1200.0, 3, 'B'};
    Pacote pacote3 = {3, "Bahia", 2000.0, 7, 'A'};

    inserirPacote(lista, &pacote1);
    inserirPacote(lista, &pacote2);
    inserirPacote(lista, &pacote3);

    imprimirPacotes(lista);

    /* ^^ Aqui vai salvar a lista em um arquivo */
    salvarLista(lista);

    /* ^^ Aqui vai buscar pelo pacote com o id 1 */
    pesquisa = buscarPacote(lista, 1);
    if (pesquisa == NULL)
    {
        printf("Pacote nao encontrado\n");
    }
    else
    {
        printf("Pacote encontrado: %s\n", pesquisa->pacote->destino);
    }

    /* ^^ Aqui vai remover o pacote com o id 1 */
    printf("Removendo o pacote com ID 1\n");
    removerPacote(lista, 1);
    imprimirPacotes(lista);

    lista = excluirLista(lista);
    return 0;
}

/* ^^ Aqui vai atualizar os dados de um pacote na lista */
int atualizarPacote(Lista *lista, int id, Pacote *novoPacote)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista nao foi criada\n");
        return 0;
    }

    ListaNo *p;

    /* ^^ Aqui vai percorrer a lista procurando o pacote com o id fornecido */
    for (p = lista->prim; p != NULL; p = p->prox)
    {
        if (p->pacote->id == id)
        {
            *(p->pacote) = *novoPacote;
            return 1;
        }
    }

    return 0;
}

/* ^^ Aqui é a funcao que vai buscar um pacote pelo seu id */
ListaNo *buscarPacote(Lista *lista, int id)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista nao foi criada ou esta vazia\n");
        return NULL;
    }

    ListaNo *p;

    for (p = lista->prim; p != NULL; p = p->prox)
    {
        if (p->pacote->id == id)
        {
            return p;
        }
    }

    return NULL;
}

/* ^^ Aqui vai criar uma nova lista */
Lista *criarLista()
{
    Lista *nova = (Lista *)malloc(sizeof(Lista));

    if (nova == NULL)
    {
        printf("Sem espaco\n");
        return NULL;
    }

    nova->prim = NULL;

    return nova;
}

/* ^^ Aqui é a funcao que exclui a lista e libera memória alocada */
Lista *excluirLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada\n");
        return NULL;
    }

    ListaNo *aux;

    while (lista->prim != NULL)
    {
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        free(aux->pacote);
        free(aux);
    }

    free(lista);

    return NULL;
}

/* ^^ Aqui adiciona um pacote na lista */
int inserirPacote(Lista *lista, Pacote *pacote)
{
    ListaNo *novaNo = (ListaNo *)malloc(sizeof(ListaNo));

    if (novaNo == NULL)
    {
        printf("Sem espaco\n");
        return 0;
    }

    novaNo->pacote = (Pacote *)malloc(sizeof(Pacote));

    if (novaNo->pacote == NULL)
    {
        printf("Sem espaco\n");
        free(novaNo);
        return 0;
    }

    *(novaNo->pacote) = *pacote;
    novaNo->prox = NULL;

    if (lista->prim == NULL)
    {
        lista->prim = novaNo;
    }
    else
    {
        ListaNo *p = lista->prim;

        while (p->prox != NULL)
        {
            p = p->prox;
        }

        p->prox = novaNo;
    }

    return 1;
}

/* ^^ imprimir todos os pacotes da lista */
void imprimirPacotes(Lista *lista)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista esta vazia\n");
        return;
    }

    ListaNo *p;

    /* ^^ percorrer a lista e imprimir todos os dados dos pacotes */
    for (p = lista->prim; p != NULL; p = p->prox)
    {
        printf("ID: %d, Destino: %s, Preco: %.2f, Duracao: %d dias, Transporte: %c\n",
               p->pacote->id, p->pacote->destino, p->pacote->precoPacote,
               p->pacote->duracaoDias, p->pacote->tipoTransporte);
    }
}

/* ^^ remover um pacote da lista pelo id */
int removerPacote(Lista *lista, int id)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista nao foi criada ou esta vazia\n");
        return 0;
    }

    ListaNo *p = lista->prim;

    if (p->pacote->id == id)
    {
        lista->prim = p->prox;
        free(p->pacote);
        free(p);
        return 1;
    }

    /* ^^ Aqui vai percorrer a lista procurando o pacote que vai ser removido */
    while (p->prox != NULL)
    {
        if (p->prox->pacote->id == id)
        {
            ListaNo *aux = p->prox;
            p->prox = aux->prox;
            free(aux->pacote);
            free(aux);
            return 1;
        }

        p = p->prox;
    }

    return 0;
}

/* ^^ funcao par salvar a lista em um arquivo */
int salvarLista(Lista *lista)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista esta vazia ou nao foi criada\n");
        return 0;
    }

    FILE *arquivo = fopen("D:\\GitHub Desktop\\C_CodeLab\\pacoteViagens2\\pacotes.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    ListaNo *p;

    /* ^^ Aqui vai percorrer a lista e pegar os dados de cada pacote para colocar no arquivo */
    for (p = lista->prim; p != NULL; p = p->prox)
    {
        fprintf(arquivo, "%d;%s;%.2f;%d;%c\n",
                p->pacote->id, p->pacote->destino,
                p->pacote->precoPacote,
                p->pacote->duracaoDias,
                p->pacote->tipoTransporte);
    }

    fclose(arquivo);

    return 1;
}

/* ^^ carregar os pacotes de um arquivo para a lista */
int carregarLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada\n");
        return 0;
    }

    FILE *arquivo = fopen("D:\\GitHub Desktop\\C_CodeLab\\pacoteViagens2\\pacotes.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    Pacote *pacote;

    /* ^^ Aqui vai ler os dados do arquivo e colocar eles na lista */
    while ((pacote = (Pacote *)malloc(sizeof(Pacote))) != NULL &&
           fscanf(arquivo, "%d;%49[^;];%f;%d;%c\n",
                  &pacote->id, pacote->destino,
                  &pacote->precoPacote,
                  &pacote->duracaoDias,
                  &pacote->tipoTransporte) == 5)
    {

        inserirPacote(lista, pacote);
    }

    fclose(arquivo);

    return 1;
}