#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definicao da estrutura para Pacote de Viagem */
typedef struct pacote
{
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
} Pacote;

/* ^^ Aqui é a estrutura do nó da lista */
typedef struct listaNo
{
    Pacote *pacote;
    struct listaNo *prox;
} ListaNo;

typedef struct lista
{
    ListaNo *prim;
} Lista;

/* ^^ ^^ Aqui sao as funcões da lista */
int atualizarPacote(Lista *, int, Pacote *);
ListaNo *buscarPacote(Lista *, int);
Lista *criarLista();
int inserirPacote(Lista *, Pacote *);
void imprimirPacotes(Lista *);
int removerPacote(Lista *, int);
Lista *excluirLista(Lista *);
int salvarLista(Lista *);
int carregarLista(Lista *);

int main()
{
    Lista *lista = NULL;
    int opcao;
    // Um while com switch pro menu:
    do {
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

        switch(opcao) {
            case 1: {
                if (lista != NULL) {
                    printf("Lista ja existe!\n");
                } else {
                    lista = criarLista();
                    if (lista != NULL) {
                        printf("Lista criada com sucesso!\n");
                        carregarLista(lista);
                    }
                }
                break;
            }
            case 2: {
                if (lista == NULL) {
                    printf("Crie a lista primeiro!\n");
                    break;
                }
                Pacote novoPacote;
                printf("Digite o ID do pacote: ");
                scanf("%d", &novoPacote.id);
                getchar(); // Limpa o buffer do \n
                printf("Digite o destino: ");
                fgets(novoPacote.destino, 49, stdin);
                novoPacote.destino[strcspn(novoPacote.destino, "\n")] = '\0';
                
                printf("Digite o preco: ");
                scanf("%f", &novoPacote.precoPacote);
                printf("Digite a duracao (dias): ");
                scanf("%d", &novoPacote.duracaoDias);
                printf("Digite o tipo de transporte (A/B): ");
                scanf(" %c", &novoPacote.tipoTransporte);

                if(inserirPacote(lista, &novoPacote)) {
                    printf("Pacote inserido com sucesso!\n");
                }
                break;
            }
            case 3: {
                if (lista == NULL) {
                    printf("Crie a lista primeiro!\n");
                    break;
                }
                int id;
                printf("Digite o ID do pacote a ser removido: ");
                scanf("%d", &id);
                if(removerPacote(lista, id)) {
                    printf("Pacote removido com sucesso!\n");
                }
                break;
            }
            case 4: {
                if (lista == NULL) {
                    printf("Crie a lista primeiro!\n");
                    break;
                }
                int id;
                printf("Digite o ID do pacote a ser buscado: ");
                scanf("%d", &id);
                ListaNo *resultado = buscarPacote(lista, id);
                if(resultado != NULL) {
                    printf("Pacote encontrado:\n");
                    printf("ID: %d, Destino: %s, Preco: R$ %.2f, Duracao: %d dias, Transporte: %c\n",
                           resultado->pacote->id, resultado->pacote->destino, 
                           resultado->pacote->precoPacote, resultado->pacote->duracaoDias, 
                           resultado->pacote->tipoTransporte);
                }
                break;
            }
            case 5: {
                if (lista == NULL) {
                    printf("Crie a lista primeiro!\n");
                    break;
                }
                imprimirPacotes(lista);
                break;
            }
            case 6: {
                if (lista == NULL) {
                    printf("Crie a lista primeiro!\n");
                    break;
                }
                Pacote pacoteAtualizado;
                printf("Digite o ID do pacote a ser atualizado: ");
                scanf("%d", &pacoteAtualizado.id);
                getchar(); // Limpa o buffer do \n
                printf("Digite o novo destino: ");
                fgets(pacoteAtualizado.destino, 49, stdin);
                pacoteAtualizado.destino[strcspn(pacoteAtualizado.destino, "\n")] = '\0';
                
                printf("Digite o novo preco: ");
                scanf("%f", &pacoteAtualizado.precoPacote);
                printf("Digite a nova duracao (dias): ");
                scanf("%d", &pacoteAtualizado.duracaoDias);
                printf("Digite o novo tipo de transporte (A/B): ");
                scanf(" %c", &pacoteAtualizado.tipoTransporte);

                if(atualizarPacote(lista, pacoteAtualizado.id, &pacoteAtualizado)) {
                    printf("Pacote atualizado com sucesso!\n");
                }
                break;
            }
            case 7: {
                if (lista == NULL) {
                    printf("Lista ja esta vazia!\n");
                } else {
                    salvarLista(lista);
                    lista = excluirLista(lista);
                    printf("Lista excluida com sucesso!\n");
                }
                break;
            }
            case 8: {
                if (lista == NULL) {
                    printf("Crie a lista primeiro!\n");
                    break;
                }
                salvarLista(lista);
                printf("Dados salvos com sucesso!\n");
                break;
            }
            case 9:
                if (lista != NULL) {
                    salvarLista(lista);
                    lista = excluirLista(lista);
                }
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 9);

    return 0;
}

/* ^^ atualizar os dados de um pacote na lista */
int atualizarPacote(Lista *lista, int id, Pacote *novoPacote)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista nao foi criada\n");
        return 0;
    }

    ListaNo *p;

    /* ^^ percorrer a lista procurando o pacote com o id fornecido */
    for (p = lista->prim; p != NULL; p = p->prox)
    {
        if (p->pacote->id == id)
        {
            *(p->pacote) = *novoPacote;
            return 1;
        }
    }

    return 0;
}

/* ^^ funcao que vai buscar um pacote pelo seu id */
ListaNo *buscarPacote(Lista *lista, int id)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista nao foi criada ou esta vazia\n");
        return NULL;
    }

    ListaNo *p;

    for (p = lista->prim; p != NULL; p = p->prox)
    {
        if (p->pacote->id == id)
        {
            return p;
        }
    }

    return NULL;
}

/* ^^ criar uma nova lista */
Lista *criarLista()
{
    Lista *nova = (Lista *)malloc(sizeof(Lista));

    if (nova == NULL)
    {
        printf("Sem espaco\n");
        return NULL;
    }

    nova->prim = NULL;

    return nova;
}

/* ^^ funcao que exclui a lista e libera memória alocada */
Lista *excluirLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada\n");
        return NULL;
    }

    ListaNo *aux;

    while (lista->prim != NULL)
    {
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        free(aux->pacote);
        free(aux);
    }

    free(lista);

    return NULL;
}

/* ^^ adiciona um pacote na lista */
int inserirPacote(Lista *lista, Pacote *pacote)
{
    ListaNo *novaNo = (ListaNo *)malloc(sizeof(ListaNo));

    if (novaNo == NULL)
    {
        printf("Sem espaco\n");
        return 0;
    }

    novaNo->pacote = (Pacote *)malloc(sizeof(Pacote));

    if (novaNo->pacote == NULL)
    {
        printf("Sem espaco\n");
        free(novaNo);
        return 0;
    }

    *(novaNo->pacote) = *pacote;
    novaNo->prox = NULL;

    if (lista->prim == NULL)
    {
        lista->prim = novaNo;
    }
    else
    {
        ListaNo *p = lista->prim;

        while (p->prox != NULL)
        {
            p = p->prox;
        }

        p->prox = novaNo;
    }

    return 1;
}

/* ^^ todos os pacotes da lista */
void imprimirPacotes(Lista *lista)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista esta vazia\n");
        return;
    }

    ListaNo *p;

    /* ^^ percorrer a lista e imprimir todos os dados dos pacotes */
    for (p = lista->prim; p != NULL; p = p->prox)
    {
        printf("ID: %d, Destino: %s, Preco: %.2f, Duracao: %d dias, Transporte: %c\n",
               p->pacote->id, p->pacote->destino, p->pacote->precoPacote,
               p->pacote->duracaoDias, p->pacote->tipoTransporte);
    }
}

/* ^^ remover um pacote da lista pelo id */
int removerPacote(Lista *lista, int id)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista nao foi criada ou esta vazia\n");
        return 0;
    }

    ListaNo *p = lista->prim;

    if (p->pacote->id == id)
    {
        lista->prim = p->prox;
        free(p->pacote);
        free(p);
        return 1;
    }

    /* ^^ percorrer a lista procurando o pacote que vai ser removido */
    while (p->prox != NULL)
    {
        if (p->prox->pacote->id == id)
        {
            ListaNo *aux = p->prox;
            p->prox = aux->prox;
            free(aux->pacote);
            free(aux);
            return 1;
        }

        p = p->prox;
    }

    return 0;
}

/* ^^ funcao par salvar a lista em um arquivo */
int salvarLista(Lista *lista)
{
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista esta vazia ou nao foi criada\n");
        return 0;
    }

    FILE *arquivo = fopen("D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens2\\pacotes.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    ListaNo *p;

    for (p = lista->prim; p != NULL; p = p->prox)
    {
        char tipoTransporteStr[10];
        if (p->pacote->tipoTransporte == 'A' || p->pacote->tipoTransporte == 'a')
            strcpy(tipoTransporteStr, "(Aviao)");
        else if (p->pacote->tipoTransporte == 'B' || p->pacote->tipoTransporte == 'b')
            strcpy(tipoTransporteStr, "(Onibus)");
        else
            strcpy(tipoTransporteStr, "(N/A)");

        fprintf(arquivo, "ID: %d | Destino: %s | Preco: R$ %.2f | Duracao: %d dias | Transporte: %c %s\n",
                p->pacote->id, p->pacote->destino,
                p->pacote->precoPacote,
                p->pacote->duracaoDias,
                p->pacote->tipoTransporte,
                tipoTransporteStr);
    }

    fclose(arquivo);
    return 1;
}

/* ^^ carregar os pacotes de um arquivo para a lista */
int carregarLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("A lista nao foi criada\n");
        return 0;
    }

    FILE *arquivo = fopen("D:\\GitHub Desktop\\C_CodeLab\\FICR_Atividades_&_Trabalhos\\Mayrton(DataStructure)\\pacoteViagens2\\pacotes.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        Pacote *pacote = (Pacote *)malloc(sizeof(Pacote));
        if (sscanf(linha, "ID: %d | Destino: %[^|] | Preco: R$ %f | Duracao: %d dias | Transporte: %c",
                   &pacote->id, pacote->destino, &pacote->precoPacote,
                   &pacote->duracaoDias, &pacote->tipoTransporte) == 5)
        {
            // Remove espaços em branco no final do destino
            char *end = pacote->destino + strlen(pacote->destino) - 1;
            while (end > pacote->destino && isspace(*end)) end--;
            *(end + 1) = '\0';
            
            inserirPacote(lista, pacote);
        }
        free(pacote);
    }

    fclose(arquivo);
    return 1;
}