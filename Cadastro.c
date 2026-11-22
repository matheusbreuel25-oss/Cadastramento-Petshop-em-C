#include <stdio.h>
#include <string.h>

#define ARQUIVO "pets.txt"

typedef struct {
    char nomepet[50];
    int idadepet;
    int id;
} Pet;


void limparBuffer(void);
void mostrarmenu(void);
void cadastrarPet(void);
void listarPets(void); 
void atualizarcadastro(void);
void excluir(void);

void limparBuffer(void) {
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Limpa o buffer de entrada
    }
}

void listarPets(void) {
    Pet pet;
    FILE *arquivo;

    printf("\n=== LISTA DE PETS ===\n");

    arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    while (fscanf(arquivo, "%d %49s %d", &pet.id, pet.nomepet, &pet.idadepet) == 3) {
        printf("ID: %d | Nome: %s | Idade: %d\n", pet.id, pet.nomepet, pet.idadepet);
    }

    fclose(arquivo);
}

void mostrarmenu(void) { //amostragem do menu de cadastro de pets
    printf("\n=== Cadastro De Pets ===\n");
    printf("1 - Cadastrar Pet\n");
    printf("2 - Listar Pets\n");
    printf("3 - Atualizar cadastro\n");
    printf("4 - Excluir\n");
    printf("5 - Sair\n");
}

void cadastrarPet(void){
    Pet novoPet;
    Pet pet;
    FILE *arquivo;
    int existe = 0;
    int maiorId = 0;

        printf("\n=== CADASTRAR PET ===\n");

        printf("Digite o nome do pet: ");
        fgets(novoPet.nomepet, sizeof(novoPet.nomepet), stdin);
        printf("Idade do pet: ");
        scanf("%d", &novoPet.idadepet);
        arquivo = fopen(ARQUIVO, "r");

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d %49s %d",
                      &pet.id, pet.nomepet, &pet.idadepet) == 3) {

            if (pet.id > maiorId) {
                maiorId = pet.id;
            }

            if (strcmp(pet.nomepet, novoPet.nomepet) == 0) {
                existe = 1;
            }
        }

        fclose(arquivo);
    }

    if (existe) {
        printf("\nEsse pet ja esta cadastrado!\n");
        return; }
        novoPet.id = maiorId + 1;

    // Abre o arquivo para adicionar informações
    arquivo = fopen(ARQUIVO, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(arquivo, "%d %s %d\n",
            novoPet.id, novoPet.nomepet, novoPet.idadepet);

    fclose(arquivo);

    printf("\nPet cadastrado com sucesso! ID: %d\n", novoPet.id);

}     


int main(void) {
    int opcao;

    do {
        mostrarmenu();
        printf("Digite a opcao desejada: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarPet();      break;
            case 2: listarPets();        break;
            case 3: atualizarcadastro(); break;
            case 4: excluir();           break;
            case 5: limpar(); printf("Saindo do programa...\n"); break;
            default: printf("Opcao invalida\n"); break;
        }
    } while (opcao != 5);

    return 0;
}