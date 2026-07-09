#include <stdio.h>
#include <string.h>
#include <locale.h>

#define NUM_TERRITORIOS 5

// estrutura do territorio
typedef struct {
    char nome[50];
    char cor[30];
    int tropas;
} Territorio;

void exibirMapa(Territorio mapa[NUM_TERRITORIOS]);

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    Territorio mapa[NUM_TERRITORIOS];
    
    printf("=== CADASTRO DE TERRITORIOS ===\n\n");
    
    // Ler os dados de cada territorio
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Territorio %d ---\n", i + 1);
        
        printf("Nome: ");
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;  // Remove '\n'
        
        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 30, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;
        
        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();  // Remove '\n' do buffer
        
        printf("\n");
    }
    
    // Exibir o mapa
    exibirMapa(mapa);
    
    return 0;
}

void exibirMapa(Territorio mapa[NUM_TERRITORIOS]) {
    printf("\n=== ESTADO DO MAPA ===\n\n");
    
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n\n", mapa[i].tropas);
    }
}
