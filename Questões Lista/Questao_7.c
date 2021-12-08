#include <stdio.h>

int mdc_diofantino(int a, int b, int *s, int *t);

int main() {
    //scaneando a e b;
    int a, b;
    scanf("%d %d", &a, &b);

    //o inverso de a mod b existe se e somente se mdc(a, b) = 1.
    //Seja s o inverso de a mod b. s eh tal que a*s + b*t = 1; (s e t sao inteiros).
	
    //definindo os coeficientes s e t:
    int s, t;

    //encontrando o valor de s e o MDC (explicacao da funcao na resolucao da questao 6):
    int MDC = mdc_diofantino(a, b, &s, &t);
	
	//verificando se MDC != 1:
	if (MDC != 1){
		printf("Nao ha inverso de %d mod %d.\n", a, b);
		return 0;
	}
	
	//caso MDC == 1, o programa continua...
    //escolhendo o inverso de a mod b entre 0 e b:
    while (s < 0) s += b;
    if (s >= b) s = s % b;

    printf("O inverso de %d mod %d eh: %d\n", a, b, s);

    return 0;
}

//explicacao na resolucao da questao 6.
int mdc_diofantino(int a, int b, int *s, int *t) {
    if(b == 0) {
        *s = 1;
        *t = 0;
        return a;
    }
  
    int s1, t1;
  
    int MDC = mdc_diofantino(b, a % b, &s1, &t1);
    *s = t1;
    *t = s1 - t1*(a/b);
    return MDC;
}
