#include <stdio.h>

int achar_solucao_congruencia(int a, int b, int m);
int inverso_modulo(int a, int b);
int mdc_diofantino(int a, int b, int *s, int *t);
int teorema_resto_chines(int n);

int main() {
  printf("Digite o número de congruências: ");
  int n; scanf("%d", &n);
  int solucao = teorema_resto_chines(n); 
  if(solucao == -1) {
    printf("Não tem solução\n");
    return 0;
  }
  printf("x é igual à %d", solucao);
}

int teorema_resto_chines(int n) {
  printf("Digite as %d congruências: \n", n);
  int M_grande = 1, r[n], m[n];
  for(int i = 0; i < n; i++) {
    scanf("%d %d", &r[i], &m[i]);
    M_grande *= m[i];
  }

  int M[n];
  int solucao = 0;
  int n_tem_sol = 0;
  for(int i = 0; i < n; i++) {
    M[i] = M_grande / m[i];
    /*
    incremente M[i] * s[i] * r[i] à solução
    */
    int s = achar_solucao_congruencia(M[i], 1, m[i]);
    if(s == -1) {
      n_tem_sol = 1;
      break;
    }
    solucao += s * M[i] * r[i];
  }
  if(n_tem_sol) return -1; //retornando -1 se a congruencia n tem solução.
  return solucao;
}

int achar_solucao_congruencia(int a, int b, int m) {
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
