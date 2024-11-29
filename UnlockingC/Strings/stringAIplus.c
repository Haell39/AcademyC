#include <stdio.h>
#include <string.h>

/*
 * Additional string manipulation examples in C.
 * This file demonstrates length calculation, character search, and tokenization.
 */

int main()
{
    // 1. << Calculate the length of a string using strlen
    char str1[] = "Learning C is fun!";
    printf("The length of str1 is: %lu\n", strlen(str1));
    // strlen() calculates the number of characters in a string excluding the null terminator.

    // 2. << Find a character in a string using strchr
    char *foundChar = strchr(str1, 'C');
    if (foundChar != NULL)
    {
        printf("Character 'C' found at position: %ld\n", foundChar - str1);
        // Subtracts the address of the string start from the found character's address to get its position.
    }
    else
    {
        printf("Character 'C' not found in str1.\n");
    }

    // 3. << Tokenize a string using strtok
    char str2[] = "C,Python,Java,JavaScript";
    printf("Tokens in str2:\n");
    char *token = strtok(str2, ",");
    while (token != NULL)
    {
        printf("- %s\n", token);
        token = strtok(NULL, ",");
    }
    // strtok() splits a string into tokens based on a delimiter (',' in this case).

    // 4. << Reverse a string manually
    char str3[] = "Reverse me!";
    int len = strlen(str3);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str3[i];
        str3[i] = str3[len - 1 - i];
        str3[len - 1 - i] = temp;
    }
    printf("Reversed string: %s\n", str3);
    // This loop swaps characters symmetrically to reverse the string.

    // 5. << Copy a portion of a string using strncpy
    char str4[] = "This is a long string";
    char partialCopy[10];
    strncpy(partialCopy, str4, 9); // Copies first 9 characters
    partialCopy[9] = '\0';         // Ensure null termination
    printf("Partial copy of str4: %s\n", partialCopy);

    // 6. << Compare strings ignoring case (manual implementation)
    char str5[] = "HELLO";
    char str6[] = "hello";
    int result = strcasecmp(str5, str6); // strcasecmp is not standard C, but available in POSIX
    printf("Case-insensitive comparison result: %d\n", result);
    /*
     * strcasecmp() returns:
     * - 0 if strings are equal (ignoring case)
     * - Positive/negative value if they're different
     */

    return 0; // End the program
}
