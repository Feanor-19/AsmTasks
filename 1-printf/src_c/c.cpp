#include <stdio.h>

int my_printf(const char *str, ...);

int main()
{
    const char *test1 = "Test 1!\nNew line!\nAgain new line...\n";
    const char *test2 = "%%%c%c%c%c%c%c%c%c%c%c";  
    const char *test3 = "%x, %x, %x, %x, %x, %x, %x, %x";
    const char *test4 = "%o, %o, %o, %o, %o, %o, %o, %o";
    const char *test5 = "%d, %d, %d, %d, %d, %d, %d, %d";
    const char *test6 = "%s";
    int chars = 0;

    chars = my_printf( test1 );
    printf("\nMyReturn: %d\n", chars);
    chars = printf   ( test1 );
    printf("\nPrintfReturn: %d\n\n", chars);

    chars = my_printf( test2, 'F', '1', '9', ' ', 'h', 'e', 'l', 'l', 'o', '!' );
    printf("\nMyReturn: %d\n", chars);
    chars = printf   ( test2, 'F', '1', '9', ' ', 'h', 'e', 'l', 'l', 'o', '!' );
    printf("\nPrintfReturn: %d\n\n", chars);

    chars = my_printf( test3, 19, 0, 1, 45, 19, 119, 19, 19 );
    printf("\nMyReturn: %d\n", chars);
    chars = printf   ( test3, 19, 0, 1, 45, 19, 119, 19, 19 );
    printf("\nPrintfReturn: %d\n\n", chars);

    chars = my_printf( "%b, %b, %b, %b, %b, %b, %b, %b", 
                        7, 0, 1, -1, 19, 0b1010101, 0b1111111, 0b10000000000000000000000001 );
    printf("\nMyReturn: %d\n\n", chars);

    chars = my_printf( test4, 19, 0, -1, 45, 19, -119, 19, 19 );
    printf("\nMyReturn: %d\n", chars);
    chars = printf   ( test4, 19, 0, -1, 45, 19, -119, 19, 19 );
    printf("\nPrintfReturn: %d\n\n", chars);

    chars = my_printf( test5, 19, 0, -1, 45, 19, -119, 19, 19 );
    printf("\nMyReturn: %d\n", chars);
    chars = printf   ( test5, 19, 0, -1, 45, 19, -119, 19, 19 );
    printf("\nPrintfReturn: %d\n\n", chars);

    chars = my_printf( test6, "Test String!\nSecond...\nThird!\n" );
    printf("\nMyReturn: %d\n", chars);
    chars = printf   ( test6, "Test String!\nSecond...\nThird!\n" );
    printf("\nPrintfReturn: %d\n\n", chars);

    return 0;
}