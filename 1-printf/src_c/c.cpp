#include <stdio.h>

int my_printf(const char *str, ...);

int main()
{
    const char *test1 = "Test 1!";
    const char *test2 = "%%%c%c%c%c%c%c%c%c%c%c";  
    const char *test3 = "%x";

    int chars = 0;

    chars = my_printf( test1 );
    printf("\nMyReturn: %d\n", chars);
    chars = printf( test1 );
    printf("\nPrintfReturn: %d\n\n", chars);

    chars = my_printf( test2, 'F', '1', '9', ' ', 'h', 'e', 'l', 'l', 'o', '!' );
    printf("\nMyReturn: %d\n", chars);
    chars = printf( test2, 'F', '1', '9', ' ', 'h', 'e', 'l', 'l', 'o', '!' );
    printf("\nPrintfReturn: %d\n\n", chars);

    chars = my_printf( test3, 19 );
    printf("\nMyReturn: %d\n", chars);
    chars = printf( test3, 19 );
    printf("\nPrintfReturn: %d\n\n", chars);


    return 0;
}