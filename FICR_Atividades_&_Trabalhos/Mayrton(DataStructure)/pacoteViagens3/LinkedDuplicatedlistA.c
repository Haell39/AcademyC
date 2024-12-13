/*Adapted from original recipe management system*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista {
    ListaNo *prim;
};

struct listaNo {
    int id;
    char destino[50];
    float precoPacote;
    int duracaoDias;
    char tipoTransporte;
    ListaNo *prox;
    ListaNo *ant;
};

/* Function Prototypes */
int AtualizarPacotes(Lista*, int, ListaNo);
ListaNo* BuscarPacotes(Lista*, int);
Lista* Criar();
int InserirPacote(Lista*, ListaNo);
int InserirPacoteID(Lista*, ListaNo);
int InserirPacoteInicio(Lista*, ListaNo);
int Tamanho(Lista*);
void ImprimirPacote(Lista *lista);
int RemoverPacote(Lista*, int);
Lista* Excluir(Lista* lista);
void OrdemInversa(Lista *lista);
void SalvarDados(Lista *lista, const char *nomeArquivo);
void CarregarDados(Lista *lista, const char *nomeArquivo);

int main() {
    Lista *lista = Criar();
    int opcao;
    ListaNo pacote;

    do {
        printf("\n---Menu de Pacotes de Viagem---\n");
        printf("[1] Inserir Pacote\n");
        printf("[2] Inserir Pacote no Inicio\n");
        printf("[3] Inserir Pacote no ID Especifico\n");
        printf("[4] Imprimir Pacotes\n");
        printf("[5] Buscar Pacote\n");
        printf("[6] Remover Pacote\n");
        printf("[7] Atualizar Pacote\n");
        printf("[8] Salvar Dados\n");
        printf("[9] Carregar Dados\n");
        printf("[10] Excluir Lista\n");
        printf("[11] Ordem Inversa\n");
        printf("[12] Tamanho da Lista\n");
        printf("[0] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: /*Inserir Pacotes*/
                printf("\n---Inserir Pacote---\n");
                printf("|ID: ");
                scanf("%d",&pacote.id);
                printf("|Destino: ");
                scanf("%s",pacote.destino);
                printf("|Preco do Pacote: ");
                scanf("%f",&pacote.precoPacote);
                printf("|Duracao (dias): ");
                scanf("%d",&pacote.duracaoDias);
                printf("|Tipo de Transporte (A-Aviao, B-Onibus): ");
                scanf(" %c",&pacote.tipoTransporte);
                InserirPacote(lista, pacote);
                break;

            case 2: /*Inserir Pacote no Início*/
                printf("\n---Inserir Pacote no Inicio---\n");
                printf("|ID: ");
                scanf("%d",&pacote.id);
                printf("|Destino: ");
                scanf("%s",pacote.destino);
                printf("|Preco do Pacote: ");
                scanf("%f",&pacote.precoPacote);
                printf("|Duracao (dias): ");
                scanf("%d",&pacote.duracaoDias);
                printf("|Tipo de Transporte (A-Aviao, B-Onibus): ");
                scanf(" %c",&pacote.tipoTransporte);
                InserirPacoteInicio(lista, pacote);
                break;

            case 3: /*Inserir Pacote no ID Específico*/
                printf("\n---Inserir Pacote no ID Especifico---\n");
                printf("|ID: ");
                scanf("%d",&pacote.id);
                printf("|Destino: ");
                scanf("%s",pacote.destino);
                printf("|Preco do Pacote: ");
                scanf("%f",&pacote.precoPacote);
                printf("|Duracao (dias): ");
                scanf("%d",&pacote.duracaoDias);
                printf("|Tipo de Transporte (A-Aviao, B-Onibus): ");
                scanf(" %c",&pacote.tipoTransporte);
                if (InserirPacoteID(lista, pacote)) {
                    printf("Pacote inserido com sucesso!\n");
                } else {
                    printf("ID ja existe!\n");
                }
                break;

            case 4: /*Imprimir Pacotes*/
                printf("\n---Imprimir Pacotes---\n");
                ImprimirPacote(lista);
                break;

            case 5: /*Buscar Pacotes*/
                printf("\n---Buscar Pacotes---\n");
                printf("Digite o ID do pacote: ");
                scanf("%d", &pacote.id);
                ListaNo *resultado = BuscarPacotes(lista, pacote.id);
                if (resultado) {
                    printf("|ID: %d\n", resultado->id);
                    printf("|Destino: %s\n", resultado->destino);
                    printf("|Preco do Pacote: R$%.2f\n", resultado->precoPacote);
                    printf("|Duracao: %d dias\n", resultado->duracaoDias);
                    printf("|Tipo de Transporte: %s\n", 
                        resultado->tipoTransporte == 'A' ? "Aviao" : 
                        (resultado->tipoTransporte == 'B' ? "Onibus" : "Desconhecido"));
                } else {
                    printf("Pacote nao encontrado!\n");
                }
                break;

            case 6: /*Remover Pacotes*/
                printf("\n---Remover Pacotes---\n");
                printf("Digite o ID do pacote: ");
                scanf("%d", &pacote.id);
                if (RemoverPacote(lista, pacote.id)) {
                    printf("Pacote removido com sucesso!\n");
                } else {
                    printf("Pacote nao encontrado!\n");
                }
                break;

            case 7: /*Atualizar Pacotes*/
                printf("\n---Atualizar Pacotes---\n");
                printf("Digite o ID do pacote: ");
                scanf("%d", &pacote.id);
                printf("|Destino: ");
                scanf("%s",pacote.destino);
                printf("|Preco do Pacote: ");
                scanf("%f",&pacote.precoPacote);
                printf("|Duracao (dias): ");
                scanf("%d",&pacote.duracaoDias);
                printf("|Tipo de Transporte (A-Aviao, B-Onibus): ");
                scanf(" %c",&pacote.tipoTransporte);
                if (AtualizarPacotes(lista, pacote.id, pacote)) {
                    printf("Pacote atualizado com sucesso!\n");
                } else {
                    printf("Pacote nao encontrado!\n");
                }
                break;

            case 8: /*Salvar*/
                printf("\n---Salvar Pacotes---\n");
                SalvarDados(lista, "pacotes.txt");
                printf("Dados salvos com sucesso!\n");
                break;

            case 9: /*Carregar*/
                printf("\n---Carregar Pacotes---\n");
                CarregarDados(lista, "pacotes.txt");
                printf("Dados carregados com sucesso!\n");
                break;

            case 10: /*Excluir Lista*/
                printf("\n---Excluir Lista---\n");
                lista = Excluir(lista);
                printf("Lista excluida com sucesso!\n");
                break;

            case 11: /*Imprimir Pacotes Ordem Inversa*/
                printf("\n---Ordem Inversa---\n");
                OrdemInversa(lista);
                break;

            case 12: /*Tamanho da Lista*/
                printf("\n---Tamanho da Lista---\n");
                printf("Total de pacotes: %d\n", Tamanho(lista));
                break;

            case 0: /*Sair*/
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

/* Function implementations remain the same as in the original code, 
   with only variable/struct names changed from 'receita' to 'pacote' */

/* Função para inserir pacote no início */
int InserirPacoteInicio(Lista *lista, ListaNo valor) {
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));

    if (nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }

    *nova = valor;
    nova->prox = lista->prim;
    nova->ant = NULL;

    if (lista->prim != NULL) {
        lista->prim->ant = nova;
    }
    lista->prim = nova;

    return 1;
}

/* Função para inserir pacote no ID específico */
int InserirPacoteID(Lista *lista, ListaNo valor) {
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));

    if (nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }

    *nova = valor;
    nova->prox = NULL;
    nova->ant = NULL;

    if (lista->prim == NULL) {
        lista->prim = nova;
        return 1;
    }

    ListaNo *p;
    for (p = lista->prim; p != NULL; p = p->prox) {
        if (p->id == valor.id) {
            free(nova);
            return 0;
        }
        if (p->id > valor.id) {
            nova->prox = p;
            nova->ant = p->ant;
            if (p->ant != NULL) {
                p->ant->prox = nova;
            } else {
                lista->prim = nova;
            }
            p->ant = nova;
            return 1;
        }
    }

    p->prox = nova;
    nova->ant = p;

    return 1;
}

/* Função para calcular o tamanho da lista */
int Tamanho(Lista *lista) {
    int count = 0;
    ListaNo *p;

    if (lista == NULL) {
        return count;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        count++;
    }

    return count;
}

/*Função para atualizar pacotes*/
int AtualizarPacotes(Lista *lista, int busca, ListaNo novoPacote) {
    ListaNo *p;

    if (lista == NULL) {
        printf("A lista nao foi criada!\n");
        return 0;
    }

    if (lista->prim == NULL) {
        printf("A lista esta vazia!\n");
        return 0;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        if (p->id == busca) {
            *p = novoPacote;
            return 1;
        }
    }
    return 0;
}

/*Função para buscar pacotes*/
ListaNo* BuscarPacotes(Lista *lista, int valor) {
    ListaNo *p;
    
    if (lista == NULL) {
        printf("A lista nao foi criada!\n");
        return NULL;
    }

    if (lista->prim == NULL) {
        printf("A lista esta vazia!\n");
        return NULL;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        if (p->id == valor) {
            return p;
        }
    }
    return NULL;
}

/* Função para criar uma lista*/
Lista* Criar() {
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    
    if (nova == NULL) {
        printf("Sem espaco!\n");
        return NULL;
    }
    nova->prim = NULL;

    return nova;
}

/* Função para excluir uma lista*/
Lista* Excluir(Lista* lista) {
    ListaNo *aux;

    if (lista == NULL) {
        printf("A lista nao foi criada!\n");
        return NULL;
    }

    while (lista->prim != NULL) {
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        free(aux);
    }

    free(lista);
    
    return NULL;
}

/* Função Para inserir Pacotes*/
int InserirPacote(Lista *lista, ListaNo valor) {
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));

    if (nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }

    *nova = valor;
    nova->prox = NULL;
    nova->ant = NULL;

    if (lista->prim == NULL) {
        lista->prim = nova;
        return 1;
    }

    ListaNo *p;
    for (p = lista->prim; p->prox != NULL; p = p->prox);
    
    p->prox = nova;
    nova->ant = p;

    return 1;
}

/*Função para imprimir os pacotes*/
void ImprimirPacote(Lista *lista) {
    ListaNo *p;

    if (lista == NULL) {
        printf("A lista nao foi criada!\n");
        return;
    }

    if (lista->prim == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        printf("|ID: %d\n", p->id);
        printf("|Destino: %s\n", p->destino);
        printf("|Preco do Pacote: R$%.2f\n", p->precoPacote);
        printf("|Duracao: %d dias\n", p->duracaoDias);
        printf("|Tipo de Transporte: %s\n\n", 
            p->tipoTransporte == 'A' ? "Aviao" : 
            (p->tipoTransporte == 'B' ? "Onibus" : "Desconhecido"));
    }
}

int RemoverPacote(Lista *lista, int id) {
    if (lista == NULL || lista->prim == NULL) {
        printf("Lista vazia ou nao criada!\n");
        return 0;
    }

    ListaNo *p = lista->prim;

    while (p != NULL) {
        if (p->id == id) {
            if (p->ant == NULL) { // É o primeiro nó
                lista->prim = p->prox;
                if (lista->prim != NULL) {
                    lista->prim->ant = NULL;
                }
            } else {
                p->ant->prox = p->prox;
                if (p->prox != NULL) {
                    p->prox->ant = p->ant;
                }
            }
            free(p);
            return 1;
        }
        p = p->prox;
    }
    return 0;
}

void SalvarDados(Lista *lista, const char *nomeArquivo) {
    if (lista == NULL || lista->prim == NULL) {
        printf("Lista vazia ou nao criada!\n");
        return;
    }

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    ListaNo *p;
    for (p = lista->prim; p != NULL; p = p->prox) {
        char tipoTransporteStr[10];
        if (p->tipoTransporte == 'A' || p->tipoTransporte == 'a')
            strcpy(tipoTransporteStr, "(Aviao)");
        else if (p->tipoTransporte == 'B' || p->tipoTransporte == 'b')
            strcpy(tipoTransporteStr, "(Onibus)");
        else
            strcpy(tipoTransporteStr, "(N/A)");

        fprintf(arquivo, "ID: %d | Destino: %s | Preco: R$ %.2f | Duracao: %d dias | Transporte: %c %s\n",
                p->id, p->destino, p->precoPacote, p->duracaoDias, p->tipoTransporte, tipoTransporteStr);
    }

    fclose(arquivo);
}

void CarregarDados(Lista *lista, const char *nomeArquivo) {
    if (lista == NULL) {
        printf("Lista nao criada!\n");
        return;
    }

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Arquivo nao encontrado!\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        ListaNo pacote;
        if (sscanf(linha, "ID: %d | Destino: %[^|] | Preco: R$ %f | Duracao: %d dias | Transporte: %c",
                   &pacote.id, pacote.destino, &pacote.precoPacote,
                   &pacote.duracaoDias, &pacote.tipoTransporte) == 5) {
            InserirPacote(lista, pacote);
        }
    }

    fclose(arquivo);
}

/*Função para imprimir os pacotes na ordem inversa*/
void OrdemInversa(Lista *lista) {
    ListaNo *p;

    if (lista == NULL) {
        printf("A lista nao foi criada!\n");
        return;
    }

    if (lista->prim == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }

    // Vai até o último nó
    for (p = lista->prim; p->prox != NULL; p = p->prox);

    // Imprime do último ao primeiro
    while (p != NULL) {
        printf("|ID: %d\n", p->id);
        printf("|Destino: %s\n", p->destino);
        printf("|Preco do Pacote: R$%.2f\n", p->precoPacote);
        printf("|Duracao: %d dias\n", p->duracaoDias);
        printf("|Tipo de Transporte: %s\n\n", 
            p->tipoTransporte == 'A' ? "Aviao" : 
            (p->tipoTransporte == 'B' ? "Onibus" : "Desconhecido"));
        p = p->ant;
    }
}
