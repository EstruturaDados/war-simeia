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
    char dono;
} Territorio;

void exibirMapa(Territorio *mapa);
void simularAtaque(Territorio *mapa, int atacante, int defensor);
int verificarMissao(Territorio *mapa, int missao);
void exibirMissao(int missao);

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

        // jeito simples: os 2 primeiros comecam como jogador
        if (i < 2) {
            mapa[i].dono = 'J';
        } else {
            mapa[i].dono = 'I';
        }

        printf("\n");
    }

    int missao = rand() % 2;

    exibirMapa(mapa);
    exibirMissao(missao);

    // menu do nivel mestre
    while (1) {
        int opcao;
        int atacante;
        int defensor;

        printf("\n=== MENU ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 0) {
            break;
        }

        if (opcao == 2) {
            exibirMissao(missao);
            if (verificarMissao(mapa, missao)) {
                printf("\nParabens! Missao concluida!\n");
                break;
            } else {
                printf("\nAinda nao concluiu a missao.\n");
            }
            continue;
        }

        if (opcao != 1) {
            printf("Opcao invalida.\n");
            continue;
        }

        printf("\n=== FASE DE ATAQUE ===\n");
        printf("Escolha atacante (1 a 5): ");
        scanf("%d", &atacante);
        getchar();

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

        if (mapa[atacante].dono != 'J') {
            printf("Esse atacante nao e seu.\n");
            continue;
        }

        if (mapa[defensor].dono == 'J') {
            printf("Nao pode atacar um territorio seu.\n");
            continue;
        }

        simularAtaque(mapa, atacante, defensor);
        exibirMapa(mapa);

        if (verificarMissao(mapa, missao)) {
            printf("\nParabens! Missao concluida!\n");
            break;
        }
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
        printf("  Dono: %c\n\n", mapa[i].dono);
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
        mapa[defensor].dono = mapa[atacante].dono;
        mapa[defensor].tropas = 1;
    }
}

void exibirMissao(int missao) {
    printf("\n=== MISSAO ATUAL ===\n");
    if (missao == 0) {
        printf("Destruir o exercito Verde.\n");
    } else {
        printf("Conquistar 3 territorios.\n");
    }
}

int verificarMissao(Territorio *mapa, int missao) {
    if (missao == 0) {
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].dono != 'J') {
                return 0;
            }
        }
        return 1;
    }

    if (missao == 1) {
        int cont = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (mapa[i].dono == 'J') {
                cont++;
            }
        }

        if (cont >= 3) {
            return 1;
        }
    }

    return 0;
}
