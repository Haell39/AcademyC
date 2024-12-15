#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // Tamanho máximo da lista
#define ARQUIVO "D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens1\\pacotes.txt"

// Estrutura do elemento Viagem
typedef struct
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte; // 'A' para avião, 'B' para ônibus
} Viagem;

// Estrutura da lista
typedef struct
{
    Viagem viagens[MAX];
    int tamanho;
} Lista;

// Função para criar a lista
Lista *criarLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->tamanho = 0;
    return lista;
}

// Função para verificar se a lista está cheia
int estaCheia(Lista *lista)
{
    return lista->tamanho == MAX;
}

// Função para inserir um elemento no final da lista
void inserirElemento(Lista *lista, Viagem viagem)
{
    if (!estaCheia(lista))
    {
        lista->viagens[lista->tamanho] = viagem;
        lista->tamanho++;
    }
    else
    {
        printf("Erro: Lista cheia!\n");
    }
}

// Função para inserir um elemento no início da lista
void inserirElementoInicio(Lista *lista, Viagem viagem)
{
    if (!estaCheia(lista))
    {
        int i;
        for (i = lista->tamanho; i > 0; i--)
        {
            lista->viagens[i] = lista->viagens[i - 1];
        }
        lista->viagens[0] = viagem;
        lista->tamanho++;
    }
    else
    {
        printf("Erro: Lista cheia!\n");
    }
}

// Função para inserir um elemento em uma posição específica
void inserirElementoID(Lista *lista, Viagem viagem, int pos)
{
    if (!estaCheia(lista) && pos >= 0 && pos <= lista->tamanho)
    {
        int i;
        for (i = lista->tamanho; i > pos; i--)
        {
            lista->viagens[i] = lista->viagens[i - 1];
        }
        lista->viagens[pos] = viagem;
        lista->tamanho++;
    }
    else
    {
        printf("Erro: Posição inválida ou lista cheia!\n");
    }
}

// Função para listar todos os elementos
void listarElementos(Lista *lista)
{
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        Viagem viagem = lista->viagens[i];
        printf("ID: %d | Destino: %s | Preço do Pacote: %.2f | Duração (dias): %d | Tipo de Transporte: %c\n",
               viagem.id, viagem.destino, viagem.precoPacote, viagem.duracaoDias, viagem.tipoTransporte);
    }
}

// Função para remover um elemento por posição
void removerElemento(Lista *lista, int pos)
{
    if (pos >= 0 && pos < lista->tamanho)
    {
        int i;
        for (i = pos; i < lista->tamanho - 1; i++)
        {
            lista->viagens[i] = lista->viagens[i + 1];
        }
        lista->tamanho--;
    }
    else
    {
        printf("Erro: Posição inválida!\n");
    }
}

// Função para atualizar um elemento
void atualizar(Lista *lista, int pos, Viagem novaViagem)
{
    if (pos >= 0 && pos < lista->tamanho)
    {
        // Verifica se o ID da nova viagem é único
        for (int i = 0; i < lista->tamanho; i++)
        {
            if (lista->viagens[i].id == novaViagem.id && i != pos)
            {
                printf("Erro: ID %d já existe na lista!\n", novaViagem.id);
                return;
            }
        }
        lista->viagens[pos] = novaViagem;
    }
    else
    {
        printf("Erro: Posição inválida!\n");
    }
}

// Função para buscar um elemento por ID
Viagem *buscarElemento(Lista *lista, int id)
{
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        if (lista->viagens[i].id == id)
        {
            return &lista->viagens[i];
        }
    }
    printf("Pacote de Viagem com ID %d não encontrado!\n", id);
    return NULL;
}

// Função para retornar o tamanho da lista
int tamanho(Lista *lista)
{
    return lista->tamanho;
}

// Função para excluir a lista
void excluirLista(Lista *lista)
{
    free(lista);
}

// Função para carregar dados do arquivo
void carregarDados(Lista *lista)
{
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo %s.\n", ARQUIVO);
        return;
    }

    Viagem temp;
    while (fscanf(file, "%d\n", &temp.id) != EOF)
    {
        fscanf(file, "%[^\n]\n", temp.destino);
        fscanf(file, "%f\n", &temp.precoPacote);
        fscanf(file, "%d\n", &temp.duracaoDias);
        fscanf(file, " %c\n", &temp.tipoTransporte);

        // Verifica se a inserção foi bem-sucedida
        if (!estaCheia(lista))
        {
            inserirElemento(lista, temp);
        }
        else
        {
            printf("Erro: Lista cheia! Não foi possível inserir o pacote com ID %d.\n", temp.id);
        }
    }

    fclose(file);
}

// Função para salvar os dados no arquivo
void salvarDados(Lista *lista)
{
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo %s.\n", ARQUIVO);
        return;
    }

    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        Viagem viagem = lista->viagens[i];
        fprintf(file, "ID: %d | Destino: %s | Preço do Pacote: %.2f | Duração (dias): %d | Tipo de Transporte: %c\n",
                viagem.id, viagem.destino, viagem.precoPacote, viagem.duracaoDias, viagem.tipoTransporte);
    }

    fclose(file);
}

// Função principal
int main()
{
    Lista *lista = criarLista();
    int opcao;
    Viagem viagemTemp;
    int pos;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir Pacote de Viagem no Final\n");
        printf("2. Inserir Pacote de Viagem no Início\n");
        printf("3. Inserir Pacote de Viagem por Posição\n");
        printf("4. Listar Pacotes de Viagem\n");
        printf("5. Remover Pacote de Viagem por Posição\n");
        printf("6. Atualizar Pacote de Viagem\n");
        printf("7. Buscar Pacote de Viagem por ID\n");
        printf("8. Tamanho da Lista\n");
        printf("9. Carregar Dados do Arquivo\n");
        printf("10. Salvar Dados no Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite os dados do pacote de viagem:\n");
            printf("ID: ");
            scanf("%d", &viagemTemp.id);
            printf("Destino: ");
            scanf(" %[^\n]", viagemTemp.destino);
            printf("Preço do Pacote: ");
            scanf("%f", &viagemTemp.precoPacote);
            printf("Duração (dias): ");
            scanf("%d", &viagemTemp.duracaoDias);
            printf("Tipo de Transporte (A para avião, B para ônibus): ");
            scanf(" %c", &viagemTemp.tipoTransporte);
            inserirElemento(lista, viagemTemp);
            break;
        case 2:
            printf("Digite os dados do pacote de viagem:\n");
            printf("ID: ");
            scanf("%d", &viagemTemp.id);
            printf("Destino: ");
            scanf(" %[^\n]", viagemTemp.destino);
            printf("Preço do Pacote: ");
            scanf("%f", &viagemTemp.precoPacote);
            printf("Duração (dias): ");
            scanf("%d", &viagemTemp.duracaoDias);
            printf("Tipo de Transporte (A para avião, B para ônibus): ");
            scanf(" %c", &viagemTemp.tipoTransporte);
            inserirElementoInicio(lista, viagemTemp);
            break;
        case 3:
            printf("Digite os dados do pacote de viagem:\n");
            printf("ID: ");
            scanf("%d", &viagemTemp.id);
            printf("Destino: ");
            scanf(" %[^\n]", viagemTemp.destino);
            printf("Preço do Pacote: ");
            scanf("%f", &viagemTemp.precoPacote);
            printf("Duração (dias): ");
            scanf("%d", &viagemTemp.duracaoDias);
            printf("Tipo de Transporte (A para avião, B para ônibus): ");
            scanf(" %c", &viagemTemp.tipoTransporte);
            printf("Posição para inserir: ");
            scanf("%d", &pos);
            inserirElementoID(lista, viagemTemp, pos);
            break;
        case 4:
            listarElementos(lista);
            break;
        case 5:
            printf("Digite a posição para remover: ");
            scanf("%d", &pos);
            removerElemento(lista, pos);
            break;
        case 6:
            printf("Digite a posição do pacote de viagem para atualizar: ");
            scanf("%d", &pos);
            printf("Digite os novos dados do pacote de viagem:\n");
            printf("ID: ");
            scanf("%d", &viagemTemp.id);
            printf("Destino: ");
            scanf(" %[^\n]", viagemTemp.destino);
            printf("Preço do Pacote: ");
            scanf("%f", &viagemTemp.precoPacote);
            printf("Duração (dias): ");
            scanf("%d", &viagemTemp.duracaoDias);
            printf("Tipo de Transporte (A para avião, B para ônibus): ");
            scanf(" %c", &viagemTemp.tipoTransporte);
            atualizar(lista, pos, viagemTemp);
            break;
        case 7:
            printf("Digite o ID do pacote de viagem para buscar: ");
            scanf("%d", &pos);
            Viagem *encontrado = buscarElemento(lista, pos);
            if (encontrado != NULL)
            {
                printf("Pacote de Viagem encontrado: ID: %d | Destino: %s | Preço do Pacote: %.2f | Duração (dias): %d | Tipo de Transporte: %c\n",
                       encontrado->id, encontrado->destino, encontrado->precoPacote,
                       encontrado->duracaoDias, encontrado->tipoTransporte);
            }
            break;
        case 8:
            printf("Tamanho da lista: %d\n", tamanho(lista));
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
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    excluirLista(lista);
    return 0;
}