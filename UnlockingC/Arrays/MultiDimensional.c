#include <stdio.h>

int main()
{
    // Declaração de uma matriz 2x2 chamada 'a'
    int a[2][2];
    printf("Enter the values rows and columns of the array A: \n");

    // Loop para ler os valores da matriz 'a'
    for (int i = 0; i < 2; i++) // Itera sobre as linhas da matriz
    {
        for (int k = 0; k < 2; k++) // Itera sobre as colunas da matriz
        {
            // Lê um valor inteiro e armazena na posição a[i][k]
            scanf("%d", &a[i][k]);
            // Exibe o valor lido para confirmação
            printf("a[%d][%d] = %d \n", i, k, a[i][k]);
        }
    }

    // Declaração de duas matrizes 3x3 chamadas 'b' e 'c'
    int b[3][3], c[3][3];
    printf("Enter the values for the sum of arrays B and C: \n");

    // Loop para ler os valores da matriz 'b'
    for (int k = 0; k < 3; k++) // Itera sobre as linhas da matriz
    {
        for (int j = 0; j < 3; j++) // Itera sobre as colunas da matriz
        {
            // Lê um valor inteiro e armazena na posição b[k][j]
            scanf("%d", &b[k][j]);
            // Exibe o valor lido para confirmação
            printf("b[%d][%d] = %d \n", k, j, b[k][j]);
        }
    }

    // Loop para ler os valores da matriz 'c'
    for (int k = 0; k < 3; k++) // Itera sobre as linhas da matriz
    {
        for (int j = 0; j < 3; j++) // Itera sobre as colunas da matriz
        {
            // Lê um valor inteiro e armazena na posição c[k][j]
            scanf("%d", &c[k][j]);
            // Exibe o valor lido para confirmação
            printf("c[%d][%d] = %d \n", k, j, c[k][j]);
        }
    }

    printf("\n"); // Imprime uma linha em branco para melhor legibilidade

    // Loop para calcular e exibir a soma das matrizes 'b' e 'c'
    for (int k = 0; k < 3; k++) // Itera sobre as linhas
    {
        for (int j = 0; j < 3; j++) // Itera sobre as colunas
        {
            // Exibe a soma dos elementos correspondentes de 'b' e 'c'
            printf("b[%d][%d] + c[%d][%d] = %d \n",
                   k, j, k, j, b[k][j] + c[k][j]);
            // Nota: Trocar o sinal se quiser subtrair em vez de somar
        }
    }

    printf("\n");

    int a[3][2] = {{1, 2}, {3, 4}, {5, 6}};

    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 2; j++)
        {

            printf("Element at a[%i][%i]: ", i, j);

            printf("%d\n", a[i][j]); // acessando o elemento na linha i, coluna j e como nao há \n no printf acima entao o resultado é displayado logo após os :
        }
    }

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}