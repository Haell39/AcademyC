#include <stdio.h>
#include <stdlib.h>

// Function prototype for a pointer-to-function example
void greet();
void addNumbers(int *x, int *y);
void swapNumbers(int *a, int *b);

int main()
{
    // 1. Basic Pointer and Pointer Arithmetic
    int num = 42;
    int *p = &num;
    printf("Basic Pointer Operations:\n");
    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", (void *)&num);
    printf("Pointer p holds address: %p\n", (void *)p);
    printf("Value at address stored in p: %d\n\n", *p);

    // Pointer Arithmetic
    int nums[] = {10, 20, 30, 40};
    int *ptr = nums; // Points to the first element of nums
    printf("Pointer Arithmetic:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Address: %p, Value: %d\n", (void *)ptr, *ptr);
        ptr++; // Moves to the next element
    }
    printf("\n");

    // 2. Pointers with Strings
    char str[] = "Hello, Pointers!";
    char *str_ptr = str;
    printf("Pointer with Strings:\n");
    while (*str_ptr != '\0')
    {
        printf("%c", *str_ptr);
        str_ptr++;
    }
    printf("\n\n");

    // 3. Pointers and Functions
    int x = 5, y = 10;
    printf("Pointers and Functions:\n");
    printf("Before addition: x = %d, y = %d\n", x, y);
    addNumbers(&x, &y); // Passing addresses of x and y
    printf("After addition: x = %d, y = %d\n\n", x, y);

    // Swap numbers using pointers
    printf("Before swap: x = %d, y = %d\n", x, y);
    swapNumbers(&x, &y);
    printf("After swap: x = %d, y = %d\n\n", x, y);

    // 4. Dynamic Memory Allocation
    printf("Dynamic Memory Allocation:\n");
    int *dynArray = (int *)malloc(3 * sizeof(int)); // Allocate memory for 3 integers
    if (dynArray == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < 3; i++)
    {
        dynArray[i] = (i + 1) * 10; // Assign values to the array
    }
    printf("Dynamically allocated array values: ");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", dynArray[i]);
    }
    printf("\n");
    free(dynArray); // Free allocated memory
    printf("Memory freed!\n\n");

    // 5. Pointer to Function
    printf("Pointer to Function:\n");
    void (*funcPtr)(); // Declare a pointer to a function
    funcPtr = greet;
    funcPtr(); // Call the function using the pointer

    return 0;
}

// Function definitions
void addNumbers(int *x, int *y)
{
    *x += *y; // Adds y to x
}

void swapNumbers(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void greet()
{
    printf("Hello from a function pointer!\n");
}
