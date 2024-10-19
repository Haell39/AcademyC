#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

/* Definição da estrutura para Pacote de Viagem */
typedef struct
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
} Pacote;

/* Definição da estrutura da Lista */
typedef struct
{
    int tamanho;       // Quantidade de pacotes na lista
    Pacote *elementos; // Vetor de Pacotes
} Lista;

/* Funções implementadas */
int atualizarElemento(Lista *, int, Pacote);
int buscarElemento(Lista *, int);
Lista *criarLista();
Lista *excluirLista(Lista *);
void imprimirElementos(Lista *);
int inserirElemento(Lista *, Pacote);
int removerElemento(Lista *, int);
void carregarDados(Lista *);
void salvarDados(Lista *);

/* Função principal */
int main()
{
    Lista *lista = criarLista();
    if (lista == NULL)
    {
        printf("Erro ao criar a lista.\n");
        return 1; // Retorna erro se a lista não for criada
    }

    /* Carregar dados do arquivo */
    printf("Carregando dados do arquivo...\n");
    carregarDados(lista);

    printf("Dados carregados:\n");
    imprimirElementos(lista); // Verifique se está imprimindo algo

    /* Exemplo de inserção de pacotes de viagem */
    printf("Inserindo pacotes...\n");
    Pacote p1 = {1, "Paris", 3500.00, 7, 'A'};
    Pacote p2 = {2, "Rio_de_Janeiro", 1500.00, 5, 'B'};
    Pacote p3 = {3, "Londres", 2000.00, 3, 'A'};
    Pacote p4 = {4, "Amsterda", 2500.00, 4, 'B'};
    Pacote p5 = {5, "Barcelona", 3000.00, 6, 'A'};

    inserirElemento(lista, p1);
    inserirElemento(lista, p2);
    inserirElemento(lista, p3);
    inserirElemento(lista, p4);
    inserirElemento(lista, p5);

    printf("Imprimindo elementos após inserção:\n");
    imprimirElementos(lista);

    removerElemento(lista, 1);
    removerElemento(lista, 5);
    printf("Imprimindo elementos após remoção:\n");
    imprimirElementos(lista);

    /* Atualizar um elemento */
    printf("Atualizando pacote com ID 2 (Rio_de_Janeiro)...\n");
    Pacote p_atualizado = {2, "Rio_de_Janeiro", 1800.00, 6, 'A'};
    atualizarElemento(lista, 2, p_atualizado);

    printf("Imprimindo elementos após atualização:\n");
    imprimirElementos(lista);

    /* Salvar dados no arquivo */
    printf("Salvando dados no arquivo...\n");
    salvarDados(lista);

    lista = excluirLista(lista);
    if (lista == NULL)
    {
        printf("Lista excluída com sucesso.\n");
    }

    return 0;
}

/* Função que cria a lista */
Lista *criarLista()
{
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    if (nova == NULL)
    {
        printf("Erro ao criar a lista.\n");
        return NULL;
    }

    nova->tamanho = 0;
    nova->elementos = (Pacote *)malloc(TAM * sizeof(Pacote));
    if (nova->elementos == NULL)
    {
        printf("Erro ao alocar memória para elementos.\n");
        free(nova);
        return NULL;
    }
    return nova;
}

/* Função para excluir a lista */
Lista *excluirLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("A lista não foi criada.\n");
        return NULL;
    }
    free(lista->elementos);
    free(lista);
    return NULL;
}

/* Função para imprimir os pacotes */
void imprimirElementos(Lista *lista)
{
    if (lista == NULL || lista->tamanho == 0)
    {
        printf("Lista vazia ou não criada.\n");
        return;
    }
    for (int i = 0; i < lista->tamanho; ++i)
    {
        Pacote p = lista->elementos[i];
        printf("ID: %d, Destino: %s, Preço: %.2f, Duração: %d dias, Transporte: %c\n",
               p.id, p.destino, p.precoPacote, p.duracaoDias, p.tipoTransporte);
    }
}

/* Função para inserir um pacote */
int inserirElemento(Lista *lista, Pacote pacote)
{
    if (lista == NULL)
    {
        printf("A lista não foi criada.\n");
        return 0;
    }

    if (lista->tamanho >= TAM)
    {
        lista->elementos = realloc(lista->elementos, (lista->tamanho + TAM) * sizeof(Pacote));
        if (lista->elementos == NULL)
        {
            printf("Erro ao alocar mais memória para elementos.\n");
            return 0;
        }
    }
    lista->elementos[lista->tamanho] = pacote;
    lista->tamanho++;
    return 1;
}

/* Função para remover um pacote */
int removerElemento(Lista *lista, int id)
{
    if (lista == NULL)
    {
        printf("A lista não foi criada.\n");
        return 0;
    }

    for (int i = 0; i < lista->tamanho; ++i)
    {
        if (lista->elementos[i].id == id)
        {
            for (int j = i; j < lista->tamanho - 1; ++j)
            {
                lista->elementos[j] = lista->elementos[j + 1];
            }
            lista->tamanho--;
            return 1;
        }
    }

    printf("Elemento não encontrado.\n");
    return 0;
}

/* Função para carregar dados do arquivo */
void carregarDados(Lista *lista)
{
    FILE *file = fopen("D:\\GitHub Desktop\\C_CodeLab\\College\\ListaVetor\\BancoDados.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Pacote p;
    while (fscanf(file, "%d %49s %f %d %c", &p.id, p.destino, &p.precoPacote,
                  &p.duracaoDias, &p.tipoTransporte) != EOF)
    {
        inserirElemento(lista, p);
    }
    fclose(file);
}

/* Função para salvar dados no arquivo */
void salvarDados(Lista *lista)
{
    FILE *file = fopen("D:\\GitHub Desktop\\C_CodeLab\\College\\ListaVetor\\BancoDados.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao salvar arquivo.\n");
        return;
    }

    for (int i = 0; i < lista->tamanho; ++i)
    {
        Pacote p = lista->elementos[i];
        fprintf(file, "%d %s %.2f %d %c\n", p.id, p.destino, p.precoPacote, p.duracaoDias, p.tipoTransporte);
    }
    fclose(file);
}

/* Função para buscar um elemento por ID */
int buscarElemento(Lista *lista, int id)
{
    if (lista == NULL)
    {
        printf("A lista não foi criada.\n");
        return -1;
    }

    for (int i = 0; i < lista->tamanho; ++i)
    {
        if (lista->elementos[i].id == id)
        {
            return i; // Retorna o índice do pacote encontrado
        }
    }

    printf("Elemento não encontrado.\n");
    return -1;
}

/* Função para atualizar um pacote */
int atualizarElemento(Lista *lista, int id, Pacote pacoteAtualizado)
{
    int index = buscarElemento(lista, id);
    if (index == -1)
    {
        printf("Erro: Elemento com ID %d não encontrado.\n", id);
        return 0;
    }

    lista->elementos[index] = pacoteAtualizado; // Atualiza o pacote no índice encontrado
    return 1;
}
