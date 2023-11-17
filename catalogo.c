#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 1000
#define MAX_LENGTH 100

typedef struct {
    int id;
    char nome[MAX_LENGTH];
    char email[MAX_LENGTH];
    char sexo[MAX_LENGTH];
    char endereco[MAX_LENGTH];
    double altura;
    int vacina;
} Usuario;

Usuario usuarios[MAX_USERS];
int total_usuarios = 0;

// Protótipos das funções
int gerarID();
int ValEmail(const char *email);
int ValSexo(const char *sexo);
void AddUser();
void EditUser();
void DelUser();
void BuscaEmail();
void PrintUser();

int gerarID() {
    return rand() % 10000 + 1;
}

int ValEmail(const char *email) {
    while (*email) {
        if (*email == '@') {
            return 1;
        }
        email++;
    }
    return 0;
}

int ValSexo(const char *sexo) {
    return strcmp(sexo, "f") == 0 || strcmp(sexo, "m") == 0;
}

void PrintUser() {
    printf("Lista de Usuario:\n");
    for (int i = 0; i < total_usuarios; i++) {
        printf("ID: %d\n", usuarios[i].id);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Email: %s\n", usuarios[i].email);
        printf("Sexo: %s\n", usuarios[i].sexo);
        printf("Endereco: %s\n", usuarios[i].endereco);
        printf("Altura: %.2f\n", usuarios[i].altura);
        printf("Vacina: %d\n", usuarios[i].vacina);
        printf("-------------------\n");
    }
}

void AddUser() {
    if (total_usuarios < MAX_USERS) {
        Usuario novoUsuario;
        novoUsuario.id = gerarID();

       
        fflush(stdin);

        printf("Nome completo: ");
        fgets(novoUsuario.nome, MAX_LENGTH, stdin);
        novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0;
        fflush(stdin);

        printf("Email: ");
        fgets(novoUsuario.email, MAX_LENGTH, stdin);
        novoUsuario.email[strcspn(novoUsuario.email, "\n")] = 0;
        while (!ValEmail(novoUsuario.email)) {
            printf("Email invalido! Insira um email valido: ");
            fgets(novoUsuario.email, MAX_LENGTH, stdin);
            novoUsuario.email[strcspn(novoUsuario.email, "\n")] = 0;
        }
fflush(stdin);
        printf("Sexo (f ou m): ");
        fgets(novoUsuario.sexo, MAX_LENGTH, stdin);
        novoUsuario.sexo[strcspn(novoUsuario.sexo, "\n")] = 0;
        while (!ValSexo(novoUsuario.sexo)) {
            printf("Sexo invalido! Insira Feminino ou Masculino: ");
            fgets(novoUsuario.sexo, MAX_LENGTH, stdin);
            novoUsuario.sexo[strcspn(novoUsuario.sexo, "\n")] = 0;
        }

        printf("Endereco: ");
        fgets(novoUsuario.endereco, MAX_LENGTH, stdin);
        novoUsuario.endereco[strcspn(novoUsuario.endereco, "\n")] = 0;

        printf("Altura (entre 1 e 3 metros): ");
        scanf("%lf", &novoUsuario.altura);
        while (novoUsuario.altura < 1 || novoUsuario.altura > 3) {
            printf("Altura invalida! Insira um valor entre 1 e 3: ");
            scanf("%lf", &novoUsuario.altura);
        }

        printf("Recebeu a vacina? (1 = sim, 0 = nao): ");
        scanf("%d", &novoUsuario.vacina);

        getchar(); // Limpar o buffer do teclado
        usuarios[total_usuarios++] = novoUsuario;
        printf("usuario adicionado com exito!\n");
    } else {
        printf("Limite de Usuario atingido!\n");
    }
}

void EditUser() {
    int id;
    printf("Digite o ID do usuario que deseja editar: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < total_usuarios; i++) {
        if (usuarios[i].id == id) {
            printf("Novo Nome completo: ");
            getchar(); // Limpar o buffer do teclado
            fgets(usuarios[i].nome, MAX_LENGTH, stdin);
            usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = 0;

            printf("Novo Email: ");
            fgets(usuarios[i].email, MAX_LENGTH, stdin);
            usuarios[i].email[strcspn(usuarios[i].email, "\n")] = 0;
            while (!ValEmail(usuarios[i].email)) {
                printf("Email invalido! Insira um email valido: ");
                fgets(usuarios[i].email, MAX_LENGTH, stdin);
                usuarios[i].email[strcspn(usuarios[i].email, "\n")] = 0;
            }

            printf("Novo Sexo (f ou m): ");
            fgets(usuarios[i].sexo, MAX_LENGTH, stdin);
            usuarios[i].sexo[strcspn(usuarios[i].sexo, "\n")] = 0;
            while (!ValSexo(usuarios[i].sexo)) {
                printf("Sexo invalido, insira Feminino ou Masculino: ");
                fgets(usuarios[i].sexo, MAX_LENGTH, stdin);
                usuarios[i].sexo[strcspn(usuarios[i].sexo, "\n")] = 0;
            }

            printf("Novo Endereco: ");
            fgets(usuarios[i].endereco, MAX_LENGTH, stdin);
            usuarios[i].endereco[strcspn(usuarios[i].endereco, "\n")] = 0;

            printf("Nova Altura (entre 1 e 3 metros): ");
            scanf("%lf", &usuarios[i].altura);
            while (usuarios[i].altura < 1 || usuarios[i].altura > 3) {
                printf("Altura invalida! Insira um valor entre 1 e 2: ");
                scanf("%lf", &usuarios[i].altura);
            }

            printf("Recebeu a vacina? (1 = sim, 0 = nao): ");
            scanf("%d", &usuarios[i].vacina);

            printf("usuario editado.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("usuario nao encontrado\n");
    }
}

void DelUser() {
    int id;
    printf("Digite o ID do usuario que deseja excluir: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < total_usuarios; i++) {
        if (usuarios[i].id == id) {
            for (int j = i; j < total_usuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            total_usuarios--;
            printf("usuario excluido com exito\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("usuario nao encontrado\n");
    }
}

void BuscaEmail() {
    char email[MAX_LENGTH];
    printf("Digite o email do usuario que deseja buscar: ");
    getchar(); // Limpar o buffer do teclado
    fgets(email, MAX_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;

    int encontrado = 0;
    printf("usuario(s) com o email '%s':\n", email);
    for (int i = 0; i < total_usuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            printf("ID: %d\n", usuarios[i].id);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Email: %s\n", usuarios[i].email);
            printf("Sexo: %s\n", usuarios[i].sexo);
            printf("Endereco: %s\n", usuarios[i].endereco);
            printf("Altura: %.2f\n", usuarios[i].altura);
            printf("Vacina: %d\n", usuarios[i].vacina);
            printf("-------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("email nao encontrado '%s'.\n", email);
    }
}

int main() {
    srand(time(NULL));
    char opcao;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar usuario\n");
        printf("2 - Editar usuario\n");
        printf("3 - Excluir usuario\n");
        printf("4 - Buscar usuario por email\n");
        printf("5 - Imprimir usuarios\n");
        printf("0 - Sair\n");
        printf("opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                AddUser();
                break;
            case '2':
                EditUser();
                break;
            case '3':
                DelUser();
                break;
            case '4':
                BuscaEmail();
                break;
            case '5':
                PrintUser();
                break;
            case '0':
                printf("Finalizando operacoes...\n Ate mais!\n");
                break;
            default:
                printf("opcao invalida, tente novamente.\n");
                break;
        }
    } while (opcao != '0');

    return 0;
}