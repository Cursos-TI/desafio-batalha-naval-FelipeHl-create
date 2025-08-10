#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// --- Função para inicializar o tabuleiro com água (valor 0) ---
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// --- Função para verificar se a posição está ocupada ou fora dos limites ---
int verificarPosicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se a posição está fora dos limites
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return 0; // Posição inválida (fora dos limites)
    }
    // Verifica se a posição já está ocupada por um navio
    if (tabuleiro[linha][coluna] == NAVIO) {
        return 0; // Posição inválida (já ocupada)
    }
    return 1; // Posição válida
}

// --- Função para posicionar o navio no tabuleiro, com validação de sobreposição ---
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, char orientacao) {
    int posicoesValidas = 1; // Flag para verificar a validade de todas as posições
    
    // 1. Pré-verificação de todas as posições do navio
    if (orientacao == 'H') { // Horizontal
        if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            posicoesValidas = 0;
        } else {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (!verificarPosicao(tabuleiro, linhaInicial, colunaInicial + i)) {
                    posicoesValidas = 0;
                    break;
                }
            }
        }
    } else if (orientacao == 'V') { // Vertical
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            posicoesValidas = 0;
        } else {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (!verificarPosicao(tabuleiro, linhaInicial + i, colunaInicial)) {
                    posicoesValidas = 0;
                    break;
                }
            }
        }
    } else if (orientacao == 'D') { // Diagonal
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            posicoesValidas = 0;
        } else {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                if (!verificarPosicao(tabuleiro, linhaInicial + i, colunaInicial + i)) {
                    posicoesValidas = 0;
                    break;
                }
            }
        }
    } else {
        printf("Erro: Orientacao de navio invalida.\n");
        return;
    }

    // 2. Se todas as posições forem válidas, posicione o navio
    if (posicoesValidas) {
        if (orientacao == 'H') {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial][colunaInicial + i] = NAVIO;
            }
        } else if (orientacao == 'V') {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial + i][colunaInicial] = NAVIO;
            }
        } else if (orientacao == 'D') {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
            }
        }
        printf("Navio posicionado com sucesso.\n");
    } else {
        printf("Nao foi possivel posicionar o navio. Verifique os limites ou sobreposicao.\n");
    }
}

// --- Função para exibir o tabuleiro no console ---
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("  "); // Espaço para alinhar com o cabeçalho
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Imprime o cabeçalho de colunas
    }
    printf("\n");
    printf("  ---------------------\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d|", i); // Imprime o número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime o valor da posição
        }
        printf("|\n");
    }
    printf("  ---------------------\n");
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    inicializarTabuleiro(tabuleiro);
    
    // Posicionamento de quatro navios
    printf("Tentando posicionar navios...\n\n");
    
    // Navio 1 (Horizontal)
    posicionarNavio(tabuleiro, 1, 2, 'H');
    
    // Navio 2 (Vertical)
    posicionarNavio(tabuleiro, 5, 5, 'V');
    
    // Navio 3 (Diagonal)
    posicionarNavio(tabuleiro, 2, 6, 'D');
    
    // Navio 4 (Diagonal - Verificando sobreposição com o navio 1)
    // Este navio deveria dar erro pois se sobrepõe ao primeiro navio horizontal
    posicionarNavio(tabuleiro, 0, 3, 'D');

    // Navio 4 (Diagonal - Posição válida)
    posicionarNavio(tabuleiro, 6, 1, 'D');
    
    printf("\n--- Exibindo Tabuleiro Final ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}