/*
uu Leitura e Impressão de Valores em um Vetor:
oo Crie um programa que leia 5 números inteiros e os armazene em um vetor. Depois, imprima esses números.
*/

#include <stdio.h>

int main()
{
    int nums[5];
    for (int i = 0; i < 5; i++)
    {
        printf("Enter the number %d: ", i + 1);
        scanf("%d", &nums[i]);
    }

    printf("The numbers entered are: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", nums[i]);
    }

    return 0;
}
