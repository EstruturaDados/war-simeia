#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define NUM_TERRITORIOS 5

// estrutura simples do territorio
typedef struct {
    char nome[50];
    char cor[30];
    int tropas;
} Territorio;

void exibirMapa(Territorio *mapa);
void simularAtaque(Territorio *mapa, int atacante, int defensor);

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    // nivel aventureiro: agora usando memoria dinamica
    Territorio *mapa = (Territorio *) calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro de memoria.\n");
        return 1;
    }

    printf("=== CADASTRO DE TERRITORIOS ===\n\n");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Territorio %d ---\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 30, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();

        printf("\n");
    }

    exibirMapa(mapa);

    // fase de ataque
    while (1) {
        int atacante;
        int defensor;

        printf("\n=== FASE DE ATAQUE ===\n");
        printf("Escolha atacante (1 a 5, 0 para sair): ");
        scanf("%d", &atacante);
        getchar();

        if (atacante == 0) {
            break;
        }

        printf("Escolha defensor (1 a 5): ");
        scanf("%d", &defensor);
        getchar();

        atacante = atacante - 1;
        defensor = defensor - 1;

        // validacao basica so pra nao quebrar o programa
        if (atacante < 0 || atacante >= NUM_TERRITORIOS || defensor < 0 || defensor >= NUM_TERRITORIOS) {
            printf("Escolha invalida.\n");
            continue;
        }

        if (atacante == defensor) {
            printf("Nao da pra atacar o mesmo territorio.\n");
            continue;
        }

        simularAtaque(mapa, atacante, defensor);
        exibirMapa(mapa);
    }

    free(mapa);
    printf("\nFim de jogo.\n");
    return 0;
}

void exibirMapa(Territorio *mapa) {
    printf("\n=== ESTADO DO MAPA ===\n\n");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n\n", mapa[i].tropas);
    }
}

void simularAtaque(Territorio *mapa, int atacante, int defensor) {
    int dadoAtaque;
    int dadoDefesa;

    dadoAtaque = (rand() % 6) + 1;
    dadoDefesa = (rand() % 6) + 1;

    printf("\nAtaque: %s -> %s\n", mapa[atacante].nome, mapa[defensor].nome);
    printf("Dado atacante: %d\n", dadoAtaque);
    printf("Dado defensor: %d\n", dadoDefesa);

    // empate favorece atacante
    if (dadoAtaque >= dadoDefesa) {
        mapa[defensor].tropas = mapa[defensor].tropas - 1;
        printf("Atacante venceu, defensor perdeu 1 tropa.\n");
    } else {
        mapa[atacante].tropas = mapa[atacante].tropas - 1;
        printf("Defensor venceu, atacante perdeu 1 tropa.\n");
    }

    if (mapa[defensor].tropas <= 0) {
        printf("Territorio conquistado!\n");
        strcpy(mapa[defensor].cor, mapa[atacante].cor);
        mapa[defensor].tropas = 1;
    }
}
