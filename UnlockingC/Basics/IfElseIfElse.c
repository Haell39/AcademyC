#include <stdint.h>

int main () {

    int a, b;
    printf("Enter the value of a and b: ");
    scanf("%d %d", &a, &b);
    if (a > b) 
    {
        printf("Value of %i is greater than value of %i", a, b);
    }
    else if (a < b)
    {
        printf("Value of %d is greater than value of %d", b, a);
    }

    else
    {
        printf("Value of %d is equal to value of %d", a, b);
    }

}