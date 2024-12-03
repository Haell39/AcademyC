#include <stdio.h>

// Define a struct to hold a person's data
struct great
{
    char name[50];
    int age;
    // Structs can store multiple variables of different types.
};

int main()
{
    struct great g1, g2;

    // Input for the first person
    printf("Enter the name of the first person: ");
    scanf("%s", g1.name); // No & needed for strings
    printf("Enter the age of the first person: ");
    scanf("%d", &g1.age); // Correct format specifier for integers

    // Input for the second person
    printf("Enter the name of the second person: ");
    scanf("%s", g2.name);
    printf("Enter the age of the second person: ");
    scanf("%d", &g2.age);

    // Output the names and ages
    printf("Names: %s, %s\n", g1.name, g2.name);
    printf("Ages: %d, %d\n", g1.age, g2.age);

    return 0;
}
