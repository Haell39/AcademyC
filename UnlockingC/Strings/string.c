#include <stdio.h>
#include <string.h>

/*
 * This program demonstrates basic string manipulation in C using functions from <string.h>.
 * It shows concatenation, copying, and comparison of strings.
 */

int main()
{
    // Declare and initialize two strings for concatenation
    char str1[50] = "You are";
    char str2[50] = " Now learning JSTS";

    // Concatenate str2 to the end of str1
    strcat(str1, str2);
    puts(str1); // Display the concatenated result: "You are Now learning JSTS"

    // Copy the content of str1 into str2
    strcpy(str2, str1);
    puts(str2); // Display str2, which is now the same as str1

    // Copy the content of str2 back into str1
    strcpy(str1, str2);
    puts(str1); // Display str1 again (no visible change)

    // Declare and initialize strings for comparison
    char str3[50] = "Hello, World!";
    char str4[50] = "Hello, C!";

    // Compare str3 and str4
    int result = strcmp(str3, str4);
    printf("Comparison result (str3 vs str4): %d\n", result);
    /*
     * << strcmp() returns:
     * - 0 if the strings are identical
     * - A positive value if the first mismatching character in str3 has a greater ASCII value than in str4
     * - A negative value if the first mismatching character in str3 has a lesser ASCII value than in str4
     *
     * Here, the result will be positive because the character 'W' in str3 has a higher ASCII value
     * than the character 'C' in str4.
     */

    // ^^ Additional comparisons for better examples
    char str5[50] = "ABC";
    char str6[50] = "ABD";
    int result2 = strcmp(str5, str6);
    printf("Comparison result (str5 vs str6): %d\n", result2);
    /*
     * Here, the result will be negative because 'C' in str5 has a lesser ASCII value than 'D' in str6.
     */

    char str7[50] = "Same";
    char str8[50] = "Same";
    int result3 = strcmp(str7, str8);
    printf("Comparison result (str7 vs str8): %d\n", result3);
    /*
     * Here, the result will be 0 because both strings are identical.
     */

    return 0; // End the program
}
