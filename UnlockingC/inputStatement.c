#include <stdio.h>

int main() {
    
    int a, b;
    printf("Enter the values of a and b: ");
    scanf("%d %d", &a, &b);
    printf("The sum is: %d + %d = %d", a, b, a + b);
    printf("\n");
    printf("The difference is: %d - %d = %d", a, b, a - b);

    return 0;
}