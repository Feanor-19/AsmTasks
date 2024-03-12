#include <stdio.h>

int my_mul(int a, int b);

int main()
{
    int x = my_mul(2, 3);
    printf( "%d * %d = %d!\n", 2, 3, x );

    return 0;
}