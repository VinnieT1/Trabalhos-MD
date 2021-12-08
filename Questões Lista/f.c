#include <stdio.h>

int mdc_diofantino(int a, int b, int *s, int *t);

int main() {
  //colentando a e b;
  int a, b;
  scanf("%d %d", &a, &b);

  //definindo os coeficientes, que serão printados;
  int s, t;

  int MDC = mdc_diofantino(a, b, &s, &t);

  printf("Os coeficientes 's' e 't' são, respectivamente, %d e %d\n", s, t);
  printf("O mdc é %d\n", MDC);
}

int mdc_diofantino(int a, int b, int *s, int *t) {
  if(b == 0) {
    *s = 1;
    *t = 0;
    return a;
  }
  
  //aqui definindo os coeficientes da próxima call
  //(leia a explicação)
  int s1, t1;
  
  int MDC = mdc_diofantino(b, a % b, &s1, &t1);
  *s = t1;
  *t = s1 - t1*(a/b);
  return MDC;
  //Algoritmo:
  /*
    Vamos achar recursivamente os coefiecientes s e t, tal que a*s + b*t = mdc(a, b);
    pela lógica do algoritmo de euclides, quando b é igual à zero, na última call da recursão
    temos que: a*s + 0*t = a, logo , s = 1;
    Daí onde vem o caso base, vamos então, resolver essa transição:
    Veja:
    a*s + b*t = b*s1 + (a % b)*t1 = mdc(a, b);
    já que a % b = a - (a/b)*b (denote (a/b) como floor(a/b)), então:
    a*s + b*t = b*s1 + [a - (a/b)*b]*t1;
    continuando:
    a*s + b*t = b*s1 + a*t1 - b*(a/b)*t1;
    colocando b em evidencia:
    a*s + b*t = a*t1 + b*{s1 - (a/b)*t1}
    logo:
    s = t1, e t = s1 - (a/b)*t1;
  */
}
