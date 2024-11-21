#include <stdio.h>

int main() {
    
    float a, b;
    printf("Enter the values of a and b: ");
    scanf("%f %f", &a, &b);
    printf("The sum is: %f + %f = %.2f", a, b, a + b);
    printf("\n");
    printf("The difference is: %f - %f = %.2f", a, b, a - b);
    printf("\n");
    
    return 0;
}