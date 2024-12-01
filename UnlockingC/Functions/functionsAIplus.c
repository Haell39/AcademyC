#include <stdio.h>

// << Function prototypes
int add(int a, int b);                   // *Function with parameters and return value
int factorial(int n);                    // *Recursive function
void swap(int *x, int *y);               // *Function with pointers
void printArray(int arr[], int size);    // *Function with array argument
int findMax(int arr[], int size);        // *Function to find maximum in an array

int main() {
    //  1. Function with parameters and return value
    int num1, num2;
    printf("Enter two numbers to add: ");
    scanf("%d %d", &num1, &num2);
    int sum = add(num1, num2);
    printf("The sum of %d and %d is: %d\n\n", num1, num2, sum);

    //  2. Recursive function example
    int n;
    printf("Enter a number to calculate factorial: ");
    scanf("%d", &n);
    printf("Factorial of %d is: %d\n\n", n, factorial(n));

    //  3. Function with pointers (swap example)
    int a, b;
    printf("Enter two numbers to swap: ");
    scanf("%d %d", &a, &b);
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d, b = %d\n\n", a, b);

    //  4. Function with arrays
    int arr[] = {5, 10, 15, 20, 25};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    printArray(arr, size);

    //  5. Finding maximum in an array
    int max = findMax(arr, size);
    printf("The maximum value in the array is: %d\n", max);

    return 0;
}

// 1. ^^ Function with parameters and return value
int add(int a, int b) {
    return a + b;
}

// 2. ^^ Recursive function example
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;  // Base case
    } else {
        return n * factorial(n - 1);  // Recursive case
    }
}

// 3. ^^ Function with pointers (swap example)
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 4. ^^ Function with array argument
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 5. ^^ Finding maximum in an array
int findMax(int arr[], int size) {
    int max = arr[0]; // Assume the first element is the largest
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
