#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTOS 100
#define MAX_DESTINO 100

// Estrutura do pacote de viagem
typedef struct
{
    int id;
    char destino[MAX_DESTINO];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
} Pacote;

// Estrutura da Lista
typedef struct
{
    Pacote elementos[MAX_ELEMENTOS];
    int tamanhoAtual;
} ListaPacotes;

// Protótipo das funcões
void inicializarLista(ListaPacotes *lista);
int inserirElemento(ListaPacotes *lista, Pacote novoPacote);
int inserirElementoInicio(ListaPacotes *lista, Pacote novoPacote);
int inserirElementoID(ListaPacotes *lista, Pacote novoPacote, int posicao);
void listarElementos(ListaPacotes *lista);
int removerElemento(ListaPacotes *lista, int posicao);
Pacote *buscarElemento(ListaPacotes *lista, int id);
void atualizarElemento(ListaPacotes *lista, int id);
void salvarDados(ListaPacotes *lista);
void carregarDados(ListaPacotes *lista);
void limparBuffer();
void entrarDestino(char *destino, int tamanho);

// Funcao para limpar buffer de entrada
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Funcao para entrada de destino com fgets
void entrarDestino(char *destino, int tamanho)
{
    limparBuffer();
    printf("Destino: ");
    fgets(destino, tamanho, stdin);

    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n')
    {
        destino[len - 1] = '\0';
    }
}

// Inicializa a lista
void inicializarLista(ListaPacotes *lista)
{
    lista->tamanhoAtual = 0;
}

// Inserir elemento no final da lista
int inserirElemento(ListaPacotes *lista, Pacote novoPacote)
{
    if (lista->tamanhoAtual >= MAX_ELEMENTOS)
    {
        printf("Lista cheia!\n");
        return 0;
    }

    lista->elementos[lista->tamanhoAtual] = novoPacote;
    lista->tamanhoAtual++;
    return 1;
}

// Inserir elemento no inicio da lista
int inserirElementoInicio(ListaPacotes *lista, Pacote novoPacote)
{
    if (lista->tamanhoAtual >= MAX_ELEMENTOS)
    {
        printf("Lista cheia!\n");
        return 0;
    }

    // Desloca todos os elementos para a direita
    for (int i = lista->tamanhoAtual; i > 0; i--)
    {
        lista->elementos[i] = lista->elementos[i - 1];
    }

    // Insere o novo elemento no inicio
    lista->elementos[0] = novoPacote;
    lista->tamanhoAtual++;
    return 1;
}

// Inserir elemento em posicao especifica
int inserirElementoID(ListaPacotes *lista, Pacote novoPacote, int posicao)
{
    if (lista->tamanhoAtual >= MAX_ELEMENTOS)
    {
        printf("Lista cheia!\n");
        return 0;
    }

    if (posicao < 0 || posicao > lista->tamanhoAtual)
    {
        printf("Posicao inválida!\n");
        return 0;
    }

    // Desloca elementos para abrir espaco
    for (int i = lista->tamanhoAtual; i > posicao; i--)
    {
        lista->elementos[i] = lista->elementos[i - 1];
    }

    // Insere o novo elemento na posicao
    lista->elementos[posicao] = novoPacote;
    lista->tamanhoAtual++;
    return 1;
}

// Listar todos os elementos
void listarElementos(ListaPacotes *lista)
{
    if (lista->tamanhoAtual == 0)
    {
        printf("Lista vazia!\n");
        return;
    }

    for (int i = 0; i < lista->tamanhoAtual; i++)
    {
        printf("ID: %d\n", lista->elementos[i].id);
        printf("Destino: %s\n", lista->elementos[i].destino);
        printf("Preco do Pacote: R$ %.2f\n", lista->elementos[i].precoPacote);
        printf("Duracao (dias): %d\n", lista->elementos[i].duracaoDias);
        printf("Tipo Transporte: %c\n", lista->elementos[i].tipoTransporte);
        printf("------------------------\n");
    }
}

// Remover elemento por posicao
int removerElemento(ListaPacotes *lista, int posicao)
{
    if (posicao < 0 || posicao >= lista->tamanhoAtual)
    {
        printf("Posicao inválida!\n");
        return 0;
    }

    // Desloca elementos para cobrir o elemento removido
    for (int i = posicao; i < lista->tamanhoAtual - 1; i++)
    {
        lista->elementos[i] = lista->elementos[i + 1];
    }

    lista->tamanhoAtual--;
    return 1;
}

// Buscar elemento por ID
Pacote *buscarElemento(ListaPacotes *lista, int id)
{
    for (int i = 0; i < lista->tamanhoAtual; i++)
    {
        if (lista->elementos[i].id == id)
        {
            return &(lista->elementos[i]);
        }
    }
    return NULL;
}

// Atualizar elemento por ID
void atualizarElemento(ListaPacotes *lista, int id)
{
    Pacote *pacote = buscarElemento(lista, id);

    if (pacote == NULL)
    {
        printf("Pacote nao encontrado.\n");
        return;
    }

    printf("Atualizando pacote %d\n", id);

    entrarDestino(pacote->destino, MAX_DESTINO);

    printf("Novo preco: ");
    scanf("%f", &pacote->precoPacote);

    printf("Nova duracao (dias): ");
    scanf("%d", &pacote->duracaoDias);

    printf("Novo tipo de transporte (A/B): ");
    scanf(" %c", &pacote->tipoTransporte);
}

// Salvar dados em arquivo
void salvarDados(ListaPacotes *lista)
{
    FILE *arquivo = fopen("pacotes.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < lista->tamanhoAtual; i++)
    {
        fprintf(arquivo, "%d;%s;%.2f;%d;%c\n",
                lista->elementos[i].id,
                lista->elementos[i].destino,
                lista->elementos[i].precoPacote,
                lista->elementos[i].duracaoDias,
                lista->elementos[i].tipoTransporte);
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

// Carregar dados do arquivo
void carregarDados(ListaPacotes *lista)
{
    FILE *arquivo = fopen("pacotes.txt", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    // Limpa lista atual
    lista->tamanhoAtual = 0;

    Pacote pacote;
    while (fscanf(arquivo, "%d;%[^;];%f;%d;%c\n",
                  &pacote.id,
                  pacote.destino,
                  &pacote.precoPacote,
                  &pacote.duracaoDias,
                  &pacote.tipoTransporte) == 5)
    {
        inserirElemento(lista, pacote);
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

//  Funcao para excluir toda a lista
// Função para excluir toda a lista
void excluirLista(ListaPacotes *lista)
{
    lista->tamanhoAtual = 0; // Zera o tamanho da lista, excluindo todos os elementos
    printf("Lista excluida com sucesso!\n");
}

// Funcao principal
int main()
{
    ListaPacotes lista;
    inicializarLista(&lista);

    int opcao, id, posicao, ultimoId = 0;
    Pacote novoPacote;

    while (1)
    {
        printf("\n--- SISTEMA DE PACOTES DE VIAGEM ---\n");
        printf("1. Criar Lista\n");
        printf("2. Inserir Elemento no Final\n");
        printf("3. Inserir Elemento em Posicao\n");
        printf("4. Inserir Elemento no Inicio\n");
        printf("5. Listar Elementos\n");
        printf("6. Remover Elemento\n");
        printf("7. Atualizar Elemento\n");
        printf("8. Buscar Elemento\n");
        printf("9. Tamanho da Lista\n");
        printf("10. Salvar Dados\n");
        printf("11. Carregar Dados\n");
        printf("12. Excluir Lista \n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            printf("Saindo do programa...\n");
            return 0;

        case 1:
            inicializarLista(&lista);
            printf("Lista criada.\n");
            break;

        case 2:
            ultimoId++;
            novoPacote.id = ultimoId;

            entrarDestino(novoPacote.destino, MAX_DESTINO);

            printf("Preco do Pacote: ");
            scanf("%f", &novoPacote.precoPacote);

            printf("Duracao (dias): ");
            scanf("%d", &novoPacote.duracaoDias);

            printf("Tipo Transporte (A/B): ");
            scanf(" %c", &novoPacote.tipoTransporte);

            inserirElemento(&lista, novoPacote);
            break;

        case 3:
            ultimoId++;
            novoPacote.id = ultimoId;

            printf("Posicao para inserir: ");
            scanf("%d", &posicao);

            entrarDestino(novoPacote.destino, MAX_DESTINO);

            printf("Preco do Pacote: ");
            scanf("%f", &novoPacote.precoPacote);

            printf("Duracao (dias): ");
            scanf("%d", &novoPacote.duracaoDias);

            printf("Tipo Transporte (A/B): ");
            scanf(" %c", &novoPacote.tipoTransporte);

            inserirElementoID(&lista, novoPacote, posicao);
            break;

        case 4:
            ultimoId++;
            novoPacote.id = ultimoId;

            entrarDestino(novoPacote.destino, MAX_DESTINO);

            printf("Preco do Pacote: ");
            scanf("%f", &novoPacote.precoPacote);

            printf("Duracao (dias): ");
            scanf("%d", &novoPacote.duracaoDias);

            printf("Tipo Transporte (A/B): ");
            scanf(" %c", &novoPacote.tipoTransporte);

            inserirElementoInicio(&lista, novoPacote);
            break;

        case 5:
            listarElementos(&lista);
            break;

        case 6:
            printf("Posicao para remover: ");
            scanf("%d", &posicao);
            removerElemento(&lista, posicao);
            break;

        case 7:
            printf("ID do pacote a atualizar: ");
            scanf("%d", &id);
            atualizarElemento(&lista, id);
            break;

        case 8:
            printf("ID do pacote a buscar: ");
            scanf("%d", &id);
            Pacote *pacoteEncontrado = buscarElemento(&lista, id);

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
            printf("Tamanho da lista: %d\n", lista.tamanhoAtual);
            break;

        case 10:
            salvarDados(&lista);
            break;

        case 11:
            carregarDados(&lista);
            break;

        case 12: // Excluir lista
            excluirLista(&lista);
            break;

        default:
            printf("Opcao inválida.\n");
        }
    }

    return 0;
}