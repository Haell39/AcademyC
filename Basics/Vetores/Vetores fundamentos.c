#include <stdio.h> // para printf
#include <stdlib.h> // para exit
#include <string.h> // para strcpy
int main()
{
    //* Vetore em C

    int num[5];
    float num2[5];
    char letter[5];
    char name[5][50];
    int values[5] = {10, 20, 30, 40, 50};

    //* Preenchendo vetor name
    for (int i = 0; i < 5; i++)
    {
        printf("Name %d: ", i + 1);
        scanf("%49s", name[i]);
    }

    //* Imprimindo vetor name
    printf("\nNames typed: \n");
    for (int i = 0; i < 5; i++)
    {
        printf("Name %d: %s\n", i + 1, name[i]);
    }

    //* Inicializando vetores, vetor num:
    for (int i = 0; i < 5; i++)
    {
        num[i] = i + 1;
        printf("\nnum[%d] = %d\n", i, num[i]);
    }
    // Ou poderiamos simplesmente atribuir os valores a num manualmente
    // num = {1, 2, 3, 4, 5}; ou desde o principio:
    // int num[5] = {1, 2, 3, 4, 5};

    //* Acessando elementos do vetor:
    values[0] = 70; // modificando o primeiro elemento
    printf("%d", values[1]);

    return 0;
}