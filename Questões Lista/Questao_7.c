#include <stdio.h>

int mdc_diofantino(int a, int b, int *s, int *t);

int inverso_modulo(int a, int b);

int main() {
    //scaneando a e b;
    int a, b;
    scanf("%d %d", &a, &b);

    //o inverso de a mod b existe se e somente se mdc(a, b) = 1.
    //Seja s o inverso de a mod b. s eh tal que a*s + b*t = 1; (s e t sao inteiros).

    //achando o inverso de a mod b:
    //explicacao da funcao na declaracao da mesma.
    int inverso = inverso_modulo(a, b);
	
    //printando o inverso caso exista, ou printando que ele nao existe (caso nao exista):
    if (inverso == 0) printf("Nao ha inverso de %d mod %d.\n", a, b);
    else printf("O inverso de %d mod %d eh: %d\n", a, b, inverso);

    return 0;
}

//encontra o inverso de a mod b:
int inverso_modulo(int a, int b){
    //declarando os coeficientes s e t:
    int s, t;

    //encontrando o MDC e achando o valor de s:
    int MDC = mdc_diofantino(a, b, &s, &t);

    //se MDC != 1, entao nao ha inverso; a funcao retorna 0. Caso contrario, a funcao retorna o inverso (entre 0 e b).
    if (MDC != 1) return 0;

    //achando o inverso entre 0 e b:
    while (s < 0) s += b;
    if (s > b) s = s % b;

    //retornando o inverso:
    return s;
}

//explicacao na resolucao da questao 6
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
