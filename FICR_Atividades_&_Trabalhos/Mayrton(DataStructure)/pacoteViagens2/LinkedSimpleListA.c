#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da estrutura do pacote de viagem
typedef struct Pacote
{
    int id;
    char destino[100];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
    struct Pacote *proximo;
} Pacote;

// Definicao da estrutura da lista
typedef struct
{
    Pacote *inicio;
} ListaPacotes;

// Protótipos das funcões
void criarLista(ListaPacotes *lista);
void inserirElemento(ListaPacotes *lista, Pacote *novoPacote);
void inserirElementoID(ListaPacotes *lista, Pacote *novoPacote, int posicao);
void inserirElementoInicio(ListaPacotes *lista, Pacote *novoPacote);
void listarElementos(ListaPacotes *lista);
void removerElemento(ListaPacotes *lista, int posicao);
void atualizar(ListaPacotes *lista, int id);
Pacote *buscarElemento(ListaPacotes *lista, int id);
int tamanho(ListaPacotes *lista);
void excluirLista(ListaPacotes *lista);
void carregarDados(ListaPacotes *lista);
void salvarDados(ListaPacotes *lista);

// Implementacao das funcões

void criarLista(ListaPacotes *lista)
{
    lista->inicio = NULL;
}

void inserirElemento(ListaPacotes *lista, Pacote *novoPacote)
{
    if (lista->inicio == NULL)
    {
        lista->inicio = novoPacote;
        novoPacote->proximo = NULL;
        return;
    }

    Pacote *atual = lista->inicio;
    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }
    atual->proximo = novoPacote;
    novoPacote->proximo = NULL;
}

void inserirElementoID(ListaPacotes *lista, Pacote *novoPacote, int posicao)
{
    if (posicao < 0)
    {
        printf("Posicao invalida!\n");
        return;
    }

    if (posicao == 0)
    {
        inserirElementoInicio(lista, novoPacote);
        return;
    }

    Pacote *atual = lista->inicio;
    int contador = 0;

    while (atual != NULL && contador < posicao - 1)
    {
        atual = atual->proximo;
        contador++;
    }

    if (atual == NULL)
    {
        printf("Posicao invalida!\n");
        return;
    }

    novoPacote->proximo = atual->proximo;
    atual->proximo = novoPacote;
}

void inserirElementoInicio(ListaPacotes *lista, Pacote *novoPacote)
{
    novoPacote->proximo = lista->inicio;
    lista->inicio = novoPacote;
}

void listarElementos(ListaPacotes *lista)
{
    Pacote *atual = lista->inicio;

    if (atual == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    while (atual != NULL)
    {
        printf("ID: %d\n", atual->id);
        printf("Destino: %s\n", atual->destino);
        printf("Preco do Pacote: R$ %.2f\n", atual->precoPacote);
        printf("Duracao (dias): %d\n", atual->duracaoDias);
        printf("Tipo de Transporte: %c\n", atual->tipoTransporte);
        printf("-------------------\n");
        atual = atual->proximo;
    }
}

void removerElemento(ListaPacotes *lista, int posicao)
{
    if (lista->inicio == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    Pacote *atual = lista->inicio;
    Pacote *anterior = NULL;
    int contador = 0;

    if (posicao == 0)
    {
        lista->inicio = atual->proximo;
        free(atual);
        return;
    }

    while (atual != NULL && contador < posicao)
    {
        anterior = atual;
        atual = atual->proximo;
        contador++;
    }

    if (atual == NULL)
    {
        printf("Posicao invalida!\n");
        return;
    }

    anterior->proximo = atual->proximo;
    free(atual);
}

void atualizar(ListaPacotes *lista, int id)
{
    Pacote *pacote = buscarElemento(lista, id);

    if (pacote == NULL)
    {
        printf("Pacote nao encontrado!\n");
        return;
    }

    printf("Digite o novo destino: ");
    scanf(" %[^\n]", pacote->destino);

    printf("Digite o novo preco do pacote: ");
    scanf("%f", &pacote->precoPacote);

    printf("Digite a nova duracao em dias: ");
    scanf("%d", &pacote->duracaoDias);

    printf("Digite o novo tipo de transporte (A/B): ");
    scanf(" %c", &pacote->tipoTransporte);
}

Pacote *buscarElemento(ListaPacotes *lista, int id)
{
    Pacote *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->id == id)
        {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

int tamanho(ListaPacotes *lista)
{
    int contador = 0;
    Pacote *atual = lista->inicio;

    while (atual != NULL)
    {
        contador++;
        atual = atual->proximo;
    }

    return contador;
}

void excluirLista(ListaPacotes *lista)
{
    Pacote *atual = lista->inicio;
    Pacote *proximo;

    while (atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->inicio = NULL;
}

void carregarDados(ListaPacotes *lista)
{
    FILE *arquivo = fopen("PACOTES.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo ou arquivo nao existe.\n");
        return;
    }

    excluirLista(lista); // Limpa a lista atual

    Pacote *novoPacote;
    while (!feof(arquivo))
    {
        novoPacote = malloc(sizeof(Pacote));
        if (fscanf(arquivo, "%d;%[^;];%f;%d;%c\n",
                   &novoPacote->id,
                   novoPacote->destino,
                   &novoPacote->precoPacote,
                   &novoPacote->duracaoDias,
                   &novoPacote->tipoTransporte) == 5)
        {
            inserirElemento(lista, novoPacote);
        }
        else
        {
            free(novoPacote);
            break;
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

void salvarDados(ListaPacotes *lista)
{
    FILE *arquivo = fopen("PACOTES.txt", "w"); // ta em letra maiuscula nao influencia o arquivo criado em output ser pacotes.txt em letra minuscula --> estudar o pq dps**

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Pacote *atual = lista->inicio;
    while (atual != NULL)
    {
        fprintf(arquivo, "%d;%s;%.2f;%d;%c\n",
                atual->id,
                atual->destino,
                atual->precoPacote,
                atual->duracaoDias,
                atual->tipoTransporte);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

int main()
{
    ListaPacotes lista;
    criarLista(&lista);

    int opcao, id, posicao;
    Pacote *novoPacote;

    do
    {
        printf("\n--- SISTEMA DE GERENCIAMENTO DE PACOTES DE VIAGEM ---\n");
        printf("1. Inserir Pacote no Final\n");
        printf("2. Inserir Pacote em Posicao Especifica\n");
        printf("3. Inserir Pacote no Inicio\n");
        printf("4. Listar Pacotes\n");
        printf("5. Remover Pacote\n");
        printf("6. Atualizar Pacote\n");
        printf("7. Buscar Pacote\n");
        printf("8. Mostrar Tamanho da Lista\n");
        printf("9. Excluir Lista\n");
        printf("10. Carregar Dados do Arquivo\n");
        printf("11. Salvar Dados no Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            novoPacote = malloc(sizeof(Pacote));
            printf("ID do Pacote: ");
            scanf("%d", &novoPacote->id);
            printf("Destino: ");
            scanf(" %[^\n]", novoPacote->destino);
            printf("Preco do Pacote: ");
            scanf("%f", &novoPacote->precoPacote);
            printf("Duracao (dias): ");
            scanf("%d", &novoPacote->duracaoDias);
            printf("Tipo de Transporte (A/B): ");
            scanf(" %c", &novoPacote->tipoTransporte);
            inserirElemento(&lista, novoPacote);
            break;

        case 2:
            novoPacote = malloc(sizeof(Pacote));
            printf("ID do Pacote: ");
            scanf("%d", &novoPacote->id);
            printf("Destino: ");
            scanf(" %[^\n]", novoPacote->destino);
            printf("Preco do Pacote: ");
            scanf("%f", &novoPacote->precoPacote);
            printf("Duracao (dias): ");
            scanf("%d", &novoPacote->duracaoDias);
            printf("Tipo de Transporte (A/B): ");
            scanf(" %c", &novoPacote->tipoTransporte);
            printf("Posicao para Insercao: ");
            scanf("%d", &posicao);
            inserirElementoID(&lista, novoPacote, posicao);
            break;

        case 3:
            novoPacote = malloc(sizeof(Pacote));
            printf("ID do Pacote: ");
            scanf("%d", &novoPacote->id);
            printf("Destino: ");
            scanf(" %[^\n]", novoPacote->destino);
            printf("Preco do Pacote: ");
            scanf("%f", &novoPacote->precoPacote);
            printf("Duracao (dias): ");
            scanf("%d", &novoPacote->duracaoDias);
            printf("Tipo de Transporte (A/B): ");
            scanf(" %c", &novoPacote->tipoTransporte);
            inserirElementoInicio(&lista, novoPacote);
            break;

        case 4:
            listarElementos(&lista);
            break;

        case 5:
            printf("Posicao do Pacote a Remover: ");
            scanf("%d", &posicao);
            removerElemento(&lista, posicao);
            break;

        case 6:
            printf("ID do Pacote a Atualizar: ");
            scanf("%d", &id);
            atualizar(&lista, id);
            break;

        case 7:
            printf("ID do Pacote a Buscar: ");
            scanf("%d", &id);
            Pacote *pacoteEncontrado = buscarElemento(&lista, id);
            if (pacoteEncontrado != NULL)
            {
                printf("Pacote Encontrado:\n");
                printf("ID: %d\n", pacoteEncontrado->id);
                printf("Destino: %s\n", pacoteEncontrado->destino);
                printf("Preco do Pacote: R$ %.2f\n", pacoteEncontrado->precoPacote);
                printf("Duracao (dias): %d\n", pacoteEncontrado->duracaoDias);
                printf("Tipo de Transporte: %c\n", pacoteEncontrado->tipoTransporte);
            }
            else
            {
                printf("Pacote nao encontrado!\n");
            }
            break;

        case 8:
            printf("Tamanho da Lista: %d\n", tamanho(&lista));
            break;

        case 9:
            excluirLista(&lista);
            printf("Lista excluida com sucesso!\n");
            break;

        case 10:
            carregarDados(&lista);
            break;

        case 11:
            salvarDados(&lista);
            break;

        case 0:
            printf("Encerrando o programa...\n");
            excluirLista(&lista);
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// OBS: Peço perdão pelos testes no txt nao serem valores e Lugares reais professor, tava só testando a funcionalidade msm