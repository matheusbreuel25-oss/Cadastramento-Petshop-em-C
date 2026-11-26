//falta implementar a funcao media das idades 
#include <stdio.h>
#include <string.h>

#define ARQUIVO "pets.txt"

typedef struct {
    char nomepet[50];
    int idadepet;
    char raca[50];
    int id;
} Pet;

void limparBuffer(void);
void mostrarmenu(void);
void cadastrarPet(void);
void listarPets(void);
void atualizarcadastro(void);
void excluir(void);
void mediaIdades(void);

void mediaIdades(void) {
    Pet pet;
    FILE *arquivo;
    int somaIdades = 0;
    int contador = 0;

    arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    while (fscanf(arquivo, "%d %49s %d %49s",
                  &pet.id, pet.nomepet, &pet.idadepet, pet.raca) == 4) {
        somaIdades += pet.idadepet;
        contador++;
    }

    fclose(arquivo);

    if (contador > 0) {
        double media = (double)somaIdades / contador;
        printf("Media das idades dos pets: %.2f\n", media);
    } else {
        printf("Nenhum pet cadastrado para calcular a media.\n");
    }
}


void atualizarcadastro(void) {
    Pet pet;
    Pet novo;
    int idAtualizar;
    int encontrado = 0;
    int duplicado = 0;

    printf("\n=== ATUALIZAR CADASTRO ===\n");
    printf("Digite o ID do pet a atualizar: ");
    if (scanf("%d", &idAtualizar) != 1) {
        limparBuffer();
        printf("ID invalido!\n");
        return;
    }
    limparBuffer();

    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    // 1ª leitura: procura o pet e guarda os dados atuais
    while (fscanf(arquivo, "%d %49s %d %49s",
                  &pet.id, pet.nomepet, &pet.idadepet, pet.raca) == 4) {
        if (pet.id == idAtualizar) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Pet com ID %d nao encontrado.\n", idAtualizar);
        fclose(arquivo);
        return;
    }

    printf("\nDados atuais -> Nome: %s | Idade: %d | Raca: %s\n",
           pet.nomepet, pet.idadepet, pet.raca);

    // Pede os dados novos
    novo.id = idAtualizar;

    printf("Novo nome: ");
    fgets(novo.nomepet, sizeof(novo.nomepet), stdin);
    novo.nomepet[strcspn(novo.nomepet, "\n")] = '\0';

    printf("Nova idade: ");
    scanf("%d", &novo.idadepet);
    limparBuffer();

    printf("Nova raca: ");
    scanf("%49s", novo.raca);
    limparBuffer();

    FILE *temp = fopen("pets.tmp", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    // 2ª leitura: volta ao início e copia tudo, trocando o pet escolhido
    rewind(arquivo);
    while (fscanf(arquivo, "%d %49s %d %49s",
                  &pet.id, pet.nomepet, &pet.idadepet, pet.raca) == 4) {
        if (pet.id == idAtualizar) {
            fprintf(temp, "%d %s %d %s\n",
                    novo.id, novo.nomepet, novo.idadepet, novo.raca);
        } else {
            // impede que o novo nome fique igual ao de outro pet
            if (strcmp(pet.nomepet, novo.nomepet) == 0) {
                duplicado = 1;
            }
            fprintf(temp, "%d %s %d %s\n",
                    pet.id, pet.nomepet, pet.idadepet, pet.raca);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (duplicado) {
        remove("pets.tmp");
        printf("\nJa existe outro pet com esse nome. Nada foi alterado.\n");
    } else {
        remove(ARQUIVO);
        rename("pets.tmp", ARQUIVO);
        printf("\nCadastro atualizado com sucesso!\n");
    }
}

void excluir(void) {
    Pet pet;
    int idExcluir;
    int encontrado = 0;

    printf("\n=== EXCLUIR PET ===\n");
    printf("Digite o ID do pet a excluir: ");
    if (scanf("%d", &idExcluir) != 1) {
        limparBuffer();
        printf("ID invalido!\n");
        return;
    }
    limparBuffer();

    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    FILE *temp = fopen("pets.tmp", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fscanf(arquivo, "%d %49s %d %49s",
                  &pet.id, pet.nomepet, &pet.idadepet, pet.raca) == 4) {
        if (pet.id == idExcluir) {
            encontrado = 1;               // pula este pet, não copia
        } else {
            fprintf(temp, "%d %s %d %s\n",
                    pet.id, pet.nomepet, pet.idadepet, pet.raca);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove(ARQUIVO);                  // apaga o arquivo antigo
        rename("pets.tmp", ARQUIVO);      // o temporário vira o arquivo oficial
        printf("Pet excluido com sucesso!\n");
    } else {
        remove("pets.tmp");               // nada mudou, descarta o temporário
        printf("Pet com ID %d nao encontrado.\n", idExcluir);
    }
}

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
    while (fscanf(arquivo, "%d %49s %d %49s",
                  &pet.id, pet.nomepet, &pet.idadepet, pet.raca) == 4) {
        printf("ID: %d | Nome: %s | Idade: %d | Raca: %s\n",
               pet.id, pet.nomepet, pet.idadepet, pet.raca);
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
    printf("6 - Media das idades dos pets\n");
}

void cadastrarPet(void) {
    Pet novoPet;
    Pet pet;
    FILE *arquivo;
    int existe = 0;
    int maiorId = 0;

    printf("\n=== CADASTRAR PET ===\n");

    printf("Digite o nome do pet: ");
    fgets(novoPet.nomepet, sizeof(novoPet.nomepet), stdin);
    novoPet.nomepet[strcspn(novoPet.nomepet, "\n")] = '\0';

    printf("Idade do pet: ");
    scanf("%d", &novoPet.idadepet);
    limparBuffer();

    printf("Digite a raca do pet: ");
    scanf("%49s", novoPet.raca);
    limparBuffer();

    arquivo = fopen(ARQUIVO, "r");

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d %49s %d %49s",
                      &pet.id, pet.nomepet, &pet.idadepet, pet.raca) == 4) {

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
        return;
    }

    novoPet.id = maiorId + 1;


    arquivo = fopen(ARQUIVO, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(arquivo, "%d %s %d %s\n",
            novoPet.id, novoPet.nomepet, novoPet.idadepet, novoPet.raca);

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
            case 5: printf("Saindo do programa...\n"); break;
            case 6: mediaIdades();       break;
            default: printf("Opcao invalida\n"); break;
        }
    } while (opcao != 5);

    return 0;
}
