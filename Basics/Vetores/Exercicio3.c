/*
uu Maior e Menor Valor em um Vetor:
oo Crie um programa que encontre e imprima o maior e o menor valor em um vetor.
*/

#include <stdio.h>

int main()
{
    int nums[5], maior, menor;

    for (int i = 0; i < 5; i++)
    {
        printf("Enter the number %d:", i + 1);
        scanf("%d", &nums[i]);
    }

    maior = menor = nums[0]; //inicializa o maior e o menor com o primeiro valor

    for (int i = 1; i < 5; i++) {
        if (nums[i] > maior) maior = nums[i];
        if (nums[i] < menor) menor = nums[i];
    }

    printf("The largest number is: %d\n", maior);
    printf("The smallest number is: %d\n", menor);
    return 0;
}
