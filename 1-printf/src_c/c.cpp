#include <stdio.h>

int my_printf(const char *str);

int main()
{
    int chars = my_printf( "Hello 123!" );

    printf("\nReturn: %d\n", chars);

    return 0;
}