#include <stdio.h>

void add(); // declaration ---------------2. second here
void sub();
void mult();
int main ()
{
    add(); // Call ------------------ 1. Compiler read here first
    mult();
    sub();
            // >> Call the functions in the order of the definition !



    return 0;
}

void add() // Definition -------------3. finally here
{
    // int a = 10, b = 15; 
    int a, b;
    printf("Enter two numbers to be added: ");
    scanf("%d %d", &a, &b);
    printf("Sum is %d \n", a + b);

}
void mult() // Definition 
{
    int a, b;
    printf("Enter two numbers for multiplication: ");
    scanf("%d %d", &a, &b);
    printf("Multiplication is %d \n", a * b);

}
void sub() // Definition 
{
    int a, b;
    printf("Enter two numbers to be subtraceted: ");
    scanf("%d %d", &a, &b);
    printf("Subtraction is %d", a - b);

}