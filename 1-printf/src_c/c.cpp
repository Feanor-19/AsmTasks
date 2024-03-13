#include <stdio.h>

int my_printf(const char *str, ...);

int main()
{
    int chars = my_printf( "%%%c%c%c%c%c%c%c%c%c%c", 'F', '1', '9', ' ', 'h', 'e', 'l', 'l', 'o', '!' );

    printf("\nReturn: %d\n", chars);

    chars = printf( "%%%c%c%c%c%c%c%c%c%c%c", 'F', '1', '9', ' ', 'h', 'e', 'l', 'l', 'o', '!' );
    printf("\nPrintfReturn: %d\n", chars);

    return 0;
}