#include <stdio.h>

void mdc_diofantino(int a, int b, int *s, int *t);

int calcular_mdc(int a, int b);

int main() {
    //scaneando a e b;
    int a, b;
    scanf("%d %d", &a, &b);

    //o inverso de a mod b existe se e somente se mdc(a, b) = 1.
    //Seja s o inverso de a mod b. s eh tal que a*s + b*t = 1; (s e t sao inteiros).
    
    //verificando se ha inverso (explicacao da funcao na resolucao da questao 5):
    if (calcular_mdc(a, b) != 1){
        printf("Nao existe inverso de %d mod %d.\n", a, b);
        return 0;
    }

    //se o mdc eh 1, existe inverso, entao o programa continua...
    //definindo os coeficientes s e t:
    int s, t;

    //encontrando o valor de s (explicacao da funcao na resolucao da questao 6):
    mdc_diofantino(a, b, &s, &t);

    //escolhendo o inverso de a mod b entre 0 e b:
    while (s < 0) s += b;
    if (s >= b) s = s % b;

    printf("O inverso de %d mod %d eh: %d\n", a, b, s);

    return 0;
}

//explicacao na resolucao da questao 5
int calcular_mdc(int a, int b)
{
    if (b == 0) return a;
    return calcular_mdc(b, a % b);
}

//explicacao na resolucao da questao 6
//transformando a funcao em void, visto que o valor esta sendo obtido com ponteiros.
void mdc_diofantino(int a, int b, int *s, int *t) {
    if(b == 0) {
        *s = 1;
        *t = 0;
        return;
    }
  
    int s1, t1;
  
    mdc_diofantino(b, a % b, &s1, &t1);
    *s = t1;
    *t = s1 - t1*(a/b);
    return;
}
