/*Alunos: Luiz Filipe e Mara Rúbia*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FilaNo filaNo;

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
    filaNo *inicio;
    filaNo *fim;
} Fila;

struct FilaNo
{
    Pacote pacote;
    filaNo *prox;
};

/* Função para criar uma fila */
Fila *Criar()
{
    Fila *novaFila = (Fila *)malloc(sizeof(Fila));
    if (novaFila == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return NULL;
    }
    novaFila->inicio = NULL;
    novaFila->fim = NULL;
    return novaFila;
}

/* Função para inserir pacotes */
int Enqueue(Fila *fila, Pacote novoPacote)
{
    filaNo *novoEspaco = (filaNo *)malloc(sizeof(filaNo));
    if (fila == NULL)
    {
        printf("A fila nao foi criada!\n");
        return 0;
    }
    novoEspaco->pacote = novoPacote;
    novoEspaco->prox = NULL;

    if (fila->inicio == NULL)
    {
        fila->inicio = novoEspaco;
        fila->fim = novoEspaco;
    }
    else
    {
        fila->fim->prox = novoEspaco;
        fila->fim = novoEspaco;
    }
    return 1;
}

/* Função para ver pacote no início */
void VerPacoteInicio(Fila *fila)
{
    if (fila == NULL || fila->inicio == NULL)
    {
        printf("A fila esta vazia!\n");
        return;
    }

    Pacote pacoteInicio = fila->inicio->pacote;
    printf("\n|Pacote no inicio da fila:");
    printf("\n|ID: %d", pacoteInicio.id);
    printf("\n|Destino: %s", pacoteInicio.destino);
    printf("\n|Preco: R$ %.2f", pacoteInicio.precoPacote);
    printf("\n|Duracao: %d dias", pacoteInicio.duracaoDias);
    printf("\n|Transporte: %s\n",
           pacoteInicio.tipoTransporte == 'A' ? "Aviao" : (pacoteInicio.tipoTransporte == 'B' ? "Onibus" : "N/A"));
}

/* Função para remover pacotes */
Pacote Dequeue(Fila *fila)
{
    Pacote pacoteRemovido;
    filaNo *ref;

    if (fila == NULL || fila->inicio == NULL)
    {
        printf("A fila esta vazia!\n");
        return pacoteRemovido;
    }

    ref = fila->inicio;
    pacoteRemovido = ref->pacote;
    fila->inicio = fila->inicio->prox;
    free(ref);
    return pacoteRemovido;
}

/* Função para excluir uma fila */
Fila *Excluir(Fila *fila)
{
    filaNo *ref;

    if (fila == NULL)
    {
        printf("A fila nao existe!\n");
        return NULL;
    }

    while (fila->inicio != NULL)
    {
        ref = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(ref);
    }
    free(fila);
    printf("Fila excluida com sucesso!\n");
    return NULL;
}

/* Função para carregar dados */
void CarregarDados(Fila *fila)
{
    FILE *file = fopen("D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens6\\pacotes.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), file) != NULL)
    {
        Pacote pacote;
        if (sscanf(linha, "ID: %d | Destino: %[^|] | Preco: R$ %f | Duracao: %d dias | Transporte: %c",
                   &pacote.id, pacote.destino, &pacote.precoPacote,
                   &pacote.duracaoDias, &pacote.tipoTransporte) == 5)
        {
            Enqueue(fila, pacote);
        }
    }
    fclose(file);
    printf("Dados carregados com sucesso!\n");
}

/* Função para salvar dados */
void SalvarDados(Fila *fila)
{
    FILE *file = fopen("D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens6\\pacotes.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    filaNo *atual = fila->inicio;
    while (atual != NULL)
    {
        char tipoTransporteStr[10];
        if (atual->pacote.tipoTransporte == 'A' || atual->pacote.tipoTransporte == 'a')
            strcpy(tipoTransporteStr, "(Aviao)");
        else if (atual->pacote.tipoTransporte == 'B' || atual->pacote.tipoTransporte == 'b')
            strcpy(tipoTransporteStr, "(Onibus)");
        else
            strcpy(tipoTransporteStr, "(N/A)");

        fprintf(file, "ID: %d | Destino: %s | Preco: R$ %.2f | Duracao: %d dias | Transporte: %c %s\n",
                atual->pacote.id, atual->pacote.destino, atual->pacote.precoPacote,
                atual->pacote.duracaoDias, atual->pacote.tipoTransporte, tipoTransporteStr);
        atual = atual->prox;
    }
    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

int main()
{
    Fila *fila = Criar();
    if (fila == NULL)
        return 1;

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
            Dequeue(fila);
            printf("Pacote removido com sucesso!\n");
            break;
        case 4: /*Carregar Dados*/
            printf("\n---Carregar Dados---\n");
            CarregarDados(fila);
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