#include <stdio.h>

int mdc_diofantino(int a, int b, int *s, int *t);

int inverso_modulo(int a, int b);

int achar_solucao_congruencia(int a, int b, int m);

int main() {
    //scaneando a, b e m:
    int a, b, m;
    scanf("%d %d %d", &a, &b, &m);

    //ax congruente a b (mod m)
    //temos que x congruente a bs (mod m), onde s eh o inverso de a mod m

    //checando se ha solucao:
    //declarando os coeficientes s e t e o mdc(a, m):
    int s, t;
    int mdc_am = mdc_diofantino(a, m, &s, &t);

    //se mdc(a, m) nao divide b, entao nao ha solucao.
    if (b % mdc_am != 0) printf("Nao ha solucao para %dx congruente a %d (mod %d)\n", a, b, m);
    //caso haja solucao:
    else{
        //x eh a solucao. Se x for -1, nao ha solucao (lembrando que queremos x entre 0 e m/mdc(a, m)).
        int x = achar_solucao_congruencia(a/mdc_am, b/mdc_am, m/mdc_am); 

        //printando a solucao (caso exista), ou printa que nao ha solucao (caso nao exista):
        if (x == -1) printf("Nao ha x que satisfaca %dx congruente a%d (mod %d).\n", a*mdc_am, b*mdc_am, m*mdc_am);
        else printf("x = %d satisfaz %dx congruente a %d (mod %d).\n", x, a*mdc_am, b*mdc_am, m*mdc_am);
    }

    return 0;
}

//retorna -1 se nao ha solucao. Caso contrario, retorna a solucao entre 0 e m:
int achar_solucao_congruencia(int a, int b, int m){
    //encontrando o inverso de a (caso exista):
    int inverso_a = inverso_modulo(a, m);
    if (inverso_a == 0) return -1;

    //encontrando a solucao entre 0 e m:
    int solucao = inverso_a*b;

    while (solucao < 0) solucao += m;
    if (solucao > m) solucao = solucao % m;

    return solucao;
}

int inverso_modulo(int a, int b){
    int s, t;
    int MDC = mdc_diofantino(a, b, &s, &t);

    if (MDC != 1) return 0;

    while (s < 0) s += b;
    if (s > b) s = s % b;

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
