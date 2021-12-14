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
    //instrucao do printf:
    printf("Digite um numero para descobrir se eh primo ou nao.\n");
    
    //numero eh a variavel que julgaremos ser primo ou nao.
    int numero;
    scanf("%d", &numero);
    
    //printa se numero eh primo ou nao.
    if (eh_primo(numero)) printf("%d eh primo!\n", numero);
    else printf("%d nao eh primo!\n", numero);

    return 0;
}
