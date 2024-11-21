#include <stdio.h>

int main()
{
    printf("Enter your age: ");
    int age;
    scanf("%d", &age);
    if (age >= 18)
    {
        printf("You are eligible to vote");
    }
    else
    {
        printf("You are not eligible to vote");
    }
}