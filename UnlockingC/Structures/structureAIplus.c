#include <stdio.h>
#include <string.h>

// Define a struct to represent a person's basic details
struct person
{
    char name[50];
    int age;
};

// Define a nested struct to represent a person's contact details
struct contactInfo
{
    struct person basicDetails; // Nested struct
    char phoneNumber[15];
    char email[50];
};

// Function to display a person's contact info
void displayContact(struct contactInfo c)
{
    printf("\n--- Contact Information ---\n");
    printf("Name: %s\n", c.basicDetails.name);
    printf("Age: %d\n", c.basicDetails.age);
    printf("Phone: %s\n", c.phoneNumber);
    printf("Email: %s\n", c.email);
    printf("---------------------------\n");
}

// Function to modify a person's email using a pointer
void updateEmail(struct contactInfo *c, const char *newEmail)
{
    strcpy(c->email, newEmail); // Use pointer to update the email
}

int main()
{
    // Example 1: Single struct usage
    struct person p1 = {"Alice", 25};
    printf("Single Struct Example:\n");
    printf("Name: %s, Age: %d\n\n", p1.name, p1.age);

    // Example 2: Array of structs
    struct person team[3] = {{"Bob", 30}, {"Carol", 27}, {"David", 35}};
    printf("Array of Structs Example:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Team Member %d: Name: %s, Age: %d\n", i + 1, team[i].name, team[i].age);
    }
    printf("\n");

    // Example 3: Nested structs and dynamic input
    struct contactInfo c1;
    printf("Enter the name: ");
    scanf("%s", c1.basicDetails.name);
    printf("Enter the age: ");
    scanf("%d", &c1.basicDetails.age);
    printf("Enter the phone number: ");
    scanf("%s", c1.phoneNumber);
    printf("Enter the email: ");
    scanf("%s", c1.email);

    displayContact(c1);

    // Example 4: Update email using a pointer
    updateEmail(&c1, "newemail@example.com");
    printf("\nAfter updating email:\n");
    displayContact(c1);

    return 0;
}
