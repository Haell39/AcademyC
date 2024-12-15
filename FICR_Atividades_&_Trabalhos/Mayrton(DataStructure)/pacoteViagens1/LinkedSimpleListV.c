#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_PACOTES 100

// Estrutura do elemento Pacote de Viagem
typedef struct
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte; // 'A' para avião, 'B' para ônibus
} PacoteViagem;

typedef struct
{
    PacoteViagem pacotes[MAX];
    int tamanho;
} Lista;

// Função que cria a lista
Lista *criarLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->tamanho = 0;
    return lista;
}

// Verifica se a lista está cheia
int estaCheia(Lista *lista)
{
    return lista->tamanho == MAX;
}

// Insere um pacote de viagem no final da lista
void inserirElemento(Lista *lista, PacoteViagem pacote)
{
    if (!estaCheia(lista))
    {
        lista->pacotes[lista->tamanho] = pacote;
        lista->tamanho++;
    }
    else
    {
        printf("Erro: Lista cheia!\n");
    }
}

// Insere um pacote de viagem no início da lista
void inserirElementoInicio(Lista *lista, PacoteViagem pacote)
{
    if (!estaCheia(lista))
    {
        int i;
        for (i = lista->tamanho; i > 0; i--)
        {
            lista->pacotes[i] = lista->pacotes[i - 1];
        }
        lista->pacotes[0] = pacote;
        lista->tamanho++;
    }
    else
    {
        printf("Erro: Lista cheia!\n");
    }
}

// Insere um pacote de viagem em uma posição específica da lista
void inserirElementoID(Lista *lista, PacoteViagem pacote, int pos)
{
    if (estaCheia(lista))
    {
        printf("Erro: Lista cheia! Não é possível inserir mais elementos.\n");
        return;
    }
    if (pos < 0 || pos > lista->tamanho)
    {
        printf("Erro: Posição inválida! A posição deve estar entre 0 e %d.\n", lista->tamanho);
        return;
    }
    int i;
    for (i = lista->tamanho; i > pos; i--)
    {
        lista->pacotes[i] = lista->pacotes[i - 1];
    }
    lista->pacotes[pos] = pacote;
    lista->tamanho++;
}

// Lista todos os pacotes de viagem
void listarElementos(Lista *lista)
{
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        PacoteViagem pacote = lista->pacotes[i];
        printf("ID: %d | Destino: %s | Preço: %.2f | Duração: %d dias | Transporte: %c\n",
               pacote.id, pacote.destino, pacote.precoPacote, pacote.duracaoDias, pacote.tipoTransporte);
    }
}

// Remove um pacote de viagem pela sua posição
void removerElemento(Lista *lista, int pos)
{
    if (pos >= 0 && pos < lista->tamanho)
    {
        int i;
        for (i = pos; i < lista->tamanho - 1; i++)
        {
            lista->pacotes[i] = lista->pacotes[i + 1];
        }
        lista->tamanho--;
    }
    else
    {
        printf("Erro: Posição inválida!\n");
    }
}

// Atualiza um pacote de viagem
void atualizar(Lista *lista)
{
    int id;
    printf("Digite o ID do pacote que deseja atualizar: ");
    scanf("%d", &id);

    int encontrado = 0; // Flag para verificar se o ID foi encontrado

    for (int i = 0; i < lista->tamanho; i++)
    {
        if (lista->pacotes[i].id == id)
        {
            printf("Pacote encontrado. Insira os novos dados:\n");

            printf("Novo destino: ");
            scanf(" %[^\n]", lista->pacotes[i].destino);

            printf("Novo custo: ");
            scanf("%f", &lista->pacotes[i].precoPacote);

            printf("Pacote com ID %d atualizado com sucesso!\n", id);
            encontrado = 1; // Marca que o ID foi encontrado
            break;
        }
    }

    if (!encontrado)
    {
        printf("Erro: Pacote com ID %d não encontrado!\n", id);
    }
}

// Busca um pacote de viagem pelo id
PacoteViagem *buscarElemento(Lista *lista, int id)
{
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        if (lista->pacotes[i].id == id)
        {
            return &lista->pacotes[i];
        }
    }
    printf("Pacote com ID %d não encontrado!\n", id);
    return NULL;
}

int tamanho(Lista *lista)
{
    return lista->tamanho;
}

// << Excluir lista :

void limparArquivo(const char *nomeArquivo)
{
    FILE *file = fopen(nomeArquivo, "w");
    if (file != NULL)
    {
        fclose(file);
    }
    else
    {
        printf("Erro ao limpar o arquivo %s.\n", nomeArquivo);
    }
}

void excluirLista(Lista *lista)
{
    free(lista);
    limparArquivo("pacotes.txt"); // Limpa o conteúdo do arquivo
}

void carregarDados(Lista *lista)
{
    FILE *file = fopen("pacotes.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    // Resetar a lista antes de carregar novos dados
    lista->tamanho = 0;

    PacoteViagem pacoteTemp;
    while (fscanf(file, "%d %[^\n] %f %d %c",
                  &pacoteTemp.id,
                  pacoteTemp.destino,
                  &pacoteTemp.precoPacote,
                  &pacoteTemp.duracaoDias,
                  &pacoteTemp.tipoTransporte) == 5)
    {
        if (lista->tamanho < MAX_PACOTES)
        {
            lista->pacotes[lista->tamanho] = pacoteTemp;
            lista->tamanho++; // Atualiza o tamanho da lista a cada pacote carregado
        }
        else
        {
            printf("Erro: Lista cheia. Não foi possível carregar mais pacotes.\n");
            break;
        }
    }

    fclose(file);
    printf("Carregamento concluído. Total de pacotes: %d\n", lista->tamanho);
}

// Salva os dados no arquivo
void salvarDados(Lista *lista)
{
    FILE *file = fopen("pacotes.txt", "w");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int i;

    for (i = 0; i < lista->tamanho; i++)
    {
        PacoteViagem pacote = lista->pacotes[i];

        fprintf(file, "ID: %d\nDestino: %s\nPreço: %.2f\nTempo: %d\nTransporte: %c\n",
                pacote.id, pacote.destino, pacote.precoPacote,
                pacote.duracaoDias, pacote.tipoTransporte);
    }

    fclose(file);
}

int main()
{
    Lista *lista = criarLista();

    int opcao;

    PacoteViagem pacoteTemp;

    int pos;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir Pacote no Final\n");
        printf("2. Inserir Pacote no Início\n");
        printf("3. Inserir Pacote por Posição\n");
        printf("4. Listar Pacotes\n");
        printf("5. Remover Pacote por Posição\n");
        printf("6. Atualizar Pacote\n");
        printf("7. Buscar Pacote por ID\n");
        printf("8. Tamanho da Lista\n");
        printf("9. Carregar Dados do Arquivo\n");
        printf("10. Salvar Dados no Arquivo\n");
        printf("0. Sair\n");
        printf("11. Excluir a Lista\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite os dados do pacote:\n");
            printf("ID: ");
            scanf("%d", &pacoteTemp.id);
            printf("Destino: ");
            scanf(" %[^\n]", pacoteTemp.destino);
            printf("Preço: ");
            scanf("%f", &pacoteTemp.precoPacote);
            printf("Duração em dias: ");
            scanf("%d", &pacoteTemp.duracaoDias);
            printf("Tipo de Transporte (A/B): ");
            scanf(" %c", &pacoteTemp.tipoTransporte);
            inserirElemento(lista, pacoteTemp);
            break;

        case 2:
            printf("Digite os dados do pacote:\n");
            printf("ID: ");
            scanf("%d", &pacoteTemp.id);
            printf("Destino: ");
            scanf(" %[^\n]", pacoteTemp.destino);
            printf("Preço: ");
            scanf("%f", &pacoteTemp.precoPacote);
            printf("Duração em dias: ");
            scanf("%d", &pacoteTemp.duracaoDias);
            printf("Tipo de Transporte (A/B): ");
            scanf(" %c", &pacoteTemp.tipoTransporte);
            inserirElementoInicio(lista, pacoteTemp);
            break;

        case 3:
            printf("Digite os dados do pacote:\n");
            printf("ID: ");
            scanf("%d", &pacoteTemp.id);
            printf("Destino: ");
            scanf(" %[^\n]", pacoteTemp.destino);
            printf("Preço: ");
            scanf("%f", &pacoteTemp.precoPacote);
            printf("Duração em dias: ");
            scanf("%d", &pacoteTemp.duracaoDias);
            printf("Tipo de Transporte (A/B): ");
            scanf(" %c", &pacoteTemp.tipoTransporte);
            printf("Posição para inserir: ");
            scanf("%d", &pos);

            if (pos < 0 || pos > tamanho(lista))
            {
                printf("Erro: Posição inválida! Insira um valor entre 0 e %d.\n", tamanho(lista));
            }
            else
            {
                inserirElementoID(lista, pacoteTemp, pos);
            }
            break;

        case 4:
            listarElementos(lista);
            break;

        case 5:
            printf("Posição para remover: ");
            scanf("%d", &pos);
            removerElemento(lista, pos);
            break;

        case 6:
        {
            int id;
            printf("Digite o ID do pacote que deseja atualizar: ");
            scanf("%d", &id);

            PacoteViagem pacoteTemp;
            int encontrado = 0; // Flag para verificar se o ID foi encontrado

            for (int i = 0; i < tamanho(lista); i++)
            {
                if (lista->pacotes[i].id == id)
                {
                    printf("Pacote encontrado. Insira os novos dados:\n");
                    printf("Novo ID: ");
                    scanf("%d", &pacoteTemp.id);
                    printf("Novo Destino: ");
                    scanf(" %[^\n]", pacoteTemp.destino);
                    printf("Novo Preço: ");
                    scanf("%f", &pacoteTemp.precoPacote);
                    printf("Nova Duração em dias: ");
                    scanf("%d", &pacoteTemp.duracaoDias);
                    printf("Novo Tipo de Transporte (A/B): ");
                    scanf(" %c", &pacoteTemp.tipoTransporte);

                    // Atualiza os dados no pacote correspondente
                    lista->pacotes[i] = pacoteTemp;
                    encontrado = 1; // Marca que o ID foi encontrado
                    printf("Pacote com ID %d atualizado com sucesso!\n", id);
                    break;
                }
            }

            if (!encontrado)
            {
                printf("Erro: Pacote com ID %d não encontrado!\n", id);
            }
            break;
        }

        case 7:
            printf("ID do pacote para buscar: ");
            int id;
            scanf("%d", &id);

            PacoteViagem *encontrado = buscarElemento(lista, id);

            if (encontrado != NULL)
            {
                printf("Pacote encontrado: ID: %d | Destino: %s | Preço: %.2f | Duração: %d dias | Transporte: %c\n",
                       encontrado->id, encontrado->destino,
                       encontrado->precoPacote,
                       encontrado->duracaoDias,
                       encontrado->tipoTransporte);
            }
            break;

        case 8:
            printf("Tamanho atual da lista: %d\n", tamanho(lista));
            break;

        case 9:
            carregarDados(lista);
            printf("Dados carregados com sucesso!\n");
            break;

        case 10:
            salvarDados(lista);
            printf("Dados salvos com sucesso!\n");
            break;
        case 0:
            printf("Você realmente deseja sair? (s/n): ");
            char confirmacao;
            scanf(" %c", &confirmacao);
            if (confirmacao == 's' || confirmacao == 'S')
            {
                printf("Programa encerrado.\n");
                return 0;
            }
            break;

        case 11:
            excluirLista(&lista);
            printf("Lista excluída e arquivo limpo.\n");
            lista = criarLista(); // Recriar a lista vazia após exclusão
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
