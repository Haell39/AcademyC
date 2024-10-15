// Estruturas de Controle com Vetores
#include <stdio.h>

int main()
{
    int i;
    int vet[5] = {10, 20, 30, 40, 50};

    for (i = 0; i < 5; i++)
    {
        printf("vet[%d] = %d\n", i, vet[i]);
    }

    return 0;
}