#include <stdio.h>

int main ()
{
    char name[20];
    char namesurname[20];
    printf("Hello Learners!!\n");
    printf("Enter your name: ");
    scanf("%s", &name);

    // cleanning the buffer to avoid issues with fgets
    while (getchar() != '\n');

    printf("\nEnter your surname: ");
    fgets(namesurname, 20, stdin);


    printf("%s\n", name);
    printf("\t%s", namesurname);


    return 0;

}