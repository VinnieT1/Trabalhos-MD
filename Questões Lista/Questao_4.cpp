#include <vector>
#include <stdio.h>
#include <math.h>
#include <set>

using namespace std;

//reaproveitando algumas funções da questão passada;
void decompor(int num, vector<int> &vetor);
vector<int> pegar_fatores_primos(int num);
vector<int> pegar_lista_expo(int num);
int pegar_mdc(int a, int b);
int pegar_mmc(int a, int b);

int main() {
  //lendo os dois inteiros;
  int A, B;
  printf("Digite dois inteiros para calcular o MMC e o MDC entre eles:\n");
  scanf("%d %d", &A, &B);

  if(A < 0 || B < 0) {
    printf("Entrada inválida, números negativos\n");
    return 0;
  }

  printf("O MMC(%d, %d) é: %d\n", A, B, pegar_mmc(A, B));
  printf("O MDC(%d, %d) é: %d\n", A, B, pegar_mdc(A, B));
}

void decompor(int num, vector<int> &vetor) {
  if(num == 1) return;
  int found = 0;
  for(int i = 2; !found && i*i <= num; i++) {
    if(num % i == 0) {
      vetor.push_back(i);
      decompor(num / i, vetor);
      found = 1;
    }
  }
  if(!found) 
    vetor.push_back(num);
}

vector<int> pegar_fatores_primos(int num) {
  vector<int> retorno;
  decompor(num, retorno);
  return retorno;
}

vector<int> pegar_lista_expo(int num) {
  vector<int> fatores_primos = pegar_fatores_primos(num);
  //vetor dos expoentes onde expoente[i] retorna o expoente
  //que acompanha o inteiro i.
  //o tamanho máximo é num + 1, visto que o maior primo possível
  //que é fator de num, é ele mesmo (se num for primo);
  //inicialmente os valores são 0;

  vector<int> expoentes(num + 1, 0);
  for(int primo : fatores_primos) {
    expoentes[primo]++;
  }
  return expoentes;
}

int pegar_mdc(int a, int b) {
  //vamos tornar a < b, já que a ordem
  //não importa, e vai ajudar na lógica
  //do meu algoritmo
  if(a > b) swap(a, b);

  //agora, se a (o menor) for igual à
  //0, então o MDC é igual a B;
  if(a == 0) return b;

  //caso o contrário, faça o resto:
  int MDC = 1;
  vector<int> expo_a, expo_b;
  expo_a = pegar_lista_expo(a);
  expo_b = pegar_lista_expo(b);
  /*
  para o mdc, precisamos apenas dos
  fatores primos de 1 número, já que
  o algoritmo pega o mínimo dos expoentes;
  */
  //vamos construir isso usando um set então:
  set<int> conjunto_fatores;
  for(int primo : pegar_fatores_primos(a))
    conjunto_fatores.insert(primo);
  //vamos pegar então os fatores de a:
  for(int primo : conjunto_fatores) {
    int min_expo = min(expo_a[primo], expo_b[primo]);
    MDC *= (int) pow(primo, min_expo);
  }
  return MDC;
}

int pegar_mmc(int a, int b) {
  int MMC = 1;
  vector<int> expo_a, expo_b;
  expo_a = pegar_lista_expo(a);
  expo_b = pegar_lista_expo(b);
  /*
  já para o mmc, devemos ver a união dos conjuntos
  dos fatores primos de a e b, e ir pegando o máximo
  de seus expoentes
  */
  //vamos construir isso usando um set então:
  set<int> conjunto_fatores;
  for(int primo : pegar_fatores_primos(a))
    conjunto_fatores.insert(primo);
  for(int primo : pegar_fatores_primos(b))
    conjunto_fatores.insert(primo);

  //vamos então ir multiplicando o mmc pelo max dos
  //expoentes
  for(int primo : conjunto_fatores) {
    int max_expo = max(expo_a[primo], expo_b[primo]);
    MMC *= (int) pow(primo, max_expo);
  }
  return MMC;
}
