#include <stdio.h>
#include <stdlib.h> 

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

#define TAM_HABILIDADE 5  // Tamanho fixo das matrizes de habilidade (5x5)

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;

    // Inicializa o tabuleiro com água
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Define coordenadas fixas dos navios
    int linhaHorizontal = 1, colunaHorizontal = 2;
    int linhaVertical = 5, colunaVertical = 6;
    int linhaDiagonal1 = 0, colunaDiagonal1 = 0;
    int linhaDiagonal2 = 0, colunaDiagonal2 = 9;

    #define LIVRE(x, y) (tabuleiro[x][y] == AGUA)

    // Navio horizontal
    if (colunaHorizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (LIVRE(linhaHorizontal, colunaHorizontal + i))
                tabuleiro[linhaHorizontal][colunaHorizontal + i] = NAVIO;
        }
    }

    // Navio vertical
    if (linhaVertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (LIVRE(linhaVertical + i, colunaVertical))
                tabuleiro[linhaVertical + i][colunaVertical] = NAVIO;
        }
    }

    // Navio diagonal ↘
    if (linhaDiagonal1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        colunaDiagonal1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (LIVRE(linhaDiagonal1 + i, colunaDiagonal1 + i))
                tabuleiro[linhaDiagonal1 + i][colunaDiagonal1 + i] = NAVIO;
        }
    }

    // Navio diagonal ↙
    if (linhaDiagonal2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
        colunaDiagonal2 - (TAMANHO_NAVIO - 1) >= 0) {
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (LIVRE(linhaDiagonal2 + i, colunaDiagonal2 - i))
                tabuleiro[linhaDiagonal2 + i][colunaDiagonal2 - i] = NAVIO;
        }
    }

    // Criação das matrizes de habilidade (Cone, Cruz e Octaedro)
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // --- Habilidade: Cone (forma piramidal apontando para baixo) ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= TAM_HABILIDADE / 2 - i && j <= TAM_HABILIDADE / 2 + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // --- Habilidade: Cruz ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // --- Habilidade: Octaedro (losango) ---
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - TAM_HABILIDADE / 2) + abs(j - TAM_HABILIDADE / 2) <= TAM_HABILIDADE / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    // Define as posições centrais das habilidades no tabuleiro
    int origemConeLinha = 2, origemConeColuna = 5;
    int origemCruzLinha = 6, origemCruzColuna = 2;
    int origemOctaedroLinha = 7, origemOctaedroColuna = 7;

    // Função genérica: sobrepõe matriz de habilidade no tabuleiro
    // (centra a matriz no ponto de origem e marca com valor 5)
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            int linhaAlvo, colunaAlvo;

            // ---- Cone ----
            linhaAlvo = origemConeLinha + i - TAM_HABILIDADE / 2;
            colunaAlvo = origemConeColuna + j - TAM_HABILIDADE / 2;
            if (linhaAlvo >= 0 && linhaAlvo < TAMANHO_TABULEIRO &&
                colunaAlvo >= 0 && colunaAlvo < TAMANHO_TABULEIRO &&
                cone[i][j] == 1) {
                if (tabuleiro[linhaAlvo][colunaAlvo] != NAVIO)
                    tabuleiro[linhaAlvo][colunaAlvo] = HABILIDADE;
            }

            // ---- Cruz ----
            linhaAlvo = origemCruzLinha + i - TAM_HABILIDADE / 2;
            colunaAlvo = origemCruzColuna + j - TAM_HABILIDADE / 2;
            if (linhaAlvo >= 0 && linhaAlvo < TAMANHO_TABULEIRO &&
                colunaAlvo >= 0 && colunaAlvo < TAMANHO_TABULEIRO &&
                cruz[i][j] == 1) {
                if (tabuleiro[linhaAlvo][colunaAlvo] != NAVIO)
                    tabuleiro[linhaAlvo][colunaAlvo] = HABILIDADE;
            }

            // ---- Octaedro ----
            linhaAlvo = origemOctaedroLinha + i - TAM_HABILIDADE / 2;
            colunaAlvo = origemOctaedroColuna + j - TAM_HABILIDADE / 2;
            if (linhaAlvo >= 0 && linhaAlvo < TAMANHO_TABULEIRO &&
                colunaAlvo >= 0 && colunaAlvo < TAMANHO_TABULEIRO &&
                octaedro[i][j] == 1) {
                if (tabuleiro[linhaAlvo][colunaAlvo] != NAVIO)
                    tabuleiro[linhaAlvo][colunaAlvo] = HABILIDADE;
            }
        }
    }

    //  Exibe o tabuleiro completo com letras no cabeçalho
    printf("\n===== TABULEIRO FINAL - BATALHA NAVAL COM HABILIDADES =====\n\n");

    printf("    ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %c ", 'A' + j);
    }
    printf("\n");

    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf(" 0 "); // Água
            else if (tabuleiro[i][j] == NAVIO)
                printf(" 3 "); // Navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf(" 5 "); // Área afetada
        }
        printf("\n");
    }

    printf("\nLegenda: . = Água | 3 = Navio | 5 = Área de Efeito da Habilidade\n");

    return 0;
}
