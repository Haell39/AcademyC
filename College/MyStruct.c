#include <stdio.h>
#include <string.h>

// Definindo a estrutura Ebook
struct Ebook {
    int id;                // Número inteiro
    char titulo[100];       // Texto
    char genero[50];        // Texto
    char autor[100];        // Texto
    int ano_publicacao;     // Número inteiro
    float preco;            // Número real
    char formato;           // Caractere (P = PDF, E = EPUB, M = MOBI)
};

int main() {
    struct Ebook ebook;  // Declarando uma variável do tipo Ebook

    // Recebendo os dados do Ebook
    printf("Digite o ID do Ebook: ");
    scanf("%d", &ebook.id);

    printf("Digite o título do Ebook: ");
    scanf(" %[^\n]s", ebook.titulo);  // O espaço antes do % é para evitar problemas com o buffer

    printf("Digite o gênero do Ebook: ");
    scanf(" %[^\n]s", ebook.genero);

    printf("Digite o autor do Ebook: ");
    scanf(" %[^\n]s", ebook.autor);

    printf("Digite o ano de publicação: ");
    scanf("%d", &ebook.ano_publicacao);

    printf("Digite o preço do Ebook: ");
    scanf("%f", &ebook.preco);

    // Receber e validar o formato do Ebook (P para PDF, E para EPUB, M para MOBI)
    do {
        printf("Digite o formato do Ebook (P para PDF, E para EPUB, M para MOBI): ");
        scanf(" %c", &ebook.formato);  // O espaço antes do %c é para evitar problemas com o buffer
    } while (ebook.formato != 'P' && ebook.formato != 'E' && ebook.formato != 'M');

    // Exibindo os dados recebidos
    printf("\nDados do Ebook:\n");
    printf("ID: %d\n", ebook.id);
    printf("Título: %s\n", ebook.titulo);
    printf("Gênero: %s\n", ebook.genero);
    printf("Autor: %s\n", ebook.autor);
    printf("Ano de Publicação: %d\n", ebook.ano_publicacao);
    printf("Preço: %.2f\n", ebook.preco);

    // Exibindo o formato do Ebook com base no caractere
    switch (ebook.formato) {
        case 'P':
            printf("Formato: PDF\n");
            break;
        case 'E':
            printf("Formato: EPUB\n");
            break;
        case 'M':
            printf("Formato: MOBI\n");
            break;
        default:
            printf("Formato inválido!\n");
    }

    return 0;
}
