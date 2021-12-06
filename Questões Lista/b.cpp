#include <vector>
#include <stdio.h>

using namespace std;

int main(void) {

  //inteiro máximo que vou checar:
  int maxNum = 80000000; 
  /*
  obs: consegui em 43 segundos no meu PC,
  talvez se não imprimisse pelo terminal fosse
  mais rápido. O tempo de execução varia com o
  ambiente.
  */

  //criando a array booleana:
  vector<bool> eh_primo(maxNum + 1, 1);
  eh_primo[1] = 0;

  //setando os não primos:
  for(int i = 2; i * i <= maxNum; i++) {
    if(eh_primo[i]) {
      for(int j = i * i; j <= maxNum; j += i) {
        eh_primo[j] = 0;
      }
    }
  }

  //basta entao, printar os primos:
  for(int i = 1; i <= maxNum; i++) {
    if(eh_primo[i])
      printf("%d\n", i);
  }

  //Time complexity: O(n)
  //Space complexity: O(n)
}
