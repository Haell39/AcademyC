
/******************************************************************
 * Nome: Lista com vetores                                        *
 * Descricao: Implementacao de lista com uso de vetores (array).  *
 *            Esse codigo possui as principais operacoes da       *
 *            lista, como:                                        *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Mayrton Dias                                            *
 * Ultima alteracao: 18/09/2024                                   *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5 // Define o tamanho

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
        return 1; // Retorna erro se a lista não for criada OBS: retorno diferente de 0 geralmente sinaliza uma falha.
    }

    /* Carregar dados do arquivo */
    printf("Carregando dados do arquivo...\n");
    carregarDados(lista);

    printf("Dados carregados:\n");
    imprimirElementos(lista); // Verifique se está imprimindo algo

    /* Inserção dos pacotes de viagem */
    printf("Inserindo pacotes...\n");
    Pacote p1 = {1, "Paris", 3500.00, 7, 'A'};
    Pacote p2 = {2, "Rio_de_Janeiro", 1500.00, 5, 'B'};
    Pacote p3 = {3, "Londres", 2000.00, 3, 'A'};
    Pacote p4 = {4, "Amsterda", 2500.00, 4, 'B'};
    Pacote p5 = {5, "Barcelona", 3000.00, 6, 'A'};

    // É aq onde o usuario vai fazer as açoes: inserir, atualizar, remover, ... os pacotes

    inserirElemento(lista, p1);
    inserirElemento(lista, p2);
    inserirElemento(lista, p3);
    inserirElemento(lista, p4);
    inserirElemento(lista, p5);

    buscarElemento(lista, 2);

    printf("Imprimindo elementos após inserção:\n");
    imprimirElementos(lista);

    removerElemento(lista, 1); // Exemplo de remoção de um pacote
    removerElemento(lista, 5);
    printf("Imprimindo elementos após remoção:\n");
    imprimirElementos(lista);

    /* Atualizar um pacote */
    printf("Atualizando pacote com ID 2 (Rio_de_Janeiro)...\n");
    Pacote p_atualizado = {2, "Rio_de_Janeiro", 1800.00, 6, 'A'};
    atualizarElemento(lista, 2, p_atualizado);

    printf("Imprimindo elementos após atualização:\n");
    imprimirElementos(lista);

    /* Salvar dados no arquivo txt */
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
    Lista *nova = (Lista *)malloc(sizeof(Lista)); // Aloca memória para a nova lista
    if (nova == NULL)
    {
        printf("Erro ao criar a lista.\n");
        return NULL; // Vai retorna NULL se não conseguir alocar memória
    }

    nova->tamanho = 0;                                        // inicializa o tamanho da lista como 0
    nova->elementos = (Pacote *)malloc(TAM * sizeof(Pacote)); // aloca memória para os pacotes
    if (nova->elementos == NULL)                              //
    {
        printf("Erro ao alocar memória para elementos.\n");
        free(nova);  // Libera memória já alocada para a lista
        return NULL; // denovo vai retorna NULL se não conseguir alocar memória
    }
    return nova;
}

/* Função para excluir a lista */
Lista *excluirLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("A lista não foi criada.\n");
        return NULL; // Retorna NULL se a lista não existe
    }
    free(lista->elementos); // Libera memória dos elementos da lista
    free(lista);            // Libera memória da lista (da propria lista)
    return NULL;            // Aqui retorna NULL, mas é pelo fato de indicar que a lista foi excluída, ou pelo menos é oq eu entendi(anotações caderno)
}

/* Função para imprimir os pacotes */
void imprimirElementos(Lista *lista)
{
    if (lista == NULL || lista->tamanho == 0)
    {
        printf("Lista vazia ou não criada.\n"); // Mensagem se a lista estiver vazia ou não existir
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
        return 0; // se lista nao existe
    }

    if (lista->tamanho >= TAM)
    {
        // Aqui é a melhor parte e onde mais deu erro pra mim, aqui é onde aumenta a capacidade da lista se necessário usando realloc
        lista->elementos = realloc(lista->elementos, (lista->tamanho + TAM) * sizeof(Pacote));
        if (lista->elementos == NULL)
        {
            printf("Erro ao alocar mais memória para elementos.\n");
            return 0; // Retorna 0 se falhar ao aumentar a capacidade
        }
    }
    // acredito com base nas minhas anotações aq eu poderia atualizar o ponteiro: lista->elementos = temp; mas em time que ta ganhando nao se mexe, se rodou rodou
    lista->elementos[lista->tamanho] = pacote;
    lista->tamanho++;
    return 1; // O retorno 1 indica que a remoção foi bem-sucedida, diferente de como foi utilizado anteriormente no inicio do codigo
}

/* Função para remover um pacote */
int removerElemento(Lista *lista, int id)
{
    if (lista == NULL)
    {
        printf("A lista não foi criada.\n");
        return 0; // 0 se nao existe
    }

    for (int i = 0; i < lista->tamanho; ++i)
    {
        if (lista->elementos[i].id == id)
        {
            for (int j = i; j < lista->tamanho - 1; ++j)
            {
                // Move os pacotes subsequentes uma posição para frente
                lista->elementos[j] = lista->elementos[j + 1];
            }
            lista->tamanho--; // Decrementa o tamanho da lista após remoção
            return 1;         // Retorna 1 indicando que o pacote foi removido com sucesso
        }
    }

    printf("Elemento não encontrado.\n");
    return 0;
}

/* Função para carregar dados do arquivo */
void carregarDados(Lista *lista)
{
    FILE *file = fopen("D:\\GitHub Desktop\\C_CodeLab\\College\\ListaVetor\\BancoDados.txt", "r"); // deve se usar \\ pois o C vai interpretar como se fosse 1 barra "\", pois uma só barra é usada para "\n"
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Pacote p;
    while (fscanf(file, "%d %49s %f %d %c", &p.id, p.destino, &p.precoPacote, // OBS: %49s: Lê uma string (até 49 caracteres) e a armazena em p.destino. O limite de 49 garante que não ocorra overflow no buffer.
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
        return -1; // Isso é uma forma de indicar que houve um erro ao tentar buscar um elemento.
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