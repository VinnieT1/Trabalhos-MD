#include <vector>
#include <stdio.h>

using namespace std;

vector<int> pegar_fatores_primos(int num);
void decompor(int num, vector<int> &vetor);


int main() {
  //pegando o input;
  int num;
  printf("Digite o número que deseja fatorar:\n");
  scanf("%d", &num);
  
  if(num < 2) {
    printf("O número %d não tem fatores primos", num);
    return 0;
  }

  //construindo o vetor de fatores primos:
  vector<int> fatores_primos = pegar_fatores_primos(num);

  //printando:
  printf("Fatores primos de %d: ", num);
  int vector_size = fatores_primos.size();
  for(int i = 0; i < vector_size; i++) {
    if(i == vector_size - 1 && vector_size > 1) printf(" e ");
    else if(i > 0) printf(", ");
    printf("%d", fatores_primos[i]);
  }
  printf(".\n");
}

//função recursiva para ir adicionando no vetor;
void decompor(int num, vector<int> &vetor) {
  if(num == 1) return;
  int found = 0; //booleana para saber se achei ou não o primo;
  for(int i = 2; !found && i*i <= num; i++) {
    if(num % i == 0) {
      vetor.push_back(i);
      decompor(num / i, vetor);
      found = 1;
    }
  }
  /*
  observe que o loop acaba quando eu acho 
  o primeiro inteiro que divide o número.
  esse primeiro inteiro é sempre o menor primo
  que divide num, visto que nunca vai chegar num
  numero composto antes de "topar" com seu fator primo.
  */
  if(!found) 
    vetor.push_back(num);
  //se não achei nenhum divisor menor que 
  //sqrt(num), então o primo é o próprio num;
}

vector<int> pegar_fatores_primos(int num) {
  vector<int> retorno;
  decompor(num, retorno);
  /*
  chamo a função decompor com o parametro
  retorno, para ir adicionando os fatores 
  primos ao vetor;
  */
  return retorno;
}
