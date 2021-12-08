#include <stdio.h>

int calcular_mdc (int a, int b)
{
    /* se b for igual à zero,
       chegamos no caso base
    */
    if (b == 0) return a;
    //o contrário chamamos a recursão:
    return calcular_mdc(b, a % b)
}


int main ()
{
    int a,b;
    printf("Digite 2 números para calcular o MDC: \n");
    scanf("%d %d", &a,&b);
    printf("Resultado: %d\n", calcular_mdc(a,b));
    return 0;
}
