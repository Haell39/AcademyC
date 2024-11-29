#include <stdio.h>
#include <stdlib.h>

/*
 * Advanced Array Concepts in C
 * This code demonstrates the use of dynamic arrays, array of pointers,
 * and multidimensional arrays with pointers.
 */

void printArray(int *arr, int size) {
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void fillArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1; // Fill array with 1, 2, 3, ...
    }
}

int main() {
    // 1. Dynamic array (one-dimensional)
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *dynamicArray = (int *)malloc(n * sizeof(int));
    if (dynamicArray == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    fillArray(dynamicArray, n);
    printArray(dynamicArray, n);

    // Free the dynamically allocated memory
    free(dynamicArray);

    // 2. Array of pointers (useful for jagged arrays)
    int rows = 3;
    int *jaggedArray[3];

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        jaggedArray[i] = (int *)malloc((i + 2) * sizeof(int)); // Variable-sized rows
        if (jaggedArray[i] == NULL) {
            printf("Memory allocation failed for row %d.\n", i);
            return 1;
        }
        for (int j = 0; j < i + 2; j++) {
            jaggedArray[i][j] = (i + 1) * (j + 1);
        }
    }

    // Print the jagged array
    printf("Jagged array elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < i + 2; j++) {
            printf("%d ", jaggedArray[i][j]);
        }
        printf("\n");
    }

    // Free memory for each row
    for (int i = 0; i < rows; i++) {
        free(jaggedArray[i]);
    }

    // 3. Multidimensional array with pointers
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*ptrMatrix)[3] = matrix;

    printf("Accessing multidimensional array with a pointer:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", ptrMatrix[i][j]);
        }
        printf("\n");
    }

    // 4. Passing multidimensional array to a function
    printf("Sum of elements in matrix: %d\n", sumMatrix(matrix, 2, 3));

    return 0;
}

int sumMatrix(int matrix[][3], int rows, int cols) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}
