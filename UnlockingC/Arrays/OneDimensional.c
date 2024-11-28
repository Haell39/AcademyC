#include <stdio.h>

int main()
{
    int a[5] = {1, 2, 3, 4, 5}; // Inicialização do array a

    // Exibindo os valores do array a
    for (int i = 0; i < 5; i++)
    {
        printf("Valores do array a: %d \n", a[i]);
    }

    int b[5]; // declarando o array
    // Coletando valores para o array b
    for (int j = 0; j < 5; j++)
    {
        printf("Digite o valor para o indice %d: ", j);
        scanf("%d", &b[j]);
    }

    // Exibindo todos os valores do array b
    printf("Todos os valores do array b são: \n");
    for (int j = 0; j < 5; j++)
    {
        printf("Valor do indice %d é %d\n", j, b[j]);
    }

    return 0;
}