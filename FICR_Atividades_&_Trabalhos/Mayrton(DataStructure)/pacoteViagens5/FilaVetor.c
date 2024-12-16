#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5
#define ARQUIVO "pacotes.txt"

typedef struct
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
} Pacote;

typedef struct
{
    int inicio;
    int fim;
    Pacote *elementos;
} Fila;

/* Funções implementadas */
Fila *Criar();
int Enqueue(Fila *, Pacote);
int Dequeue(Fila *);
void VerPacoteInicio(Fila *);
Fila *Excluir(Fila *);
void CarregarDados(Fila **);
void SalvarDados(Fila *);
Fila *CriarFila();

/* Função para criar uma fila */
Fila *Criar()
{
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if (novaFila == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return NULL;
    }

    novaFila->inicio = 0;
    novaFila->fim = 0;
    novaFila->elementos = (Pacote *)malloc(TAM * sizeof(Pacote));
    if (novaFila->elementos == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        free(novaFila);
        return NULL;
    }

    printf("Fila criada com sucesso!\n");
    return novaFila;
}

/* Função para inserir pacotes */
int Enqueue(Fila *fila, Pacote novoPacote)
{

    if ((fila->fim + 1) % TAM == fila->inicio)
    {
        printf("Fila cheia!\n");
        return 0;
    }

    fila->elementos[fila->fim] = novoPacote;
    fila->fim = (fila->fim + 1) % TAM;
    return 1;
}

/* Função para remover pacotes */
int Dequeue(Fila *fila)
{
    if (fila == NULL)
    {
        printf("A fila não foi criada!\n");
        return 0;
    }
    if (fila->inicio == fila->fim)
    {
        printf("Fila vazia! Não há pacotes para remover.\n");
        return 0;
    }

    // Remove o pacote do início da fila
    Pacote pacoteRemovido = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM; // Atualiza o índice de início

    printf("Pacote removido:\n");
    printf("|ID: %d\n", pacoteRemovido.id);
    printf("|Destino: %s\n", pacoteRemovido.destino);
    printf("|Preco: R$ %.2f\n", pacoteRemovido.precoPacote);
    printf("|Duracao: %d dias\n", pacoteRemovido.duracaoDias);
    printf("|Transporte: %c\n", pacoteRemovido.tipoTransporte);

    return 1; // Retorna 1 para indicar que a remoção foi bem-sucedida
}

/* Função para ver pacote no início */
void VerPacoteInicio(Fila *fila)
{

    if (fila == NULL || fila->inicio == fila->fim)
    {
        printf("Fila vazia!\n");
        return;
    }

    Pacote inicio = fila->elementos[fila->inicio];
    printf("\n|Pacote no inicio da fila:");
    printf("\n|ID: %d", inicio.id);
    printf("\n|Destino: %s", inicio.destino);
    printf("\n|Preco: R$ %.2f", inicio.precoPacote);
    printf("\n|Duracao: %d dias", inicio.duracaoDias);
    printf("\n|Transporte: %s\n",
           inicio.tipoTransporte == 'A' ? "Aviao" : (inicio.tipoTransporte == 'B' ? "Onibus" : "N/A"));
}

/* Função para excluir uma fila */
Fila *Excluir(Fila *fila)
{
    if (fila == NULL)
    {
        printf("A fila nao existe!\n");
        return NULL;
    }

    free(fila->elementos);
    free(fila);
    printf("Fila excluida com sucesso!\n");
    return NULL;
}

/* Função para carregar dados */
void CarregarDados(Fila **fila)
{
    if (*fila == NULL)
    {
        printf("A fila não existe. Criando uma nova fila...\n");
        *fila = Criar();
        if (*fila == NULL)
        {
            printf("Erro ao criar a fila!\n");
            return;
        }
    }

    FILE *file = fopen("pacotes.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[256];
    int pacotesCarregados = 0;
    while (fgets(linha, sizeof(linha), file) != NULL)
    {
        Pacote pacote;
        if (sscanf(linha, "ID: %d | Destino: %[^|] | Preco: R$ %f | Duracao: %d dias | Transporte: %c",
                   &pacote.id, pacote.destino, &pacote.precoPacote,
                   &pacote.duracaoDias, &pacote.tipoTransporte) == 5)
        {
            if (Enqueue(*fila, pacote))
            {
                pacotesCarregados++;
            }
            else
            {
                printf("Fila cheia, não foi possível carregar todos os pacotes!\n");
                break;
            }
        }
    }

    fclose(file);
    if (pacotesCarregados > 0)
    {
        printf("%d dados carregados com sucesso!\n", pacotesCarregados);
    }
    else
    {
        printf("Nenhum dado foi carregado. O arquivo estava vazio ou não foi possível ler os dados.\n");
    }
}

/* Função para salvar dados */
void SalvarDados(Fila *fila)
{

    FILE *file = fopen("pacotes.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int i = fila->inicio;
    while (i != fila->fim)
    {
        Pacote pacote = fila->elementos[i];
        char tipoTransporteStr[10];
        if (pacote.tipoTransporte == 'A' || pacote.tipoTransporte == 'a')
            strcpy(tipoTransporteStr, "(Aviao)");
        else if (pacote.tipoTransporte == 'B' || pacote.tipoTransporte == 'b')
            strcpy(tipoTransporteStr, "(Onibus)");
        else
            strcpy(tipoTransporteStr, "(N/A)");

        fprintf(file, "ID: %d | Destino: %s | Preco: R$ %.2f | Duracao: %d dias | Transporte: %c %s\n",
                pacote.id, pacote.destino, pacote.precoPacote, pacote.duracaoDias,
                pacote.tipoTransporte, tipoTransporteStr);
        i = (i + 1) % TAM;
    }

    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

Fila *CriarFila()
{
    Fila *novaFila = Criar();
    if (novaFila == NULL)
    {
        printf("Erro ao criar a fila!\n");
    }
    return novaFila;
}

int main()
{
    Fila *fila = NULL;
    int opcao;
    Pacote novoPacote;

    do
    {
        printf("\n---Menu de Pacotes de Viagem---\n");
        printf("[1] Inserir Pacote\n");
        printf("[2] Ver Pacote no Inicio\n");
        printf("[3] Remover Pacote\n");
        printf("[4] Carregar Dados\n");
        printf("[5] Salvar Dados\n");
        printf("[6] Excluir Fila\n");
        printf("[0] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: /*Inserir Pacotes*/
            if (fila == NULL)
            {
                printf("A fila foi criada automaticamente.\n");
                fila = Criar();
                if (fila == NULL)
                {
                    printf("Erro ao criar a fila!\n");
                    return 1;
                }
            }
            printf("\n---Inserir Pacote---\n");
            printf("|ID: ");
            scanf("%d", &novoPacote.id);
            getchar(); // Limpa o buffer do \n
            printf("|Destino: ");
            fgets(novoPacote.destino, 49, stdin);
            novoPacote.destino[strcspn(novoPacote.destino, "\n")] = '\0';
            printf("|Preco: ");
            scanf("%f", &novoPacote.precoPacote);
            printf("|Duracao (dias): ");
            scanf("%d", &novoPacote.duracaoDias);
            printf("|Tipo de Transporte (A-Aviao, B-Onibus): ");
            scanf(" %c", &novoPacote.tipoTransporte);
            Enqueue(fila, novoPacote);
            break;
        case 2: /*Ver Pacote no Início*/
            printf("\n---Ver Pacote no Inicio---\n");
            VerPacoteInicio(fila);
            break;
        case 3: /*Remover Pacote*/
            printf("\n---Remover Pacote---\n");
            if (Dequeue(fila))
            {
                printf("Pacote removido com sucesso!\n");
            }
            break;
        case 4: /*Carregar Dados*/
            printf("\n---Carregar Dados---\n");
            CarregarDados(&fila);
            break;
        case 5: /*Salvar Dados*/
            printf("\n---Salvar Dados---\n");
            SalvarDados(fila);
            break;
        case 6: /*Excluir Fila*/
            printf("\n---Excluir Fila---\n");
            fila = Excluir(fila);
            break;
        case 0: /*Sair*/
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    if (fila != NULL)
    {
        fila = Excluir(fila);
    }
    return 0;
}