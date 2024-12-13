#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5
#define ARQUIVO "D:\\GitHub Desktop\\C_CodeLab\\lesserProjects\\bancoDados\\BancoYuri.txt"

typedef struct
{
    int id;
    char marca[50];
    char modelo[50];
    int ano;
    char cor[20];
    float quilometragem;
    float valor;
    char categoria[30];
    char disponibilidade;
} Carro;

typedef struct
{
    int id;
    Carro *elementos;
} Lista;

// Protótipos das funções
Lista *criarLista(void);
void carregarDados(Lista *lista);
void salvarDados(Lista *lista);
int inserirCarro(Lista *lista, Carro carro);
int removerCarro(Lista *lista, int id);
int buscarCarro(Lista *lista, int id);
void imprimirCarros(Lista *lista);
int atualizarCarro(Lista *lista, int id, Carro carro);
int inserirCarroInicio(Lista *lista, Carro carro);
Lista *excluirLista(Lista *lista);

Lista *criarLista(void)
{
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    if (nova == NULL)
    {
        printf("Erro: Falha na alocacao de memoria para a lista\n");
        return NULL;
    }

    nova->elementos = (Carro *)malloc(TAM * sizeof(Carro));
    if (nova->elementos == NULL)
    {
        printf("Erro: Falha na alocacao de memoria para os elementos\n");
        free(nova);
        return NULL;
    }

    nova->id = 0;
    return nova;
}

void carregarDados(Lista *lista)
{
    if (lista == NULL)
        return;

    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL)
    {
        printf("Aviso: Arquivo nao encontrado. Iniciando com lista vazia.\n");
        return;
    }

    Carro carro;
    while (fscanf(arquivo, "%d %s %s %d %s %f %f %s %c\n",
                  &carro.id, carro.marca, carro.modelo, &carro.ano,
                  carro.cor, &carro.quilometragem, &carro.valor,
                  carro.categoria, &carro.disponibilidade) == 9)
    {

        inserirCarro(lista, carro);
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

void salvarDados(Lista *lista)
{
    if (lista == NULL || lista->id == 0)
    {
        printf("Erro: Nada para salvar\n");
        return;
    }

    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL)
    {
        printf("Erro: Nao foi possivel abrir o arquivo para escrita\n");
        return;
    }

    for (int i = 0; i < lista->id; i++)
    {
        fprintf(arquivo, "%d %s %s %d %s %.2f %.2f %s %c\n",
                lista->elementos[i].id,
                lista->elementos[i].marca,
                lista->elementos[i].modelo,
                lista->elementos[i].ano,
                lista->elementos[i].cor,
                lista->elementos[i].quilometragem,
                lista->elementos[i].valor,
                lista->elementos[i].categoria,
                lista->elementos[i].disponibilidade);
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso em: %s\n", ARQUIVO);
}

int inserirCarro(Lista *lista, Carro carro)
{
    if (lista == NULL)
    {
        printf("Erro: Lista nao inicializada\n");
        return 0;
    }

    if (lista->id >= TAM)
    {
        printf("Erro: Lista cheia\n");
        return 0;
    }

    // Verificar se já existe um carro com este ID
    if (buscarCarro(lista, carro.id) != -1)
    {
        printf("Erro: Ja existe um carro com ID %d\n", carro.id);
        return 0;
    }

    lista->elementos[lista->id] = carro;
    lista->id++;
    printf("Carro inserido com sucesso!\n");
    return 1;
}

int removerCarro(Lista *lista, int id)
{
    if (lista == NULL || lista->id == 0)
    {
        printf("Erro: Lista vazia ou nao inicializada\n");
        return 0;
    }

    int pos = buscarCarro(lista, id);
    if (pos == -1)
    {
        printf("Erro: Carro nao encontrado\n");
        return 0;
    }

    // Deslocar os elementos
    for (int i = pos; i < lista->id - 1; i++)
    {
        lista->elementos[i] = lista->elementos[i + 1];
    }

    lista->id--;
    printf("Carro removido com sucesso!\n");
    return 1;
}

int buscarCarro(Lista *lista, int id)
{
    if (lista == NULL)
        return -1;

    for (int i = 0; i < lista->id; i++)
    {
        if (lista->elementos[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void imprimirCarros(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Erro: Lista nao inicializada\n");
        return;
    }

    if (lista->id == 0)
    {
        printf("Lista vazia\n");
        return;
    }

    printf("\n=== Lista de Carros ===\n");
    for (int i = 0; i < lista->id; i++)
    {
        printf("\nCarro %d:\n", i + 1);
        printf("ID: %d\n", lista->elementos[i].id);
        printf("Marca: %s\n", lista->elementos[i].marca);
        printf("Modelo: %s\n", lista->elementos[i].modelo);
        printf("Ano: %d\n", lista->elementos[i].ano);
        printf("Cor: %s\n", lista->elementos[i].cor);
        printf("Quilometragem: %.2f\n", lista->elementos[i].quilometragem);
        printf("Valor: R$ %.2f\n", lista->elementos[i].valor);
        printf("Categoria: %s\n", lista->elementos[i].categoria);
        printf("Disponibilidade: %c\n", lista->elementos[i].disponibilidade);
        printf("--------------------\n");
    }
}

int atualizarCarro(Lista *lista, int id, Carro carro)
{
    if (lista == NULL)
    {
        printf("Erro: Lista nao inicializada\n");
        return 0;
    }

    int pos = buscarCarro(lista, id);
    if (pos == -1)
    {
        printf("Erro: Carro nao encontrado\n");
        return 0;
    }

    lista->elementos[pos] = carro;
    printf("Carro atualizado com sucesso!\n");
    return 1;
}

int inserirCarroInicio(Lista *lista, Carro carro)
{
    if (lista == NULL)
    {
        printf("Erro: Lista nao inicializada\n");
        return 0;
    }

    if (lista->id >= TAM)
    {
        printf("Erro: Lista cheia\n");
        return 0;
    }

    // Verificar se já existe um carro com este ID
    if (buscarCarro(lista, carro.id) != -1)
    {
        printf("Erro: Ja existe um carro com ID %d\n", carro.id);
        return 0;
    }

    // Deslocar todos os elementos uma posição para frente
    for (int i = lista->id; i > 0; i--)
    {
        lista->elementos[i] = lista->elementos[i - 1];
    }

    lista->elementos[0] = carro;
    lista->id++;
    printf("Carro inserido no inicio com sucesso!\n");
    return 1;
}

Lista *excluirLista(Lista *lista)
{
    if (lista != NULL)
    {
        if (lista->elementos != NULL)
        {
            free(lista->elementos);
        }
        free(lista);
        printf("Lista excluida com sucesso!\n");
    }
    return NULL;
}

int main()
{
    Lista *lista = criarLista();
    if (lista == NULL)
    {
        printf("Erro ao criar lista\n");
        return 1;
    }

    int opcao;
    Carro carro;

    carregarDados(lista);

    do
    {
        printf("\n=== MENU ===\n");
        printf("1. Inserir carro\n");
        printf("2. Inserir carro no inicio\n");
        printf("3. Remover carro\n");
        printf("4. Buscar carro\n");
        printf("5. Atualizar carro\n");
        printf("6. Imprimir todos os carros\n");
        printf("7. Salvar e sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        switch (opcao)
        {
        case 1:
        {
            printf("ID: ");
            scanf("%d", &carro.id);
            printf("Marca: ");
            scanf("%s", carro.marca);
            printf("Modelo: ");
            scanf("%s", carro.modelo);
            printf("Ano: ");
            scanf("%d", &carro.ano);
            printf("Cor: ");
            scanf("%s", carro.cor);
            printf("Quilometragem: ");
            scanf("%f", &carro.quilometragem);
            printf("Valor: ");
            scanf("%f", &carro.valor);
            printf("Categoria: ");
            scanf("%s", carro.categoria);
            printf("Disponibilidade (D/N): ");
            scanf(" %c", &carro.disponibilidade);
            inserirCarro(lista, carro);
            break;
        }
        case 2:
        {
            printf("ID: ");
            scanf("%d", &carro.id);
            printf("Marca: ");
            scanf("%s", carro.marca);
            printf("Modelo: ");
            scanf("%s", carro.modelo);
            printf("Ano: ");
            scanf("%d", &carro.ano);
            printf("Cor: ");
            scanf("%s", carro.cor);
            printf("Quilometragem: ");
            scanf("%f", &carro.quilometragem);
            printf("Valor: ");
            scanf("%f", &carro.valor);
            printf("Categoria: ");
            scanf("%s", carro.categoria);
            printf("Disponibilidade (D/N): ");
            scanf(" %c", &carro.disponibilidade);
            inserirCarroInicio(lista, carro);
            break;
        }
        case 3:
        {
            int id;
            printf("Digite o ID do carro a ser removido: ");
            scanf("%d", &id);
            removerCarro(lista, id);
            break;
        }
        case 4:
        {
            int id;
            printf("Digite o ID do carro a ser buscado: ");
            scanf("%d", &id);
            int pos = buscarCarro(lista, id);
            if (pos != -1)
            {
                printf("\nCarro encontrado:\n");
                printf("Marca: %s\n", lista->elementos[pos].marca);
                printf("Modelo: %s\n", lista->elementos[pos].modelo);
                printf("Ano: %d\n", lista->elementos[pos].ano);
            }
            else
            {
                printf("Carro nao encontrado\n");
            }
            break;
        }
        case 5:
        {
            int id;
            printf("Digite o ID do carro a ser atualizado: ");
            scanf("%d", &id);
            printf("Novos dados:\n");
            carro.id = id;
            printf("Marca: ");
            scanf("%s", carro.marca);
            printf("Modelo: ");
            scanf("%s", carro.modelo);
            printf("Ano: ");
            scanf("%d", &carro.ano);
            printf("Cor: ");
            scanf("%s", carro.cor);
            printf("Quilometragem: ");
            scanf("%f", &carro.quilometragem);
            printf("Valor: ");
            scanf("%f", &carro.valor);
            printf("Categoria: ");
            scanf("%s", carro.categoria);
            printf("Disponibilidade (D/N): ");
            scanf(" %c", &carro.disponibilidade);
            atualizarCarro(lista, id, carro);
            break;
        }
        case 6:
            imprimirCarros(lista);
            break;
        case 7:
            salvarDados(lista);
            lista = excluirLista(lista);
            printf("Programa finalizado.\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}