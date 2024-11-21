#include <stdio.h>

int main ()
{
    int a, b, choice;
    printf("Enter the value of a and b: ");
    scanf("%d %d", &a, &b);
    printf("Enter your choice: (1. Addition, 2. Subtraction, 3. Multiplication, 4. Division): ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:{
        printf("a + b = %d", a + b);
        break;
        }

    case 2:{
        printf("a - b = %d", a - b);
        break;
        }

    case 3:
    {
        printf("a * b = %d", a * b);
        break;
    }

    case 4:
    {
        printf("a / b = %d", a / b);
        break;
    }

    default:
    {
        printf("Invalid choice");
        break;

    }
        
    }

    return 0;

}