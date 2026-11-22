#include <stdio.h> 
#include <stdlib.h>

struct Pet {
   char nomepet [50]; 
   int idadepet;
   int id;
   char raca [50];
   
};


int mostrarmenu(void){
        printf("===Cadastro De Pets===\n");
        printf("=== 1-Cadastrar Pet===\n");
        printf("=== 2-Listar Pets ===\n");
        printf("=== 3-atualizar cadastro ===\n");
        printf("=== 4-Excluir ===\n");
        printf("=== 5-Sair ===\n");
    }

int main(void) {
    int opcao; 
    mostrarmenu();
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);




    return 0; 
}