
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Aqui está mostrando a estrutura do elemento Carro que foi escolhido /
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
    char disponibilidade; /* esse aqui eu adicionei pois no gmail o senhor fala que ficou faltando um tipo char. 'D' para disponível, 'N' para não disponível*/
} Carro;

typedef struct
{
    Carro carros[MAX];
    int tamanho;
} Lista;

/* Aqui é Função que vai criar a lista*/
Lista *criarLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->tamanho = 0;
    return lista;
}

// Aqui vai verificar se a lista ta cheia ou não /
int estaCheia(Lista *lista)
{
    return lista->tamanho == MAX;
}

void inserirElemento(Lista *lista, Carro carro)
{
    if (!estaCheia(lista))
    {
        lista->carros[lista->tamanho] = carro;
        lista->tamanho++;
    }
    else
    {
        printf("Erro: Lista cheia!\n");
    }
}

// Aqui vai ser para inserir um elemento no início da lista //
void inserirElementoInicio(Lista *lista, Carro carro)
{
    if (!estaCheia(lista))
    {
        int i;
        for (i = lista->tamanho; i > 0; i--)
        {
            lista->carros[i] = lista->carros[i - 1];
        }
        lista->carros[0] = carro;
        lista->tamanho++;
    }
    else
    {
        printf("Erro: Lista cheia!\n");
    }
}

// Aqui é a função para colocar em uma posição específica da lista //
void inserirElementoID(Lista *lista, Carro carro, int pos)
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
        lista->carros[i] = lista->carros[i - 1];
    }
    lista->carros[pos] = carro;
    lista->tamanho++;
}

void listarElementos(Lista *lista)
{
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        Carro carro = lista->carros[i];
        printf("ID: %d | Marca: %s | Modelo: %s | Ano: %d | Cor: %s | Quilometragem: %.2f | Valor: %.2f | Categoria: %s | Disponibilidade: %c\n",
               carro.id, carro.marca, carro.modelo, carro.ano, carro.cor,
               carro.quilometragem, carro.valor, carro.categoria, carro.disponibilidade);
    }
}

// Aqui é a função que remove um carro pela sua posição //
void removerElemento(Lista *lista, int pos)
{
    if (pos >= 0 && pos < lista->tamanho)
    {
        int i;
        for (i = pos; i < lista->tamanho - 1; i++)
        {
            lista->carros[i] = lista->carros[i + 1];
        }
        lista->tamanho--;
    }
    else
    {
        printf("Erro: Posição inválida!\n");
    }
}

// Aqui é a função que atualiza um carro //
void atualizar(Lista *lista, int pos, Carro novoCarro)
{
    if (pos >= 0 && pos < lista->tamanho)
    {
        lista->carros[pos] = novoCarro;
    }
    else
    {
        printf("Erro: Posição inválida!\n");
    }
}

// Aqui é a função que vai buscar um carro pelo id //
Carro *buscarElemento(Lista *lista, int id)
{
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        if (lista->carros[i].id == id)
        {
            return &lista->carros[i];
        }
    }
    printf("Carro com ID %d não encontrado!\n", id);
    return NULL;
}

int tamanho(Lista *lista)
{
    return lista->tamanho;
}

void excluirLista(Lista *lista)
{
    free(lista);
}

void carregarDados(Lista *lista)
{
    FILE *file = fopen("carros.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Carro temp;
    while (fscanf(file, "%d\n", &temp.id) != EOF)
    {
        fscanf(file, "%[^\n]\n", temp.marca);
        fscanf(file, "%[^\n]\n", temp.modelo);
        fscanf(file, "%d\n", &temp.ano);
        fscanf(file, "%[^\n]\n", temp.cor);
        fscanf(file, "%f\n", &temp.quilometragem);
        fscanf(file, "%f\n", &temp.valor);
        fscanf(file, "%[^\n]\n", temp.categoria);
        fscanf(file, " %c\n", &temp.disponibilidade);
        inserirElemento(lista, temp);
    }

    fclose(file);
}

// Aqui vai salvar os dados no arquivo //
void salvarDados(Lista *lista)
{
    FILE *file = fopen("carros.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        Carro carro = lista->carros[i];
        fprintf(file, "ID: %d | Marca: %s | Modelo: %s | Ano: %d | Cor: %s | Quilometragem: %.2f | Valor: %.2f | Categoria: %s | Disponibilidade: %c\n",
                carro.id, carro.marca, carro.modelo, carro.ano, carro.cor,
                carro.quilometragem, carro.valor, carro.categoria, carro.disponibilidade);
    }

    fclose(file);
}

int main()
{
    Lista *lista = criarLista();
    int opcao;
    Carro carroTemp;
    int pos;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir Carro no Final\n");
        printf("2. Inserir Carro no Início\n");
        printf("3. Inserir Carro por Posição\n");
        printf("4. Listar Carros\n");
        printf("5. Remover Carro por Posição\n");
        printf("6. Atualizar Carro\n");
        printf("7. Buscar Carro por ID\n");
        printf("8. Tamanho da Lista\n");
        printf("9. Carregar Dados do Arquivo\n");
        printf("10. Salvar Dados no Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite os dados do carro:\n");
            printf("ID: ");
            scanf("%d", &carroTemp.id);
            printf("Marca: ");
            scanf(" %[^\n]", carroTemp.marca);
            printf("Modelo: ");
            scanf(" %[^\n]", carroTemp.modelo);
            printf("Ano: ");
            scanf("%d", &carroTemp.ano);
            printf("Cor: ");
            scanf(" %[^\n]", carroTemp.cor);
            printf("Quilometragem: ");
            scanf("%f", &carroTemp.quilometragem);
            printf("Valor: ");
            scanf("%f", &carroTemp.valor);
            printf("Categoria: ");
            scanf(" %[^\n]", carroTemp.categoria);
            printf("Disponibilidade (D/N): ");
            scanf(" %c", &carroTemp.disponibilidade);
            inserirElemento(lista, carroTemp);
            break;
        case 2:
            printf("Digite os dados do carro:\n");
            printf("ID: ");
            scanf("%d", &carroTemp.id);
            printf("Marca: ");
            scanf(" %[^\n]", carroTemp.marca);
            printf("Modelo: ");
            scanf(" %[^\n]", carroTemp.modelo);
            printf("Ano: ");
            scanf("%d", &carroTemp.ano);
            printf("Cor: ");
            scanf(" %[^\n]", carroTemp.cor);
            printf("Quilometragem: ");
            scanf("%f", &carroTemp.quilometragem);
            printf("Valor: ");
            scanf("%f", &carroTemp.valor);
            printf("Categoria: ");
            scanf(" %[^\n]", carroTemp.categoria);
            printf("Disponibilidade (D/N): ");
            scanf(" %c", &carroTemp.disponibilidade);
            inserirElementoInicio(lista, carroTemp);
            break;
        case 3:
            printf("Digite os dados do carro:\n");
            printf("ID: ");
            scanf("%d", &carroTemp.id);
            printf("Marca: ");
            scanf(" %[^\n]", carroTemp.marca);
            printf("Modelo: ");
            scanf(" %[^\n]", carroTemp.modelo);
            printf("Ano: ");
            scanf("%d", &carroTemp.ano);
            printf("Cor: ");
            scanf(" %[^\n]", carroTemp.cor);
            printf("Quilometragem: ");
            scanf("%f", &carroTemp.quilometragem);
            printf("Valor: ");
            scanf("%f", &carroTemp.valor);
            printf("Categoria: ");
            scanf(" %[^\n]", carroTemp.categoria);
            printf("Disponibilidade (D/N): ");
            scanf(" %c", &carroTemp.disponibilidade);

            printf("Posição para inserir: ");
            scanf("%d", &pos);

            if (pos < 0 || pos > tamanho(lista))
            {
                printf("Erro: Posição inválida! Insira um valor entre 0 e %d.\n", tamanho(lista));
            }
            else
            {
                inserirElementoID(lista, carroTemp, pos);
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
            printf("Posição para atualizar: ");
            scanf("%d", &pos);
            if (pos >= 0 && pos < tamanho(lista))
            {
                printf("Digite os novos dados do carro:\n");
                printf("ID: ");
                scanf("%d", &carroTemp.id);
                printf("Marca: ");
                scanf(" %[^\n]", carroTemp.marca);
                printf("Modelo: ");
                scanf(" %[^\n]", carroTemp.modelo);
                printf("Ano: ");
                scanf("%d", &carroTemp.ano);
                printf("Cor: ");
                scanf(" %[^\n]", carroTemp.cor);
                printf("Quilometragem: ");
                scanf("%f", &carroTemp.quilometragem);
                printf("Valor: ");
                scanf("%f", &carroTemp.valor);
                printf("Categoria: ");
                scanf(" %[^\n]", carroTemp.categoria);
                printf("Disponibilidade (D/N): ");
                scanf(" %c", &carroTemp.disponibilidade);
                atualizar(lista, pos, carroTemp);
            }
            else
            {
                printf("Erro: Posição inválida!\n");
            }
            break;
        case 7:
            printf("ID do carro para buscar: ");
            int id;
            scanf("%d", &id);
            Carro *encontrado = buscarElemento(lista, id);
            if (encontrado != NULL)
            {
                printf("Carro encontrado: ID: %d | Marca: %s | Modelo: %s | Ano: %d | Cor: %s | Quilometragem: %.2f | Valor: %.2f | Categoria: %s | Disponibilidade: %c\n",
                       encontrado->id, encontrado->marca, encontrado->modelo, encontrado->ano, encontrado->cor,
                       encontrado->quilometragem, encontrado->valor, encontrado->categoria, encontrado->disponibilidade);
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
            excluirLista(lista);
            printf("Lista excluída e programa encerrado.\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}