#include <stdio.h>

#define TAMANHO_TABULEIRO 10   // Tamanho fixo do tabuleiro 10x10
#define TAMANHO_NAVIO 3        // Cada navio ocupa 3 posições
#define AGUA 0                 // água
#define NAVIO 3                // parte de navio

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;

    // Inicializa o tabuleiro com água (0)
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Define as coordenadas iniciais dos navios
    // ---- Navios horizontais/verticais ----
    int linhaHorizontal = 1, colunaHorizontal = 2; // Navio horizontal
    int linhaVertical = 5, colunaVertical = 6;     // Navio vertical

    // ---- Navios diagonais ----
    int linhaDiagonal1 = 0, colunaDiagonal1 = 0;   // Diagonal principal ↘
    int linhaDiagonal2 = 0, colunaDiagonal2 = 9;   // Diagonal secundária ↙

    //  Função auxiliar simples para verificar se posição está livre
    #define LIVRE(x, y) (tabuleiro[x][y] == AGUA)

    //  Posiciona o navio horizontal
    if (colunaHorizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!LIVRE(linhaHorizontal, colunaHorizontal + i))
                sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAMANHO_NAVIO; i++)
                tabuleiro[linhaHorizontal][colunaHorizontal + i] = NAVIO;
        }
    }

    //  Posiciona o navio vertical
    if (linhaVertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!LIVRE(linhaVertical + i, colunaVertical))
                sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAMANHO_NAVIO; i++)
                tabuleiro[linhaVertical + i][colunaVertical] = NAVIO;
        }
    }

    // Posiciona o navio diagonal ↘ (linha e coluna aumentam)
    if (linhaDiagonal1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        colunaDiagonal1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {

        int sobreposicao = 0;
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!LIVRE(linhaDiagonal1 + i, colunaDiagonal1 + i))
                sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAMANHO_NAVIO; i++)
                tabuleiro[linhaDiagonal1 + i][colunaDiagonal1 + i] = NAVIO;
        }
    }

    // Posiciona o navio diagonal ↙ (linha aumenta, coluna diminui)
    if (linhaDiagonal2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        colunaDiagonal2 - (TAMANHO_NAVIO - 1) >= 0) {

        int sobreposicao = 0;
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (!LIVRE(linhaDiagonal2 + i, colunaDiagonal2 - i))
                sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (i = 0; i < TAMANHO_NAVIO; i++)
                tabuleiro[linhaDiagonal2 + i][colunaDiagonal2 - i] = NAVIO;
        }
    }

    //  Exibe o tabuleiro com cabeçalho alfabético (A–J)
    printf("\n===== TABULEIRO COMPLETO - BATALHA NAVAL =====\n\n");

    // Cabeçalho de colunas (A, B, C, ...)
    printf("    ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %c ", 'A' + j);
    }
    printf("\n");

    // Linhas com índices numéricos
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n");

    return 0;
}