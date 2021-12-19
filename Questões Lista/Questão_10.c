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
  //instrucoes para o scanf:
  printf("Digite o número de congruências: ");
  int n; scanf("%d", &n);
  int solucao = teorema_resto_chines(n);
  //caso haja erro, eh avisado:
  if(ERRO) {
    printf("O problema não pode ser resolvido pelo teorema do resto chinês ou não tem solução\n");
  }
  //senao, eh printada a solucao:
  else {
    printf("x é igual à %d", solucao);
  }
}

//a funcao serve para "padronizar" congruencias do tipo ax congruente a r (mod m),
//transformando em uma congruencia equivalente no formado x congruente a k (mod n),
//onde 0 < k < n, n > 1
void interpretar(int *r, int *m) {
  //declarando as variaveis necessarias para fazer a padronizacao:
  //ax congruente a r (mod m)
  int a_inicial, r_inicial, m_inicial, inverso_a, mdc;
  int s, t;
  scanf("%d %d %d", &a_inicial, &r_inicial, &m_inicial);

  //caso m seja invalido, ha erro:
  if (m_inicial <= q){
    ERRO = 1;
    *r = -1;
    *m = -1;
    return;
  }
  
  //padronizando os valores equivalentes e positivos:
  r_inicial = (m_inicial + r_inicial % m_inicial) % m_inicial;
  a_inicial = (m_inicial + a_inicial % m_inicial) % m_inicial;

  //calculando o mdc entre a e m:
  mdc = mdc_diofantino(a_inicial, m_inicial, &s, &t);

  //se o mdc nao divide r, ha erro:
  if (r_inicial % mdc != 0){
    ERRO = 1;
    *r = -1;
    *m = -1;
    return;
  }

  //dividindo os numeros pelo mdc de a e m:
  a_inicial /= mdc;
  r_inicial /= mdc;
  m_inicial /= mdc;

  //calculando o inverso de a (mod m):
  inverso_a = inverso_modulo(a_inicial, m_inicial);
  
  //se nao tem inverso, ha erro:
  if (inverso_a == 0){
    ERRO = 1;
    *r = -1;
    *m = -1;
    return;
  }
  
  //achando o novo valor padronizado de r:
  r_inicial *= inverso_a;
  r_inicial = r_inicial % m_inicial;

  //designando os novos valores de a e m:
  *r = r_inicial;
  *m = m_inicial;
}

//retorna -1 caso nao haja solucao, caso contrario, retorna uma solucao:
int teorema_resto_chines(int n) {
  //instrucao de input:
  printf("Digite as %d congruências: \n", n);
  int M_grande = 1, r[n], m[n];
  
  //obtendo os inputs e padronizando:
  //obtendo tambem o produto de todos os m das congruencias:
  for(int i = 0; i < n; i++) {
    interpretar(&r[i], &m[i]);
    M_grande *= m[i];
  }

  //caso haja erro, eh retornado -1:
  if (ERRO) return -1;

  //obtendo a solucao:
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
  //retornando a solucao entre 0 e M_grande:
  return solucao % M_grande;
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
