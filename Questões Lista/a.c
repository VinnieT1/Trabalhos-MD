#include <stdio.h>
#include <stdbool.h>

//retorna true se num for primo, retorna false se num não for primo.
bool eh_primo(int num){
    if (num <= 1) return false;
    if (num == 2) return true;

    for(int i = 2; i*i <= num; i++){
        if (num % i == 0) return false;
    }

    return true;
}

int main(){
    int numero;
    scanf("%d", &numero);

    if (eh_primo(numero)) printf("%d eh primo!\n", numero);
    else printf("%d nao eh primo!\n", numero);

    return 0;
}
