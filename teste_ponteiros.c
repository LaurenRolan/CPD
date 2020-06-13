#include <stdio.h>
#include <stdlib.h>

void troca(int *i)
{
    *i += 1;
    troca_mais(i);
}
void troca_mais(int *i)
{
    *i = 8;
}

int main()
{
    int i=3, j;
    troca(&i);
    printf("%d", i);
}
