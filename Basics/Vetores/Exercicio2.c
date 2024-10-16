/*
*Cálculo da Soma dos Elementos:
?Modifique o programa anterior para calcular e imprimir a soma dos números lidos.
*/

#include <stdio.h>

int main () {
    int nums[5], sum = 0; // variáveis para armazenar os números e a soma
    for (int i = 0; i < 5; i++) {
        printf("Enter the number %d: ", i + 1);
        scanf("%d", &nums[i]);
        sum += nums[i]; //adiciona cada numero à soma
        //note: se fosse o produto: sum *= nums[i]; 
        //note: se fosse a divisão: sum /= nums[i];
        //note: se fosse a subtração: sum -= nums[i];
        
    }

    printf("The sum of the numbers are: %d\n", sum);
    return 0;


}
