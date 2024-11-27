#include <stdio.h>

int main()
{
    int i = 7;
    do
    {
        printf("Hello, Java++!\n");
        i++;
    } while (i < 5);

    int k = 0;
    do
    {
        printf("%d * 8 = %d\n", k, k * 8);
        k++;
    } while (k <= 10);

    return 0;
}