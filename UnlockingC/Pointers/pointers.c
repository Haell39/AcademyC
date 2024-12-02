#include <stdio.h>

int main()

{
    int num = 10;
    int *ptr;
    ptr = &num;

    printf("%d \n", num);  // --> 10
    printf("%d \n", &num); // --> address of num
    printf("%d \n", ptr);  // --> address of num
    printf("%d \n", *ptr); // --> Value inside the pointer (inside the address of num)
    printf("%d \n", &ptr); // --> address of num

    num = 50;
    printf("\n\n");

    printf("%d \n", num);
    printf("%d \n", *ptr);

    return 0;
}