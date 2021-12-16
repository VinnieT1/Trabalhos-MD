#include <stdio.h>
#include <stdlib.h>

int achar_solucao_congruencia(int a, int b, int m);
int inverso_modulo(int a, int b);
int mdc_diofantino(int a, int b, int *s, int *t);
int teorema_resto_chines(int n);

/*
Variável ERRO:
Se 0:
  Tudo ok.
Se 1:
  O problema não pode ser resolvido pelo
  teorema do resto chinês ou não tem solução
  ....
*/
int ERRO = 0;

int main() {
  printf("Digite o número de congruências: ");
  int n; scanf("%d", &n);
  int solucao = teorema_resto_chines(n);
  if(ERRO) {
    printf("O problema não pode ser resolvido pelo teorema do resto chinês ou não tem solução\n");
  }
  else {
    printf("x é igual à %d", solucao);
  }
}

void interpretar(int *r, int *m) {
  int a_inicial, r_inicial, m_inicial, inverso_a, mdc;
  int s, t;
  scanf("%d %d %d", &a_inicial, &r_inicial, &m_inicial);

  if (m_inicial <= 0){
    ERRO = 1;
    *r = -1;
    *m = -1;
    return;
  }

  r_inicial = (m_inicial + r_inicial % m_inicial) % m_inicial;
  a_inicial = (m_inicial + a_inicial % m_inicial) % m_inicial;

  mdc = mdc_diofantino(a_inicial, m_inicial, &s, &t);

  if (r_inicial % mdc != 0){
    ERRO = 1;
    *r = -1;
    *m = -1;
    return;
  }

  a_inicial /= mdc;
  r_inicial /= mdc;
  m_inicial /= mdc;

  inverso_a = inverso_modulo(a_inicial, m_inicial);
  
  if (inverso_a == 0){
    ERRO = 1;
    *r = -1;
    *m = -1;
    return;
  }

  r_inicial *= inverso_a;
  r_inicial = r_inicial % m_inicial;

  *r = r_inicial;
  *m = m_inicial;
}

int teorema_resto_chines(int n) {
  printf("Digite as %d congruências: \n", n);
  int M_grande = 1, r[n], m[n];
  for(int i = 0; i < n; i++) {
    interpretar(&r[i], &m[i]);
    M_grande *= m[i];
  }

  if (ERRO) return -1;

  int solucao = 0;
  for(int i = 0; i < n; i++) {
    int M = M_grande / m[i];
    //M = M_grande / m[i]
    //incremente M * s[i] * r[i] à solução
    int s = achar_solucao_congruencia(M, 1, m[i]);
    int coefS, coefT; 
    if(mdc_diofantino(M, m[i], &coefS, &coefT) != 1)
      ERRO = 1;
    solucao += s * M * r[i];
  }
  return solucao;
}

int achar_solucao_congruencia(int a, int b, int m){
    int ap = a;
    ap = (m + ap % m) % m;

    int bp = b;
    bp = (m + bp % m) % m;

    if (ap == 0 && bp == 0) return 0;

    int s, t;
    int mdc_am = mdc_diofantino(ap, m, &s, &t);

    if (bp % mdc_am != 0) return -1;

    int inverso_a = inverso_modulo(ap/mdc_am, m/mdc_am);
    if (inverso_a == 0) return -1;

    int solucao = inverso_a*(bp/mdc_am);

    solucao = (m + solucao % m) % m;

    return solucao;
}

int inverso_modulo(int a, int b){
    int s, t;
    int MDC = mdc_diofantino(a, b, &s, &t);

    if (MDC != 1) return 0;

    s = (b + s % b) % b;

    return s;
}

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
