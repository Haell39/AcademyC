#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da estrutura do pacote de viagem
typedef struct Pacote
{
    int id;
    char destino[100]; // Aumentei o tamanho para acomodar nomes mais longos
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
    struct Pacote *proximo;
} Pacote;

// Variaveis globais
Pacote *lista = NULL;
int ultimoId = 0;

// Protótipos das funcões
Pacote *criarLista();
void inserirElemento(Pacote **lista, int id, char *destino, float preco, int duracao, char transporte);
void inserirElementoID(Pacote **lista, int posicao, int id, char *destino, float preco, int duracao, char transporte);
void inserirElementoInicio(Pacote **lista, int id, char *destino, float preco, int duracao, char transporte);
void listarElementos(Pacote *lista);
void removerElemento(Pacote **lista, int posicao);
void atualizar(Pacote *lista, int id);
Pacote *buscarElemento(Pacote *lista, int id);
int tamanho(Pacote *lista);
void excluirLista(Pacote **lista);
void salvarDados(Pacote *lista);
void carregarDados();

// Funcao para criar lista vazia
Pacote *criarLista()
{
    return NULL;
}

// Funcao para inserir elemento no final da lista
void inserirElemento(Pacote **lista, int id, char *destino, float preco, int duracao, char transporte)
{
    Pacote *novoPacote = (Pacote *)malloc(sizeof(Pacote));

    novoPacote->id = id;
    strcpy(novoPacote->destino, destino);
    novoPacote->precoPacote = preco;
    novoPacote->duracaoDias = duracao;
    novoPacote->tipoTransporte = transporte;

    if (*lista == NULL)
    {
        *lista = novoPacote;
        novoPacote->proximo = *lista;
    }
    else
    {
        Pacote *atual = *lista;
        while (atual->proximo != *lista)
        {
            atual = atual->proximo;
        }
        atual->proximo = novoPacote;
        novoPacote->proximo = *lista;
    }
}

// Funcao para inserir elemento em uma posicao especIfica
void inserirElementoID(Pacote **lista, int posicao, int id, char *destino, float preco, int duracao, char transporte)
{
    if (posicao < 0)
        return;

    Pacote *novoPacote = (Pacote *)malloc(sizeof(Pacote));
    novoPacote->id = id;
    strcpy(novoPacote->destino, destino);
    novoPacote->precoPacote = preco;
    novoPacote->duracaoDias = duracao;
    novoPacote->tipoTransporte = transporte;

    if (*lista == NULL)
    {
        *lista = novoPacote;
        novoPacote->proximo = *lista;
        return;
    }

    Pacote *atual = *lista;
    int count = 0;

    do
    {
        if (count == posicao - 1)
        {
            novoPacote->proximo = atual->proximo;
            atual->proximo = novoPacote;
            return;
        }
        atual = atual->proximo;
        count++;
    } while (atual != *lista);
}

// Funcao para inserir elemento no inIcio da lista deu treta aqui, mas ajeitei
void inserirElementoInicio(Pacote **lista, int id, char *destino, float preco, int duracao, char transporte)
{
    Pacote *novoPacote = (Pacote *)malloc(sizeof(Pacote));

    novoPacote->id = id;
    strcpy(novoPacote->destino, destino);
    novoPacote->precoPacote = preco;
    novoPacote->duracaoDias = duracao;
    novoPacote->tipoTransporte = transporte;

    if (*lista == NULL)
    {
        *lista = novoPacote;
        novoPacote->proximo = *lista;
    }
    else
    {
        Pacote *atual = *lista;
        while (atual->proximo != *lista)
        {
            atual = atual->proximo;
        }
        novoPacote->proximo = *lista;
        atual->proximo = novoPacote;
        *lista = novoPacote;
    }
}

// Funcao para listar elementos
void listarElementos(Pacote *lista)
{
    if (lista == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    Pacote *atual = lista;
    do
    {
        printf("ID: %d\n", atual->id);
        printf("Destino: %s\n", atual->destino);
        printf("Preco do Pacote: R$ %.2f\n", atual->precoPacote);
        printf("Duracao (dias): %d\n", atual->duracaoDias);
        printf("Tipo Transporte: %c\n", atual->tipoTransporte);
        printf("------------------------\n");
        atual = atual->proximo;
    } while (atual != lista);
}

// Funcao para remover elemento por posicao infernal essa aqui, me compliquei muito
void removerElemento(Pacote **lista, int posicao)
{
    if (*lista == NULL)
        return;

    Pacote *atual = *lista;
    Pacote *anterior = NULL;
    int count = 0;

    do
    {
        if (count == posicao)
        {
            if (anterior == NULL)
            {
                if (atual->proximo == *lista)
                {
                    *lista = NULL;
                }
                else
                {
                    Pacote *temp = *lista;
                    while (temp->proximo != *lista)
                    {
                        temp = temp->proximo;
                    }
                    temp->proximo = atual->proximo;
                    *lista = atual->proximo;
                }
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
        count++;
    } while (atual != *lista);
}

// Funcao para atualizar dados de um elemento
void atualizar(Pacote *lista, int id)
{
    Pacote *pacote = buscarElemento(lista, id);
    if (pacote == NULL)
    {
        printf("Pacote nao encontrado.\n");
        return;
    }

    printf("Atualizando pacote %d\n", id);
    printf("Novo destino: ");
    scanf(" %[^\n]", pacote->destino);
    printf("Novo preco: ");
    scanf("%f", &pacote->precoPacote);
    printf("Nova duracao (dias): ");
    scanf("%d", &pacote->duracaoDias);
    printf("Novo tipo de transporte (A/B): ");
    scanf(" %c", &pacote->tipoTransporte);
}

// Funcao para buscar elemento por ID (outra bem dificil)
Pacote *buscarElemento(Pacote *lista, int id)
{
    if (lista == NULL)
        return NULL;

    Pacote *atual = lista;
    do
    {
        if (atual->id == id)
        {
            return atual;
        }
        atual = atual->proximo;
    } while (atual != lista);

    return NULL;
}

// Funcao para contar elementos da lista
int tamanho(Pacote *lista)
{
    if (lista == NULL)
        return 0;

    int count = 0;
    Pacote *atual = lista;
    do
    {
        count++;
        atual = atual->proximo;
    } while (atual != lista);

    return count;
}

// Funcao para excluir toda a lista
void excluirLista(Pacote **lista)
{
    if (*lista == NULL)
        return;

    Pacote *atual = *lista;
    Pacote *proximo;

    do
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    } while (atual != *lista);

    *lista = NULL;
}

// Funcao para salvar dados no arquivo
void salvarDados(Pacote *lista)
{
    FILE *arquivo = fopen("pacotes.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (lista == NULL)
    {
        fclose(arquivo);
        return;
    }

    Pacote *atual = lista;
    do
    {
        fprintf(arquivo, "%d;%s;%.2f;%d;%c\n",
                atual->id, atual->destino, atual->precoPacote,
                atual->duracaoDias, atual->tipoTransporte);
        atual = atual->proximo;
    } while (atual != lista);

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

// Funcao para carregar dados do arquivo
void carregarDados()
{
    FILE *arquivo = fopen("pacotes.txt", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    excluirLista(&lista); // Limpa lista atual

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo))
    {
        int id, duracaoDias;
        char destino[50], tipoTransporte;
        float precoPacote;

        sscanf(linha, "%d;%[^;];%f;%d;%c",
               &id, destino, &precoPacote, &duracaoDias, &tipoTransporte);

        inserirElemento(&lista, id, destino, precoPacote, duracaoDias, tipoTransporte);
        if (id > ultimoId)
            ultimoId = id;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void entrarDestino(char *destino, int tamanho)
{
    limparBuffer(); // Limpa buffer antes de ler
    printf("Destino: ");
    fgets(destino, tamanho, stdin);

    // Remove o caractere de nova linha, se presente(pesquisei pra saber)
    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n')
    {
        destino[len - 1] = '\0';
    }
}

// Funcao principal com menu interativo
int main()
{
    int opcao, id, posicao, duracaoDias;
    char destino[100]; // Aumentei o tamanho(lembrar**)
    char tipoTransporte;
    float precoPacote;

    while (1)
    {
        printf("\n--- SISTEMA DE PACOTES DE VIAGEM ---\n");
        printf("1. Criar Lista\n");
        printf("2. Inserir Elemento no Final\n");
        printf("3. Inserir Elemento em Posicao\n");
        printf("4. Inserir Elemento no InIcio\n");
        printf("5. Listar Elementos\n");
        printf("6. Remover Elemento\n");
        printf("7. Atualizar Elemento\n");
        printf("8. Buscar Elemento\n");
        printf("9. Tamanho da Lista\n");
        printf("10. Excluir Lista\n");
        printf("11. Salvar Dados\n");
        printf("12. Carregar Dados\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            printf("Saindo do programa...\n");
            return 0;

        case 1:
            lista = criarLista();
            printf("Lista criada.\n");
            break;

        case 2:
            ultimoId++;
            entrarDestino(destino, sizeof(destino));

            printf("Preco do Pacote: ");
            scanf("%f", &precoPacote);

            printf("Duracao (dias): ");
            scanf("%d", &duracaoDias);

            printf("Tipo Transporte (A/B): ");
            scanf(" %c", &tipoTransporte);

            inserirElemento(&lista, ultimoId, destino, precoPacote, duracaoDias, tipoTransporte);
            break;

        case 3:
            ultimoId++;
            printf("Posicao para inserir: ");
            scanf("%d", &posicao);

            entrarDestino(destino, sizeof(destino));

            printf("Preco do Pacote: ");
            scanf("%f", &precoPacote);

            printf("Duracao (dias): ");
            scanf("%d", &duracaoDias);

            printf("Tipo Transporte (A/B): ");
            scanf(" %c", &tipoTransporte);

            inserirElementoID(&lista, posicao, ultimoId, destino, precoPacote, duracaoDias, tipoTransporte);
            break;

        case 4:
            ultimoId++;
            entrarDestino(destino, sizeof(destino));

            printf("Preco do Pacote: ");
            scanf("%f", &precoPacote);

            printf("Duracao (dias): ");
            scanf("%d", &duracaoDias);

            printf("Tipo Transporte (A/B): ");
            scanf(" %c", &tipoTransporte);

            inserirElementoInicio(&lista, ultimoId, destino, precoPacote, duracaoDias, tipoTransporte);
            break;

        case 5:
            listarElementos(lista);
            break;

        case 6:
            printf("Posicao para remover: ");
            scanf("%d", &posicao);
            removerElemento(&lista, posicao);
            break;

        case 7: // Atualizar elemento
            printf("ID do pacote a atualizar: ");
            scanf("%d", &id);

            Pacote *pacoteAtualizar = buscarElemento(lista, id);
            if (pacoteAtualizar)
            {
                printf("Atualizando pacote %d\n", id);

                entrarDestino(pacoteAtualizar->destino, sizeof(pacoteAtualizar->destino));

                printf("Novo preco: ");
                scanf("%f", &pacoteAtualizar->precoPacote);

                printf("Nova duracao (dias): ");
                scanf("%d", &pacoteAtualizar->duracaoDias);

                printf("Novo tipo de transporte (A/B): ");
                scanf(" %c", &pacoteAtualizar->tipoTransporte);
            }
            else
            {
                printf("Pacote nao encontrado.\n");
            }
            break;

        case 8:
            printf("ID do pacote a buscar: ");
            scanf("%d", &id);
            Pacote *pacoteEncontrado = buscarElemento(lista, id);
            if (pacoteEncontrado)
            {
                printf("Pacote encontrado:\n");
                printf("ID: %d\n", pacoteEncontrado->id);
                printf("Destino: %s\n", pacoteEncontrado->destino);
                printf("Preco: R$ %.2f\n", pacoteEncontrado->precoPacote);
            }
            else
            {
                printf("Pacote nao encontrado.\n");
            }
            break;

        case 9:
            printf("Tamanho da lista: %d\n", tamanho(lista));
            break;

        case 10:
            excluirLista(&lista);
            printf("Lista excluIda.\n");
            break;

        case 11:
            salvarDados(lista);
            break;

        case 12:
            carregarDados();
            break;

        default:
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}