#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5
#define ARQUIVO "D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens4\\pacotes.txt"

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
    int topo;
    Pacote *elementos;
} Pilha;

/* Funções implementadas */
Pilha *Criar();
Pilha *Excluir(Pilha *);
int Push(Pilha *, Pacote);
void VerTopo(Pilha *);
int Pop(Pilha *);
int EhVazia(Pilha *);
void CarregarDados(Pilha *);
void SalvarDados(Pilha *);

/* Função para criar uma pilha */
Pilha *Criar()
{
    Pilha *novaPilha = (Pilha *)malloc(sizeof(Pilha));
    if (novaPilha == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return NULL;
    }
    novaPilha->topo = 0;
    novaPilha->elementos = (Pacote *)malloc(TAM * sizeof(Pacote));
    if (novaPilha->elementos == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        free(novaPilha);
        return NULL;
    }
    printf("\nPilha criada com sucesso!\n");
    return novaPilha;
}

/* Função para ver se a pilha esta vazia */
int EhVazia(Pilha *pilha)
{
    return pilha->topo == 0;
}

/* Função para carregar dados de pacotes */
void CarregarDados(Pilha *pilha)
{
    FILE *file = fopen(ARQUIVO, "r");
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
            if (Push(pilha, pacote) == 0)
            {
                printf("Pilha cheia, nao foi possivel carregar todos os pacotes!\n");
                break;
            }
        }
    }

    fclose(file);
    printf("Dados carregados com sucesso!\n");
}

/* Função para salvar dados em pacotes */
void SalvarDados(Pilha *pilha)
{
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < pilha->topo; i++)
    {
        Pacote pacote = pilha->elementos[i];
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
    }

    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

/* Função para excluir uma pilha */
Pilha *Excluir(Pilha *pilha)
{
    if (pilha == NULL)
    {
        printf("A pilha nao existe!\n");
        return NULL;
    }
    
    // Libera a memória dos elementos da pilha
    free(pilha->elementos);
    
    // Limpa o conteúdo do arquivo
    FILE *file = fopen(ARQUIVO, "w");
    if (file)
    {
        fclose(file); // Apenas abre e fecha para limpar o conteúdo
    }

    free(pilha);
    printf("Pilha excluida com sucesso!\n");
    return NULL;
}

/* Função para inserir pacotes */
int Push(Pilha *pilha, Pacote novoPacote)
{
    if (pilha == NULL)
    {
        printf("\nA pilha nao foi criada.\n");
        return 0;
    }
    if (pilha->topo < TAM)
    {
        pilha->elementos[pilha->topo] = novoPacote;
        pilha->topo++;
        return 1;
    }
    else
    {
        printf("Pilha cheia!\n");
        return 0;
    }
}

/* Função para ver o topo da pilha */
void VerTopo(Pilha *pilha)
{
    if (pilha == NULL)
    {
        printf("A pilha nao foi criada!\n");
        return;
    }
    if (pilha->topo == 0)
    {
        printf("Pilha vazia!\n");
        return;
    }
    Pacote topo = pilha->elementos[pilha->topo - 1];
    printf("\n|Topo da pilha:");
    printf("\n|ID: %d", topo.id);
    printf("\n|Destino: %s", topo.destino);
    printf("\n|Preco: R$ %.2f", topo.precoPacote);
    printf("\n|Duracao: %d dias", topo.duracaoDias);
    printf("\n|Transporte: %s\n",
           topo.tipoTransporte == 'A' ? "Aviao" : (topo.tipoTransporte == 'B' ? "Onibus" : "N/A"));
}

/* Função para remover pacotes */
int Pop(Pilha *pilha)
{
    if (pilha == NULL)
    {
        printf("A pilha nao foi criada!\n");
        return 0;
    }
    if (pilha->topo == 0)
    {
        printf("Pilha vazia!\n");
        return 0;
    }
    pilha->topo--;
    return 1;
}

int main()
{
    Pilha *minhaPilha = Criar();
    int opcao;
    Pacote novoPacote;

    do
    {
        printf("\n---Menu de Pacotes de Viagem---\n");
        printf("[1] Inserir Pacote\n");
        printf("[2] Ver Pacote no Topo\n");
        printf("[3] Ver se a Pilha esta Vazia\n");
        printf("[4] Remover Pacote do Topo\n");
        printf("[5] Carregar Dados\n");
        printf("[6] Salvar Dados\n");
        printf("[7] Excluir Pilha\n");
        printf("[0] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: /*Inserir Pacotes*/
            printf("\n---Inserir Pacote---\n");
            if (minhaPilha->topo < TAM)
            {
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
                Push(minhaPilha, novoPacote);
            }
            else
            {
                printf("Pilha cheia!\n");
            }
            break;
        case 2: /*Ver Pacote no Topo*/
            printf("\n---Ver Pacote no Topo---\n");
            VerTopo(minhaPilha);
            break;
        case 3: /*Ver se a Pilha está Vazia*/
            printf("\n---Ver se a Pilha esta Vazia---\n");
            if (EhVazia(minhaPilha))
            {
                printf("A pilha esta vazia!\n");
            }
            else
            {
                printf("A pilha nao esta vazia!\n");
            }
            break;
        case 4: /*Remover Pacote*/
            printf("\n---Remover Pacote---\n");
            if (Pop(minhaPilha))
            {
                printf("Pacote removido do topo!\n");
            }
            break;
        case 5: /*Carregar Dados*/
            printf("\n---Carregar Dados---\n");
            CarregarDados(minhaPilha);
            break;
        case 6: /*Salvar Dados*/
            printf("\n---Salvar Dados---\n");
            SalvarDados(minhaPilha);
            break;
        case 7: /*Excluir Pilha*/
            printf("\n---Excluir Pilha---\n");
            minhaPilha = Excluir(minhaPilha);
            break;
        case 0: /*Sair*/
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    if (minhaPilha != NULL)
    {
        minhaPilha = Excluir(minhaPilha);
    }
    return 0;
}