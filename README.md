![Logo](/assets/logo-ic.png)
# Discrete-Maths
Resoluções dos trabalhos de Matemática Discreta, dos Cursos de Engenharia e Ciência da Computação, IC/UFAL.
## Introdução  
**Grupo**:  
* Daniel Silva  
* Eduardo Melo  
* Pedro Ferreira  
* Vinícius Teixeira  

**Professor**:  
* Bruno Almeida Pimentel

## Resoluções da Lista:
### Questão 1
1. Escrever um programa que determina se um dado número inteiro é primo ou não.  
#### Solução
  ```c
#include <stdio.h>
#include <stdbool.h>

//retorna true se num for primo, retorna false se num não for primo.
bool eh_primo(int num){
    if (num <= 1) return false;
    if (num == 2) return true;
    
    //checando se há algum numero que divide num, tal que este numero seja diferente de 1 e diferente de num.
    for(int i = 2; i*i <= num; i++){
        //se tal numero for achado, num nao eh primo, logo, retorna false.
        if (num % i == 0) return false;
    }
    
    //caso nao haja divisor diferente de 1 e de num, num eh primo e retorna true.
    return true;
}

int main(){
    //numero eh a variavel que julgaremos ser primo ou nao.
    int numero;
    scanf("%d", &numero);
    
    //printa se numero eh primo ou nao.
    if (eh_primo(numero)) printf("%d eh primo!\n", numero);
    else printf("%d nao eh primo!\n", numero);

    return 0;
}
  ```  
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Questões%20Lista/Questao_1.c)
#### Explicação
A função eh_primo() tem como input um inteiro N. A função checará se existe algum divisor de N no intervalo [2, sqrt(N)]. Caso haja, então N não é primo.
Caso contrário, N é primo.
A função retorna o valor booleano true caso N seja primo, e retorna o valor booleano false caso N não seja primo.

### Questão 2
2. Escrever um programa para listar números primos sequencialmente. Você deve otimizar o programa para que ele liste o maior número possível de primos em 60
segundos.  
#### Solução  
```c++
#include <vector>
#include <stdio.h>

using namespace std;

int main(void) {

  //inteiro máximo que vou checar:
  int maxNum = 90000000; 
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
  int contador = 0;
  for(int i = 1; i <= maxNum; i++) {
    if(eh_primo[i]) {
      contador++;
      printf("%d\n", i);
    }
  }
  printf("\nQuantidade de primos encontrados: %d\n", contador);
  //Time complexity: O(n)
  //Space complexity: O(n)
}
```
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Questões%20Lista/Questao_2.cpp)
#### Explicação
Esse algoritmo é igual ao crivo de erastótenes, que o professor inclusive comentou em aula. Perceba o truque que, ao visitar um primo i, ele só marca os multiplos de i maiores iguais que i * i, veja que isso basta pois qualquer número múltiplo de i menor que i * i é fatorável por um primo menor, que já foi visitado, sendo assim, os compostos menores que i * i podem ser expressos como j * k, j sendo um primo e k um inteiro qualquer, e já foi marcado como composto.  

### Questão 3
3. Escrever um programa para decompor um determinado número inteiro em seus fatores primos.  
#### Solução
```c++
#include <vector>
#include <stdio.h>

using namespace std;

vector<int> pegar_fatores_primos(int num);
void decompor(int num, vector<int> &vetor);


int main() {
  //pegando o input;
  int num;
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
```
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Questões%20Lista/Questao_3.cpp)
#### Explicação
Esse algoritmo pega recursivamente o menor divisor inteiro de um número que é maior que 1, isto é, sempre vai pegar um número primo, pois imagine o seguinte:  
Imagine que ele pegou um número K, que não seja primo, K é fatorável por dois primos k1 e k2, logo K = k1 * k2, está aí a contradição, antes de pegar o número K o algoritmo acharia k1 < K, ou k2 < K (O menor deles). Logo, o vetor que retorno sai ordenado, com os fatores primos.

### Questão 4
4. Escrever um programa para determinar o mdc e o mmc de dois inteiros com base em seus fatores primos.
#### Solução
```c++
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
```
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Questões%20Lista/Questao_4.cpp)
#### Explicação
Bom, o professor mencionou em aula esse algoritmo que acha o MDC e o MMC, basta encontrar os fatores primos dos números, e então:  
Para o MDC:
O MDC é igual à cada fator primo elevado ao seu mínimo expoente de A e de B, por isso criei a array dos expoentes, e fiz es processo, começando por 1. Perceba que precisei tratar o caso onde 1 número é 0, pois MMC(0, Z) é sempre Z.  
Para o MMC:  
Fiz semelhante, só que usando o máximo expoente de A e de B, eu poderia usar a propriedade que o MMC(a, b) = a * b / MDC(a, b), e poupar algumas linhas de código, mas preferi fazer como foi pedido na questão.  
**Sobre o uso do Set**  
Optei por usar o set<int>, uma estrutura do C++ que simula um conjunto na matemática, onde as repetições não importam (cada elemento é considerado único). Além disso, o tempo do método insert é baixo, O(log(size)), onde size é a quantidade de elementos do no set, isso deixa o programa mais rápido, tive que usá-lo pois não podia visitar o mesmo fator primo 2x, uma alternativa à isso seria iterar entre todos os inteiros de 2 até max(a, b), porém isso seria mais custoso computacionalmente.  

### Questão 5
5. Escrever um programa para determinar o mdc de dois números com base no Algoritmo de Euclides.
#### Solução
```c
#include <stdio.h>

int calcular_mdc (int a, int b)
{
    /* se b for igual à zero,
       chegamos no caso base
    */
    if (b == 0) return a;
    //o contrário chamamos a recursão:
    return calcular_mdc(b, a % b);
}


int main ()
{
    int a,b;//2 variáveis inteiras que deseja calcular o máximo divisor comum por meio do algoritmo de euclides
    printf("Digite 2 números para calcular o MDC: \n");
    scanf("%d %d", &a,&b);
    printf("Resultado: %d\n", calcular_mdc(a,b));
    return 0;
}
```
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Questões%20Lista/Questao_5.c)
#### Explicação
TO_DO;

  
### Questão 6
6. Escrever um programa para encontrar os coeficientes s e t da combinação linear
mdc(a, b) = s * a + t * b.
#### Solução 
```c 
 
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
}
```
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Quest%C3%B5es%20Lista/Questao_6.c)
#### Explicação
Vamos achar recursivamente os coefiecientes s e t, tal que a * s + b * t = mdc(a, b);  
Pela lógica do algoritmo de euclides, quando b é igual à zero, na última call da recursão temos que:  
a * s + 0 * t = a, logo , s = 1;  
Daí onde vem o caso base, vamos então, resolver essa transição:  
Veja:  
a * s + b * t = b * s1 + (a % b) * t1 = mdc(a, b);  
Já que a % b = a - (a/b) * b (denote (a/b) como floor(a/b)), então:  
a * s + b * t = b * s1 + [a - (a/b) * b] * t1;  
Continuando:  
a * s + b * t = b * s1 + a * t1 - b * (a/b) * t1;  
Colocando b em evidencia:  
a * s + b * t = a * t1 + b * {s1 - (a/b) * t1}  
Logo:  
s = t1, e t = s1 - (a/b) * t1;  

### Questão 7
7. Escrever um programa para encontrar o inverso de a ≡ mod b.
#### Solução
```c
#include <stdio.h>

int mdc_diofantino(int a, int b, int *s, int *t);

int inverso_modulo(int a, int b);

int main() {
    //scaneando a e b;
    int a, b;
    scanf("%d %d", &a, &b);

    //o inverso de a mod b existe se e somente se mdc(a, b) = 1.
    //Seja s o inverso de a mod b. s eh tal que a*s + b*t = 1; (s e t sao inteiros).

    //achando o inverso de a mod b:
    //explicacao da funcao na declaracao da mesma.
    int inverso = inverso_modulo(a, b);
	
    //printando o inverso caso exista, ou printando que ele nao existe (caso nao exista):
    if (inverso == 0) printf("Nao ha inverso de %d mod %d.\n", a, b);
    else printf("O inverso de %d mod %d eh: %d\n", a, b, inverso);

    return 0;
}

//encontra o inverso de a mod b:
int inverso_modulo(int a, int b){
    //declarando os coeficientes s e t:
    int s, t;

    //encontrando o MDC e achando o valor de s:
    int MDC = mdc_diofantino(a, b, &s, &t);

    //se MDC != 1, entao nao ha inverso; a funcao retorna 0. Caso contrario, a funcao retorna o inverso (entre 0 e b).
    if (MDC != 1) return 0;

    //achando o inverso entre 0 e b:
    while (s < 0) s += b;
    if (s > b) s = s % b;

    //retornando o inverso:
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
```
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Quest%C3%B5es%20Lista/Questao_7.c)
#### Explicação
O inverso de a (mod b) é um número inteiro k, tal que ka é congruente a 1 (mod b). É possível achar k a partir do algoritmo de Euclides: mdc(a, b) = ak + bt; (t é um número inteiro que satisfaz tal equação). Na realidade, existem infinitos inversos de a mod b, os quais possuem fórmula geral K = k + cb, onde K é o termo geral para o inverso, e c é um inteiro qualquer. No entanto, decidimos padronizar o valor do inverso no intervalo (0, b), isto é, o inverso encontrado sempre estará entre 0 e b.
  
### Questão 8
8. Escrever um programa para encontrar a solução de uma congruência do tipo ax 
b mod m.
#### Solução
```c	
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
```
* [Link](https://github.com/VinnieT1/Trabalhos-MD/blob/main/Quest%C3%B5es%20Lista/Questao_8.c)
#### Explicação
Para encontrar um valor de x que satisfaça a congruência, devemos achar x congruente a bk (mod m), onde k é um inteiro tal que ka é congruente a 1 (mod m). Usando o algoritmo da questão anterior, encontramos k (que é o inverso de a). Então, x = bk satisfará a equação (caso as demais exigências explicitadas no código também sejam cumpridas). No entanto, existem casos onde existem múltiplos valores para x. Então, decidimos escolher x pertencente ao intervalo (0, m), isto é, x estará entre 0 e m.

### Questão 9
### Questão 10

