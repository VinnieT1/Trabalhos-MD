#include <stdio.h>

int mdc_diofantino(int a, int b, int *s, int *t);

int inverso_modulo(int a, int b);

int achar_solucao_congruencia(int a, int b, int m);

int main() {
    //instrucao para o scanf:
    printf("Digite a (inteiro), b (inteiro), m (m > 1), nesta ordem.\n");

    //scaneando a, b e m:
    int a, b, m;
    scanf("%d %d %d", &a, &b, &m);

    //ax congruente a b (mod m)
    //temos que x congruente a bs (mod m), onde s eh o inverso de a mod m

    //x sera a solucao:
    int x = achar_solucao_congruencia(a, b, m);

    //printa a solucao (caso haja) ou printa que nao tem solucao (caso nao tenha):
    if (x == -1) printf("Nao ha solucao para %dx congruente a %d (mod %d)\n", a, b, m);
    else printf("x = %d satisfaz %dx congruente a %d (mod %d).\n", x, a, b, m);

    return 0;
}

//retorna -1 se nao ha solucao. Caso contrario, retorna a solucao entre 0 e m:
int achar_solucao_congruencia(int a, int b, int m){
    //encontrando a e b positivos e equivalentes, caso a e/ou b sejam negativos:
    int ap = a;
    while (ap < 0) ap += m;
    ap = ap % m;

    int bp = b;
    while (bp < 0) bp += m;
    bp = bp % m;

    //caso a == 0 e b == 0, qualquer x eh solucao.
    //retornando, por conveniencia, a solucao x = 0:
    if (ap == 0 && bp == 0) return 0;

    //checando se ha solucao:
    //declarando os coeficientes s e t e o mdc(a, m):
    int s, t;
    int mdc_am = mdc_diofantino(ap, m, &s, &t);

    //se mdc(a, m) nao divide b, entao nao ha solucao.
    if (bp % mdc_am != 0) return -1;

    //encontrando o inverso de a (caso exista):
    int inverso_a = inverso_modulo(ap/mdc_am, m/mdc_am);
    if (inverso_a == 0) return -1;

    //encontrando a solucao entre 0 e m:
    int solucao = inverso_a*(bp/mdc_am);

    while (solucao < 0) solucao += m;
    if (solucao > m) solucao = solucao % m;

    return solucao;
}

//explicacao na resolucao da questao 7
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
