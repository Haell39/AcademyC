#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // Tamanho máximo da lista

// Estrutura do elemento Carro
typedef struct {
    int id;
    char marca[50];
    char modelo[50];
    int ano;
    char cor[20];
    float quilometragem;
    float valor;
    char categoria[30];
    char disponibilidade; // 'D' para disponível, 'N' para não disponível
} Carro;

// Estrutura da lista
typedef struct {
    Carro carros[MAX];
    int tamanho;
} Lista;

// Função para criar a lista
Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->tamanho = 0;
    return lista;
}

// Função para verificar se a lista está cheia
int estaCheia(Lista* lista) {
    return lista->tamanho == MAX;
}

// Função para inserir um elemento no final da lista
void inserirElemento(Lista* lista, Carro carro) {
    if (!estaCheia(lista)) {
        lista->carros[lista->tamanho] = carro;
        lista->tamanho++;
    } else {
        printf("Erro: Lista cheia!\n");
    }
}

// Função para inserir um elemento no início da lista
void inserirElementoInicio(Lista* lista, Carro carro) {
    if (!estaCheia(lista)) {
        int i;
        for (i = lista->tamanho; i > 0; i--) {
            lista->carros[i] = lista->carros[i - 1];
        }
        lista->carros[0] = carro;
        lista->tamanho++;
    } else {
        printf("Erro: Lista cheia!\n");
    }
}

// Função para inserir um elemento em uma posição específica
void inserirElementoID(Lista* lista, Carro carro, int pos) {
    if (!estaCheia(lista) && pos >= 0 && pos <= lista->tamanho) {
        int i;
        for (i = lista->tamanho; i > pos; i--) {
            lista->carros[i] = lista->carros[i - 1];
        }
        lista->carros[pos] = carro;
        lista->tamanho++;
    } else {
        printf("Erro: Posição inválida ou lista cheia!\n");
    }
}

// Função para listar todos os elementos
void listarElementos(Lista* lista) {
    int i;
    for (i = 0; i < lista->tamanho; i++) {
        Carro carro = lista->carros[i];
        printf("ID: %d | Marca: %s | Modelo: %s | Ano: %d | Cor: %s | Quilometragem: %.2f | Valor: %.2f | Categoria: %s | Disponibilidade: %c\n",
               carro.id, carro.marca, carro.modelo, carro.ano, carro.cor, carro.quilometragem, carro.valor, carro.categoria, carro.disponibilidade);
    }
}

// Função para remover um elemento por posição
void removerElemento(Lista* lista, int pos) {
    if (pos >= 0 && pos < lista->tamanho) {
        int i;
        for (i = pos; i < lista->tamanho - 1; i++) {
            lista->carros[i] = lista->carros[i + 1];
        }
        lista->tamanho--;
    } else {
        printf("Erro: Posição inválida!\n");
    }
}

// Função para atualizar um elemento
void atualizar(Lista* lista, int pos, Carro novoCarro) {
    if (pos >= 0 && pos < lista->tamanho) {
        lista->carros[pos] = novoCarro;
    } else {
        printf("Erro: Posição inválida!\n");
    }
}

// Função para buscar um elemento por ID
Carro* buscarElemento(Lista* lista, int id) {
    int i;
    for (i = 0; i < lista->tamanho; i++) {
        if (lista->carros[i].id == id) {
            return &lista->carros[i];
        }
    }
    printf("Carro com ID %d não encontrado!\n", id);
    return NULL;
}

// Função para retornar o tamanho da lista
int tamanho(Lista* lista) {
    return lista->tamanho;
}

// Função para excluir a lista
void excluirLista(Lista* lista) {
    free(lista);
}

// Função para carregar dados do arquivo
void carregarDados(Lista* lista) {
    FILE* file = fopen("carros.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Carro temp;
    while (fscanf(file, "%d\n", &temp.id) != EOF) {
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

// Função para salvar os dados no arquivo
// Função para salvar os dados no arquivo no formato solicitado
void salvarDados(Lista* lista) {
    FILE* file = fopen("carros.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    
    int i;
    for (i = 0; i < lista->tamanho; i++) {
        Carro carro = lista->carros[i];
        fprintf(file, "ID: %d | Marca: %s | Modelo: %s | Ano: %d | Cor: %s | Quilometragem: %.2f | Valor: %.2f | Categoria: %s | Disponibilidade: %c\n",
                carro.id, carro.marca, carro.modelo, carro.ano, carro.cor,
                carro.quilometragem, carro.valor, carro.categoria, carro.disponibilidade);
    }

    fclose(file);
}


// Função principal
int main() {
    Lista* lista = criarLista();
    int opcao;
    Carro carroTemp;
    int pos;

    do {
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

        switch (opcao) {
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
                inserirElementoID(lista, carroTemp, pos);
                break;
            case 4:
                listarElementos(lista);
                break;
            case 5:
                printf("Digite a posição para remover: ");
                scanf("%d", &pos);
                removerElemento(lista, pos);
                break;
            case 6:
                printf("Digite a posição do carro para atualizar: ");
                scanf("%d", &pos);
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
                break;
            case 7:
                printf("Digite o ID do carro para buscar: ");
                scanf("%d", &pos);
                Carro* encontrado = buscarElemento(lista, pos);
                if (encontrado != NULL) {
                    printf("Carro encontrado: ID: %d | Marca: %s | Modelo: %s | Ano: %d | Cor: %s | Quilometragem: %.2f | Valor: %.2f | Categoria: %s | Disponibilidade: %c\n",
                           encontrado->id, encontrado->marca, encontrado->modelo, encontrado->ano,
                           encontrado->cor, encontrado->quilometragem, encontrado->valor,
                           encontrado->categoria, encontrado->disponibilidade);
                }
                break;
            case 8:
                printf("Tamanho da lista: %d\n", tamanho(lista));
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
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    excluirLista(lista);
    return 0;
}