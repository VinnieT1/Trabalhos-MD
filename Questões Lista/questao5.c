#include <stdio.h>

int calcular_mdc (int a, int b)
{
    if (a % b == 0) return b;
    else 
    {
        b = a % b;
        a = b;
        
        calcular_mdc(a,b);
    }
    
}


int main ()
{
    int a,b;
    printf("Digite 2 números para calcular o MDC: \n");
    scanf("%d %d", &a,&b);
    printf("Resultado: %d\n", calcular_mdc(a,b));
    return 0;
}