#include <stdio.h>

int main()
{

    int a[5] = {7,8,9,6,40};
    int *ptr;
    ptr = a;
    for (int i = 0; i < 5; i++)
    {
        printf("%d \n", *ptr++);
    }



    return 0;
}