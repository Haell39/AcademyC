#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da estrutura do pacote
typedef struct Pacote
{
    int id;
    char destino[100];
    float preco;
    int dias;
    char tipoTransporte[20];
    struct Pacote *proximo;
} Pacote;

// Protótipos das funcões
Pacote *criarLista();
void inserirInicio(Pacote **lista);
void inserirFinal(Pacote **lista);
void mostrarLista(Pacote *lista);
void buscarPacote(Pacote *lista);
void atualizar(Pacote **lista);
void excluirPacote(Pacote **lista);
void excluirLista(Pacote **lista);
int tamanho(Pacote *lista);
void carregarDados(Pacote **lista);
void salvarDados(Pacote *lista);

// Funcao para criar lista vazia
Pacote *criarLista()
{
    return NULL;
}

// Funcao para inserir no inicio da lista
void inserirInicio(Pacote **lista)
{
    Pacote *novoPacote = (Pacote *)malloc(sizeof(Pacote));
    char buffer[100]; // Buffer temporario para entrada

    printf("Digite o ID do pacote: ");
    scanf("%d", &novoPacote->id);
    getchar(); // Limpa o buffer de entrada

    printf("Digite o destino: ");
    fgets(novoPacote->destino, sizeof(novoPacote->destino), stdin);
    novoPacote->destino[strcspn(novoPacote->destino, "\n")] = 0; // Remove newline

    printf("Digite o preco: ");
    scanf("%f", &novoPacote->preco);
    getchar(); // Limpa o buffer de entrada

    printf("Digite a quantidade de dias: ");
    scanf("%d", &novoPacote->dias);
    getchar(); // Limpa o buffer de entrada

    printf("Tipo de transporte (ex: Aviao, Ônibus, Cruzeiro): ");
    fgets(novoPacote->tipoTransporte, sizeof(novoPacote->tipoTransporte), stdin);
    novoPacote->tipoTransporte[strcspn(novoPacote->tipoTransporte, "\n")] = 0; // Remove newline

    novoPacote->proximo = *lista;
    *lista = novoPacote;

    printf("Pacote inserido no inicio com sucesso!\n");
}

// Funcao para inserir no final da lista (semelhante a inserirInicio)
void inserirFinal(Pacote **lista)
{
    Pacote *novoPacote = (Pacote *)malloc(sizeof(Pacote));

    printf("Digite o ID do pacote: ");
    scanf("%d", &novoPacote->id);
    getchar(); // Limpa o buffer de entrada

    printf("Digite o destino: ");
    fgets(novoPacote->destino, sizeof(novoPacote->destino), stdin);
    novoPacote->destino[strcspn(novoPacote->destino, "\n")] = 0; // Remove newline

    printf("Digite o preco: ");
    scanf("%f", &novoPacote->preco);
    getchar(); // Limpa o buffer de entrada

    printf("Digite a quantidade de dias: ");
    scanf("%d", &novoPacote->dias);
    getchar(); // Limpa o buffer de entrada

    printf("Tipo de transporte (ex: Aviao, Ônibus, Cruzeiro): ");
    fgets(novoPacote->tipoTransporte, sizeof(novoPacote->tipoTransporte), stdin);
    novoPacote->tipoTransporte[strcspn(novoPacote->tipoTransporte, "\n")] = 0; // Remove newline

    novoPacote->proximo = NULL;

    // Se a lista estiver vazia
    if (*lista == NULL)
    {
        *lista = novoPacote;
        printf("Pacote inserido no final com sucesso!\n");
        return;
    }

    // Percorre até o último nó
    Pacote *atual = *lista;
    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }

    atual->proximo = novoPacote;
    printf("Pacote inserido no final com sucesso!\n");
}

// Funcao para mostrar a lista (atualizada para novo tipo de transporte)
void mostrarLista(Pacote *lista)
{
    if (lista == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    Pacote *atual = lista;
    int contador = 1;

    printf("--- Lista de Pacotes ---\n");
    while (atual != NULL)
    {
        printf("Pacote %d:\n", contador);
        printf("ID: %d\n", atual->id);
        printf("Destino: %s\n", atual->destino);
        printf("Preco: %.2f\n", atual->preco);
        printf("Dias: %d\n", atual->dias);
        printf("Tipo de Transporte: %s\n\n", atual->tipoTransporte);

        atual = atual->proximo;
        contador++;
    }
}

// Funcao para buscar pacote (renomeada)
void buscarPacoteA(Pacote *lista)
{
    if (lista == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    int idBusca;
    printf("Digite o ID do pacote a buscar: ");
    scanf("%d", &idBusca);

    Pacote *atual = lista;
    int encontrado = 0;

    while (atual != NULL)
    {
        if (atual->id == idBusca)
        {
            printf("Pacote encontrado:\n");
            printf("ID: %d\n", atual->id);
            printf("Destino: %s\n", atual->destino);
            printf("Preco: %.2f\n", atual->preco);
            printf("Dias: %d\n", atual->dias);
            printf("Tipo de Transporte: %s\n\n", atual->tipoTransporte);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Pacote nao encontrado!\n");
    }
}

// Funcao para atualizar pacote (atualizada)
void atualizar(Pacote **lista)
{
    if (*lista == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    int idBusca;
    printf("Digite o ID do pacote a atualizar: ");
    scanf("%d", &idBusca);
    getchar(); // Limpa o buffer de entrada

    Pacote *atual = *lista;
    int encontrado = 0;

    while (atual != NULL)
    {
        if (atual->id == idBusca)
        {
            printf("Pacote encontrado. Digite os novos dados:\n");

            printf("Novo destino (atual: %s): ", atual->destino);
            fgets(atual->destino, sizeof(atual->destino), stdin);
            atual->destino[strcspn(atual->destino, "\n")] = 0;

            printf("Novo preco (atual: %.2f): ", atual->preco);
            scanf("%f", &atual->preco);
            getchar(); // Limpa o buffer de entrada

            printf("Nova quantidade de dias (atual: %d): ", atual->dias);
            scanf("%d", &atual->dias);
            getchar(); // Limpa o buffer de entrada

            printf("Novo tipo de transporte (atual: %s): ", atual->tipoTransporte);
            fgets(atual->tipoTransporte, sizeof(atual->tipoTransporte), stdin);
            atual->tipoTransporte[strcspn(atual->tipoTransporte, "\n")] = 0;

            printf("Pacote atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Pacote nao encontrado!\n");
    }
}

// Funcao para salvar dados no arquivo (atualizada)
void salvarDados(Pacote *lista)
{
    FILE *arquivo = fopen("pacotes.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    Pacote *atual = lista;
    while (atual != NULL)
    {
        fprintf(arquivo, "%d; %s; %.2f; %d; %s\n",
                atual->id,
                atual->destino,
                atual->preco,
                atual->dias,
                atual->tipoTransporte);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

// Funcao para carregar dados de um arquivo (atualizada)
void carregarDados(Pacote **lista)
{
    FILE *arquivo = fopen("pacotes.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo ou arquivo nao existe.\n");
        return;
    }

    // Limpar lista existente antes de carregar
    excluirLista(lista);

    Pacote *novoPacote;
    while (!feof(arquivo))
    {
        novoPacote = (Pacote *)malloc(sizeof(Pacote));

        if (fscanf(arquivo, " %d; %[^;]; %f; %d; %[^\n]\n",
                   &novoPacote->id,
                   novoPacote->destino,
                   &novoPacote->preco,
                   &novoPacote->dias,
                   novoPacote->tipoTransporte) != 5)
        {
            free(novoPacote);
            break;
        }

        novoPacote->proximo = *lista;
        *lista = novoPacote;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

// Funcao para excluir pacote especifico
void excluirPacote(Pacote **lista)
{
    if (*lista == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    int idBusca;
    printf("Digite o ID do pacote a excluir: ");
    scanf("%d", &idBusca);

    Pacote *atual = *lista;
    Pacote *anterior = NULL;
    int encontrado = 0;

    while (atual != NULL)
    {
        if (atual->id == idBusca)
        {
            if (anterior == NULL)
            {
                // Pacote a ser removido é o primeiro
                *lista = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("Pacote excluido com sucesso!\n");
            encontrado = 1;
            break;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Pacote nao encontrado!\n");
    }
}

// Funcao para excluir toda a lista
void excluirLista(Pacote **lista)
{
    if (*lista == NULL)
    {
        printf("Lista ja esta vazia!\n");
        return;
    }

    Pacote *atual = *lista;
    Pacote *proximo;

    while (atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    *lista = NULL;
    printf("Lista excluida com sucesso!\n");
}

// Funcao para retornar o tamanho da lista
int tamanho(Pacote *lista)
{
    int contador = 0;
    Pacote *atual = lista;

    while (atual != NULL)
    {
        contador++;
        atual = atual->proximo;
    }

    return contador;
}

// Funcao principal
int main()
{
    Pacote *lista = criarLista();
    int opcao;

    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Inserir no Inicio\n");
        printf("2. Inserir no Final\n");
        printf("3. Mostrar Lista\n");
        printf("4. Buscar Pacote\n");
        printf("5. Atualizar Pacote\n");
        printf("6. Excluir Pacote\n");
        printf("7. Excluir Toda a Lista\n");
        printf("8. Mostrar Tamanho da Lista\n");
        printf("9. Carregar Dados do Arquivo\n");
        printf("10. Salvar Dados no Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserirInicio(&lista);
            break;
        case 2:
            inserirFinal(&lista);
            break;
        case 3:
            mostrarLista(lista);
            break;
        case 4:
            buscarPacoteA(lista);
            break;
        case 5:
            atualizar(&lista);
            break;
        case 6:
            excluirPacote(&lista);
            break;
        case 7:
            excluirLista(&lista);
            break;
        case 8:
            printf("Tamanho da lista: %d\n", tamanho(lista));
            break;
        case 9:
            carregarDados(&lista);
            break;
        case 10:
            salvarDados(lista);
            break;
        case 0:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    // Liberar memória antes de sair
    excluirLista(&lista);

    return 0;
}
