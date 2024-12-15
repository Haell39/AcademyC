#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Viagem
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte; // 'A' - Avião, 'B' - Ônibus
} Viagem;

typedef struct No
{
    Viagem dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Funções de Manipulação da Lista
Lista *criarLista();
void inserirElemento(Lista *lista, Viagem viagem);
void inserirElementoID(Lista *lista, Viagem viagem, int posicao);
void inserirElementoInicio(Lista *lista, Viagem viagem);
void listarElementos(Lista *lista);
int removerElemento(Lista *lista, int id);
void atualizarElemento(Lista *lista, int id);
No *buscarElemento(Lista *lista, int id);
int tamanho(Lista *lista);
void excluirLista(Lista *lista);
void salvarDados(Lista *lista, char *nomeArquivo);
void carregarDados(Lista *lista, char *nomeArquivo);

// Menu Principal
int main()
{
    Lista *lista = criarLista();
    int opcao, id, posicao;
    Viagem viagem;
    char *nomeArquivo = "D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens8\\pacotes.txt";

    carregarDados(lista, nomeArquivo); // Carrega dados do arquivo ao iniciar o programa

    do
    {
        printf("\n=== Sistema de Gerenciamento de Pacotes de Viagem ===\n");
        printf("1. Inserir Viagem no Final\n");
        printf("2. Inserir Viagem em Posicao\n");
        printf("3. Inserir Viagem no Inicio\n");
        printf("4. Listar Viagens\n");
        printf("5. Remover Viagem por ID\n");
        printf("6. Atualizar Viagem por ID\n");
        printf("7. Buscar Viagem por ID\n");
        printf("8. Tamanho da Lista\n");
        printf("9. Salvar Dados\n");
        printf("10. Excluir Lista\n");
        printf("11. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite os dados da viagem:\n");
            printf("ID: ");
            scanf("%d", &viagem.id);
            printf("Destino: ");
            getchar();
            fgets(viagem.destino, 50, stdin);
            viagem.destino[strcspn(viagem.destino, "\n")] = '\0';
            printf("Preco do Pacote: ");
            scanf("%f", &viagem.precoPacote);
            printf("Duracao (em dias): ");
            scanf("%d", &viagem.duracaoDias);
            printf("Tipo de Transporte (A - Aviao / B - Onibus): ");
            scanf(" %c", &viagem.tipoTransporte);
            inserirElemento(lista, viagem);
            break;

        case 2:
            printf("Posicao para inserir: ");
            scanf("%d", &posicao);
            printf("Digite os dados da viagem:\n");
            printf("ID: ");
            scanf("%d", &viagem.id);
            printf("Destino: ");
            getchar();
            fgets(viagem.destino, 50, stdin);
            viagem.destino[strcspn(viagem.destino, "\n")] = '\0';
            printf("Preco do Pacote: ");
            scanf("%f", &viagem.precoPacote);
            printf("Duracao (em dias): ");
            scanf("%d", &viagem.duracaoDias);
            printf("Tipo de Transporte (A - Aviao / B - Onibus): ");
            scanf(" %c", &viagem.tipoTransporte);
            inserirElementoID(lista, viagem, posicao);
            break;

        case 3:
            printf("Digite os dados da viagem:\n");
            printf("ID: ");
            scanf("%d", &viagem.id);
            printf("Destino: ");
            getchar();
            fgets(viagem.destino, 50, stdin);
            viagem.destino[strcspn(viagem.destino, "\n")] = '\0';
            printf("Preco do Pacote: ");
            scanf("%f", &viagem.precoPacote);
            printf("Duracao (em dias): ");
            scanf("%d", &viagem.duracaoDias);
            printf("Tipo de Transporte (A - Aviao / B - Onibus): ");
            scanf(" %c", &viagem.tipoTransporte);
            inserirElementoInicio(lista, viagem);
            break;

        case 4:
            listarElementos(lista);
            break;

        case 5:
            printf("Digite o ID da viagem para remover: ");
            scanf("%d", &id);
            if (removerElemento(lista, id))
                printf("Viagem removida com sucesso.\n");
            else
                printf("Viagem nao encontrada.\n");
            break;

        case 6:
            printf("Digite o ID da viagem para atualizar: ");
            scanf("%d", &id);
            atualizarElemento(lista, id);
            break;

        case 7:
            printf("Digite o ID da viagem para buscar: ");
            scanf("%d", &id);
            No *encontrado = buscarElemento(lista, id);
            if (encontrado != NULL)
            {
                printf("Viagem encontrada: ID=%d, Destino=%s, Preco=%.2f, Duracao=%d, Transporte=%c\n",
                       encontrado->dado.id, encontrado->dado.destino, encontrado->dado.precoPacote,
                       encontrado->dado.duracaoDias, encontrado->dado.tipoTransporte);
            }
            else
            {
                printf("Viagem nao encontrada.\n");
            }
            break;

        case 8:
            printf("Tamanho atual da lista: %d\n", tamanho(lista));
            break;

        case 9:
            salvarDados(lista, nomeArquivo);
            printf("Dados salvos com sucesso.\n");
            break;

        case 10:
            excluirLista(lista);
            printf("Lista excluida com sucesso.\n");
            break;

        case 11:
            salvarDados(lista, nomeArquivo); // Salva os dados antes de sair
            printf("Saindo do programa. Ate logo!\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 11);

    return 0;
}

// Implementação das funções de lista
Lista *criarLista()
{
    Lista *novaLista = (Lista *)malloc(sizeof(Lista));
    novaLista->inicio = NULL;
    return novaLista;
}

void inserirElemento(Lista *lista, Viagem viagem)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dado = viagem;
    if (lista->inicio == NULL)
    {
        lista->inicio = novoNo;
        novoNo->prox = novoNo; // Circular
    }
    else
    {
        No *temp = lista->inicio;
        while (temp->prox != lista->inicio)
        {
            temp = temp->prox;
        }
        temp->prox = novoNo;
        novoNo->prox = lista->inicio;
    }
}

void inserirElementoInicio(Lista *lista, Viagem viagem)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dado = viagem;
    if (lista->inicio == NULL)
    {
        lista->inicio = novoNo;
        novoNo->prox = novoNo; // Circular
    }
    else
    {
        No *temp = lista->inicio;
        while (temp->prox != lista->inicio)
        {
            temp = temp->prox;
        }
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        temp->prox = lista->inicio;
    }
}

void listarElementos(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }
    No *temp = lista->inicio;
    do
    {
        printf("ID: %d | Destino: %s | Preco: %.2f | Duracao: %d dias | Transporte: %c\n",
               temp->dado.id, temp->dado.destino, temp->dado.precoPacote,
               temp->dado.duracaoDias, temp->dado.tipoTransporte);
        temp = temp->prox;
    } while (temp != lista->inicio);
}

int removerElemento(Lista *lista, int id)
{
    if (lista->inicio == NULL)
        return 0;

    No *atual = lista->inicio, *anterior = NULL;
    do
    {
        if (atual->dado.id == id)
        {
            if (anterior == NULL)
            { // Remover o primeiro nó
                No *temp = lista->inicio;
                while (temp->prox != lista->inicio)
                    temp = temp->prox;
                if (temp == lista->inicio)
                { // Apenas 1 elemento
                    free(lista->inicio);
                    lista->inicio = NULL;
                }
                else
                {
                    temp->prox = lista->inicio->prox;
                    free(lista->inicio);
                    lista->inicio = temp->prox;
                }
            }
            else
            { // Remover elemento intermediário ou final
                anterior->prox = atual->prox;
                free(atual);
            }
            return 1; // Sucesso
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != lista->inicio);

    return 0; // Não encontrado
}

void atualizarElemento(Lista *lista, int id)
{
    No *no = buscarElemento(lista, id);
    if (no != NULL)
    {
        printf("Digite os novos dados para a viagem:\n");
        printf("Destino: ");
        getchar();
        fgets(no->dado.destino, 50, stdin);
        no->dado.destino[strcspn(no->dado.destino, "\n")] = '\0';
        printf("Preco do Pacote: ");
        scanf("%f", &no->dado.precoPacote);
        printf("Duracao (em dias): ");
        scanf("%d", &no->dado.duracaoDias);
        printf("Tipo de Transporte (A - Aviao / B - Onibus): ");
        scanf(" %c", &no->dado.tipoTransporte);
        printf("Viagem atualizada com sucesso!\n");
    }
    else
    {
        printf("Viagem com ID %d nao encontrada.\n", id);
    }
}

No *buscarElemento(Lista *lista, int id)
{
    if (lista->inicio == NULL)
        return NULL;

    No *temp = lista->inicio;
    do
    {
        if (temp->dado.id == id)
            return temp;
        temp = temp->prox;
    } while (temp != lista->inicio);

    return NULL;
}

int tamanho(Lista *lista)
{
    if (lista->inicio == NULL)
        return 0;

    int count = 0;
    No *temp = lista->inicio;
    do
    {
        count++;
        temp = temp->prox;
    } while (temp != lista->inicio);

    return count;
}

void excluirLista(Lista *lista)
{
    if (lista->inicio == NULL)
        return;

    No *temp = lista->inicio;
    No *proxNo;
    do
    {
        proxNo = temp->prox;
        free(temp);
        temp = proxNo;
    } while (temp != lista->inicio);

    lista->inicio = NULL;
}

void salvarDados(Lista *lista, char *nomeArquivo)
{
    FILE *file = fopen(nomeArquivo, "w");
    if (!file)
    {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }
    No *temp = lista->inicio;
    if (temp == NULL)
    {
        fclose(file);
        return;
    }

    do
    {
        fprintf(file, "%d %s %.2f %d %c\n", temp->dado.id, temp->dado.destino,
                temp->dado.precoPacote, temp->dado.duracaoDias, temp->dado.tipoTransporte);
        temp = temp->prox;
    } while (temp != lista->inicio);

    fclose(file);
}

void carregarDados(Lista *lista, char *nomeArquivo)
{
    FILE *file = fopen(nomeArquivo, "r");
    if (!file)
        return; // Arquivo não existe ainda

    Viagem viagem;
    while (fscanf(file, "%d %49s %f %d %c", &viagem.id, viagem.destino, &viagem.precoPacote,
                  &viagem.duracaoDias, &viagem.tipoTransporte) != EOF)
    {
        inserirElemento(lista, viagem);
    }
    fclose(file);
}
