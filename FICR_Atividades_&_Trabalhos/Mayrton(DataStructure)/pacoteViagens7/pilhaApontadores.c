#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens7\\pacotes.txt"

typedef struct
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte; // 'A' para aéreo, 'B' para terrestre
} Viagem;

typedef struct No
{
    Viagem viagem;
    struct No *proximo;
} No;

typedef struct
{
    No *topo;
} Pilha;

void verificarPilhaVazia(Pilha *pilha)
{
    if (ehVazia(pilha))
    {
        printf("A pilha esta vazia! \n");
    }
    else
    {
        printf("A pilha nao esta vazia, ha viagens na pilha. \n");
    }
}

Pilha *criarPilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha)
    {
        pilha->topo = NULL;
    }
    return pilha;
}

int ehVazia(Pilha *pilha)
{
    return pilha == NULL || pilha->topo == NULL;
}

int push(Pilha *pilha, Viagem viagem)
{
    if (!pilha)
        return 0;
    if (viagem.id <= 0 || (viagem.tipoTransporte != 'A' && viagem.tipoTransporte != 'B'))
    {
        printf("Dados invalidos para a viagem.\n");
        return 0;
    }

    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo)
        return 0;

    novoNo->viagem = viagem;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
    return 1;
}

int pop(Pilha *pilha)
{
    if (ehVazia(pilha))
        return 0;

    No *temp = pilha->topo;
    pilha->topo = temp->proximo;
    free(temp);
    return 1;
}

Viagem *verTopo(Pilha *pilha)
{
    if (ehVazia(pilha))
        return NULL;
    return &(pilha->topo->viagem);
}

/* Função para excluir uma pilha que tava faltando */
void excluirPilha(Pilha *pilha)
{
    while (!ehVazia(pilha))
    {
        pop(pilha);
    }
    free(pilha);
    printf("Pilha e todos os elementos foram excluídos com sucesso.\n");
}

void salvarDados(Pilha *pilha)
{
    if (!pilha)
        return;

    FILE *file = fopen(ARQUIVO, "w");
    if (!file)
    {
        printf("Erro ao salvar os dados no arquivo.\n");
        return;
    }

    Pilha temp;
    temp.topo = NULL;

    while (!ehVazia(pilha))
    {
        Viagem *viagem = verTopo(pilha);
        fprintf(file, "ID: %d | Destino: %s | Preco: R$ %.2f | Duracao: %d dias | Transporte: %c\n",
                viagem->id, viagem->destino, viagem->precoPacote, viagem->duracaoDias, viagem->tipoTransporte);
        push(&temp, *viagem);
        pop(pilha);
    }

    while (!ehVazia(&temp))
    {
        push(pilha, *verTopo(&temp));
        pop(&temp);
    }

    fclose(file);
    printf("Dados salvos com sucesso.\n");
}

void carregarDados(Pilha *pilha)
{
    if (!pilha)
        return;

    FILE *file = fopen(ARQUIVO, "r");
    if (!file)
    {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    while (1)
    {
        Viagem viagem;
        // Lê a linha inteira
        char buffer[200];
        if (fgets(buffer, sizeof(buffer), file) == NULL)
            break; // Sai do loop se não houver mais linhas

        // Lê os dados do buffer
        if (sscanf(buffer, "ID: %d | Destino: %49[^|] | Preco: R$ %f | Duracao: %d dias | Transporte: %c",
                   &viagem.id, viagem.destino, &viagem.precoPacote, &viagem.duracaoDias, &viagem.tipoTransporte) == 5)
        {
            push(pilha, viagem);
        }
    }

    fclose(file);
    printf("Dados carregados com sucesso.\n");
}

void exibirViagem(Viagem *viagem)
{
    if (!viagem)
        return;
    printf("ID: %d\n", viagem->id);
    printf("Destino: %s\n", viagem->destino);
    printf("Preco do Pacote: %.2f\n", viagem->precoPacote);
    printf("Duracao (dias): %d\n", viagem->duracaoDias);
    printf("Tipo de Transporte: %c\n", viagem->tipoTransporte);
}

void listarViagens(Pilha *pilha)
{
    if (ehVazia(pilha))
    {
        printf("A pilha esta vazia.\n");
        return;
    }

    No *atual = pilha->topo;
    while (atual)
    {
        exibirViagem(&atual->viagem);
        printf("----------------------\n");
        atual = atual->proximo;
    }
}

int main()
{
    Pilha *pilha = NULL;
    int opcao;

    // Verifica se o arquivo existe e não está vazio
    FILE *file = fopen(ARQUIVO, "r");
    if (file)
    {
        fseek(file, 0, SEEK_END); // Move o ponteiro para o final do arquivo
        if (ftell(file) > 0)      // Verifica se o tamanho do arquivo é maior que 0
        {
            pilha = criarPilha(); // Cria a pilha
            carregarDados(pilha); // Carrega os dados do arquivo
        }
        fclose(file); // Fecha o arquivo
    }

    do
    {
        printf("\nMenu:\n");
        printf("1. Criar pilha\n");
        printf("2. Inserir viagem\n");
        printf("3. Remover viagem do topo\n");
        printf("4. Ver viagem do topo\n");
        printf("5. Listar todas as viagens\n");
        printf("6. Salvar dados no arquivo\n");
        printf("7. Carregar dados do arquivo\n");
        printf("8. Verificar se a pilha esta vazia\n");
        printf("9. Excluir pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao != 1 && opcao != 8 && opcao != 0 && !pilha)
        {
            printf("\nVoce precisa criar a pilha antes de realizar outras operacoes.\n");
            continue;
        }

        switch (opcao)
        {
        case 1:
            if (!pilha)
            {
                pilha = criarPilha();
                if (pilha)
                {
                    printf("Pilha criada com sucesso!\n");
                }
                else
                {
                    printf("Erro ao criar a pilha.\n");
                }
            }
            else
            {
                printf("A pilha ja foi criada.\n");
            }
            break;

        case 2:
        {
            Viagem viagem;
            printf("Digite o ID da viagem: ");
            scanf("%d", &viagem.id);
            printf("Digite o destino da viagem: ");
            getchar(); // Limpa o buffer do newline
            fgets(viagem.destino, sizeof(viagem.destino), stdin);
            viagem.destino[strcspn(viagem.destino, "\n")] = 0; // Remove o newline
            printf("Digite o preco do pacote: ");
            scanf("%f", &viagem.precoPacote);
            printf("Digite a duracao em dias: ");
            scanf("%d", &viagem.duracaoDias);
            printf("Tipo de Transporte (A-Aviao, B-Onibus): ");
            scanf(" %c", &viagem.tipoTransporte);

            if (push(pilha, viagem))
            {
                printf("Viagem inserida com sucesso!\n");
            }
            else
            {
                printf("Erro ao inserir a viagem.\n");
            }
            break;
        }

        case 3:
            if (pop(pilha))
            {
                printf("Viagem removida com sucesso.\n");
            }
            else
            {
                printf("Erro ao remover a viagem ou pilha vazia.\n");
            }
            break;

        case 4:
        {
            Viagem *viagem = verTopo(pilha);
            if (viagem)
            {
                printf("Dados da viagem no topo:\n");
                exibirViagem(viagem);
            }
            else
            {
                printf("A pilha esta vazia.\n");
            }
            break;
        }

        case 5:
            listarViagens(pilha);
            break;

        case 6:
            salvarDados(pilha);
            break;

        case 7:
            carregarDados(pilha);
            break;

        case 8:
            verificarPilhaVazia(pilha);
            break;

        case 9:
            if (pilha)
            {
                excluirPilha(pilha);
                pilha = NULL;
                printf("Pilha excluida com sucesso.\n");
            }
            else
            {
                printf("A pilha ja esta vazia.\n");
            }
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    if (pilha)
    {
        excluirPilha(pilha);
    }

    return 0;
}
