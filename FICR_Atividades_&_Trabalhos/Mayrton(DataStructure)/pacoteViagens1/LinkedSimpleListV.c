/******************************************************************
 * Nome: Lista com vetores                                        *
 * Descricao: Implementacao de lista com uso de vetores (array).  *
 *            Esse codigo possui as principais operacoes da       *
 *            lista, como:                                        *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Rafael Andrade                                          *
 * Ultima alteracao: 13/12/2024                                   *
 ******************************************************************/

// ** OBS: Tirei todos os caracteres especiais e acentos para nao dar conflito com o compilador do C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5 // Define o tamanho

/* Aq é a definicao da estrutura para Pacote de Viagem */
typedef struct
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
} Pacote;

/* Agora definindo a estrutura da Lista */
typedef struct
{
    int tamanho;       // Quantidade de pacotes na lista
    Pacote *elementos; // Vetor de Pacotes
} Lista;

/* Funcões implementadas listadas aq abaixo */
int atualizarElemento(Lista *, int, Pacote);
int buscarElemento(Lista *, int);
Lista *criarLista();
Lista *excluirLista(Lista *);
void imprimirElementos(Lista *);
int inserirElemento(Lista *, Pacote);
int removerElemento(Lista *, int);
void carregarDados(Lista *);
void salvarDados(Lista *);

/* Funcao principal */
int main()
{
    Lista *lista = NULL;
    int opcao;

    do
    {
        printf("\n=== Menu de Operacoes da Lista ===\n");
        printf("1. Criar lista\n");
        printf("2. Inserir viagem\n");
        printf("3. Remover viagem\n");
        printf("4. Buscar viagem\n");
        printf("5. Mostrar viagens\n");
        printf("6. Atualizar viagem\n");
        printf("7. Excluir lista\n");
        printf("8. Salvar dados\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Aqui vai o menu com switch case:
        switch (opcao)
        {
        case 1:
        {
            if (lista != NULL)
            {
                printf("Lista ja existe!\n");
            }
            else
            {
                lista = criarLista();
                if (lista != NULL)
                {
                    printf("Lista criada com sucesso!\n");
                    carregarDados(lista);
                }
            }
            break;
        }
        case 2:
        {
            if (lista == NULL)
            {
                printf("Crie a lista primeiro!\n");
                break;
            }
            Pacote novoPacote;
            printf("Digite o ID do pacote: ");
            scanf("%d", &novoPacote.id);
            getchar(); // Limpa o buffer do \n
            printf("Digite o destino: ");
            fgets(novoPacote.destino, 49, stdin);
            // Remove o \n do final da string
            novoPacote.destino[strcspn(novoPacote.destino, "\n")] = '\0';
            
            printf("Digite o preco: ");
            scanf("%f", &novoPacote.precoPacote);
            printf("Digite a duracao (dias): ");
            scanf("%d", &novoPacote.duracaoDias);
            printf("Digite o tipo de transporte (A/B): ");
            scanf(" %c", &novoPacote.tipoTransporte);

            if (inserirElemento(lista, novoPacote))
            {
                printf("Pacote inserido com sucesso!\n");
            }
            break;
        }
        case 3:
        {
            if (lista == NULL)
            {
                printf("Crie a lista primeiro!\n");
                break;
            }
            int id;
            printf("Digite o ID do pacote a ser removido: ");
            scanf("%d", &id);
            if (removerElemento(lista, id))
            {
                printf("Pacote removido com sucesso!\n");
            }
            break;
        }
        case 4:
        {
            if (lista == NULL)
            {
                printf("Crie a lista primeiro!\n");
                break;
            }
            int id;
            printf("Digite o ID do pacote a ser buscado: ");
            scanf("%d", &id);
            int index = buscarElemento(lista, id);
            if (index != -1)
            {
                Pacote p = lista->elementos[index];
                printf("Pacote encontrado:\n");
                printf("ID: %d, Destino: %s, Preco: %.2f, Duracao: %d dias, Transporte: %c\n",
                       p.id, p.destino, p.precoPacote, p.duracaoDias, p.tipoTransporte);
            }
            break;
        }
        case 5:
        {
            if (lista == NULL)
            {
                printf("Crie a lista primeiro!\n");
                break;
            }
            imprimirElementos(lista);
            break;
        }
        case 6:
        {
            if (lista == NULL)
            {
                printf("Crie a lista primeiro!\n");
                break;
            }
            Pacote pacoteAtualizado;
            printf("Digite o ID do pacote a ser atualizado: ");
            scanf("%d", &pacoteAtualizado.id);
            getchar(); // Limpa o buffer do \n
            printf("Digite o novo destino: ");
            fgets(pacoteAtualizado.destino, 49, stdin);
            // Remove o \n do final da string
            pacoteAtualizado.destino[strcspn(pacoteAtualizado.destino, "\n")] = '\0';
            
            printf("Digite o novo preco: ");
            scanf("%f", &pacoteAtualizado.precoPacote);
            printf("Digite a nova duracao (dias): ");
            scanf("%d", &pacoteAtualizado.duracaoDias);
            printf("Digite o novo tipo de transporte (A/B): ");
            scanf(" %c", &pacoteAtualizado.tipoTransporte);

            if (atualizarElemento(lista, pacoteAtualizado.id, pacoteAtualizado))
            {
                printf("Pacote atualizado com sucesso!\n");
            }
            break;
        }
        case 7:
        {
            if (lista == NULL)
            {
                printf("Lista ja esta vazia!\n");
            }
            else
            {
                salvarDados(lista);
                lista = excluirLista(lista);
                printf("Lista excluida com sucesso!\n");
            }
            break;
        }
        case 8:
        {
            if (lista == NULL)
            {
                printf("Crie a lista primeiro!\n");
                break;
            }
            salvarDados(lista);
            printf("Dados salvos com sucesso!\n");
            break;
        }
        case 9:
            if (lista != NULL)
            {
                salvarDados(lista);
                lista = excluirLista(lista);
            }
            printf("Programa encerrado!\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 9);

    return 0;
}

/* Funcao que cria a lista */
Lista *criarLista()
{
    Lista *nova = (Lista *)malloc(sizeof(Lista)); // Aloca memoria para a nova lista
    if (nova == NULL)
    {
        printf("Erro ao criar a lista.\n");
        return NULL; // Vai retorna NULL se nao conseguir alocar memoria
    }

    nova->tamanho = 0;                                        // inicializa o tamanho da lista como 0
    nova->elementos = (Pacote *)malloc(TAM * sizeof(Pacote)); // aloca memoria para os pacotes
    if (nova->elementos == NULL)                              //
    {
        printf("Erro ao alocar memoria para elementos.\n");
        free(nova);  // Libera memoria já alocada para a lista
        return NULL; // denovo vai retorna NULL se nao conseguir alocar memoria
    }
    return nova;
}

/* Funcao para excluir a lista */
Lista *excluirLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada.\n");
        return NULL; // Retorna NULL se a lista nao existe
    }
    free(lista->elementos); // Libera memoria dos elementos da lista
    free(lista);            // Libera memoria da lista (da propria lista)
    return NULL;            // Aqui retorna NULL, mas é pelo fato de indicar que a lista foi excluida, ou pelo menos é oq eu entendi(anotacões caderno)
}

/* Funcao para imprimir os pacotes */
void imprimirElementos(Lista *lista)
{
    if (lista == NULL || lista->tamanho == 0)
    {
        printf("Lista vazia ou nao criada.\n"); // Mensagem se a lista estiver vazia ou nao existir
        return;
    }
    for (int i = 0; i < lista->tamanho; ++i)
    {
        Pacote p = lista->elementos[i];
        printf("ID: %d, Destino: %s, Preco: %.2f, Duracao: %d dias, Transporte: %c\n",
               p.id, p.destino, p.precoPacote, p.duracaoDias, p.tipoTransporte);
    }
}

/* Funcao para inserir um pacote */
int inserirElemento(Lista *lista, Pacote pacote)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada.\n");
        return 0; // se lista nao existe
    }

    if (lista->tamanho >= TAM)
    {
        // Aqui é a melhor parte e onde mais deu erro pra mim, aqui é onde aumenta a capacidade da lista se necessário usando realloc
        lista->elementos = realloc(lista->elementos, (lista->tamanho + TAM) * sizeof(Pacote));
        if (lista->elementos == NULL)
        {
            printf("Erro ao alocar mais memoria para elementos.\n");
            return 0; // Retorna 0 se falhar ao aumentar a capacidade
        }
    }
    // acredito com base nas minhas anotacões aq eu poderia atualizar o ponteiro: lista->elementos = temp; mas em time que ta ganhando nao se mexe, se rodou rodou
    lista->elementos[lista->tamanho] = pacote;
    lista->tamanho++;
    return 1; // O retorno 1 indica que a remocao foi bem-sucedida, diferente de como foi utilizado anteriormente no inicio do codigo
}

/* Funcao para remover um pacote */
int removerElemento(Lista *lista, int id)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada.\n");
        return 0; // 0 se nao existe
    }

    for (int i = 0; i < lista->tamanho; ++i)
    {
        if (lista->elementos[i].id == id)
        {
            for (int j = i; j < lista->tamanho - 1; ++j)
            {
                // Move os pacotes subsequentes uma posicao para frente
                lista->elementos[j] = lista->elementos[j + 1];
            }
            lista->tamanho--; // Decrementa o tamanho da lista apos remocao
            return 1;         // Retorna 1 indicando que o pacote foi removido com sucesso
        }
    }

    printf("Elemento nao encontrado.\n");
    return 0;
}

/* Funcao para carregar dados do arquivo */
void carregarDados(Lista *lista)
{
    FILE *file = fopen("D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens1\\pacotes.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Pacote p;
    char linha[256];
    while (fgets(linha, sizeof(linha), file) != NULL)
    {
        // Extrair informações usando sscanf
        if (sscanf(linha, "ID: %d | Destino: %[^|] | Preco: R$ %f | Duracao: %d dias | Transporte: %c",
                   &p.id, p.destino, &p.precoPacote, &p.duracaoDias, &p.tipoTransporte) == 5)
        {
            // Remove espaços em branco no final do destino
            char *end = p.destino + strlen(p.destino) - 1;
            while (end > p.destino && isspace(*end)) end--;
            *(end + 1) = '\0';
            
            inserirElemento(lista, p);
        }
    }
    fclose(file);
}

/* Funcao para salvar dados no arquivo */
void salvarDados(Lista *lista)
{
    FILE *file = fopen("D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens1\\pacotes.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao salvar arquivo.\n");
        return;
    }

    for (int i = 0; i < lista->tamanho; ++i)
    {
        Pacote p = lista->elementos[i];
        char tipoTransporteStr[10];
        if (p.tipoTransporte == 'A' || p.tipoTransporte == 'a')
            strcpy(tipoTransporteStr, "(Aviao)");
        else if (p.tipoTransporte == 'B' || p.tipoTransporte == 'b')
            strcpy(tipoTransporteStr, "(Onibus)");
        else
            strcpy(tipoTransporteStr, "(N/A)");

        fprintf(file, "ID: %d | Destino: %s | Preco: R$ %.2f | Duracao: %d dias | Transporte: %c %s\n", 
               p.id, p.destino, p.precoPacote, p.duracaoDias, p.tipoTransporte, tipoTransporteStr);
    }
    fclose(file);
}

/* Funcao para buscar um elemento por ID */
int buscarElemento(Lista *lista, int id)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada.\n");
        return -1; // Isso é uma forma de indicar que houve um erro ao tentar buscar um elemento.
    }

    for (int i = 0; i < lista->tamanho; ++i)
    {
        if (lista->elementos[i].id == id)
        {
            return i; // Retorna o indice do pacote encontrado
        }
    }

    printf("Elemento nao encontrado.\n");
    return -1;
}

/* Funcao para atualizar um pacote */
int atualizarElemento(Lista *lista, int id, Pacote pacoteAtualizado)
{
    int index = buscarElemento(lista, id);
    if (index == -1)
    {
        printf("Erro: Elemento com ID %d nao encontrado.\n", id);
        return 0;
    }

    lista->elementos[index] = pacoteAtualizado; // Atualiza o pacote no indice encontrado
    return 1;
}
