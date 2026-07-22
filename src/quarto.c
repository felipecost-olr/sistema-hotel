#include <stdio.h>
#include <string.h>
#include "../include/quarto.h"

#define ARQUIVO_QUARTOS "data/quartos.dat"

static Quarto quartos[NUM_ANDARES][QUARTOS_POR_ANDAR];
static int carregado = 0;

// Cria os quartos: numero baseado no andar (ex: andar 1 = 101 a 110)
static void criarQuartosPadrao(void) {
    int andar, pos;
    for (andar = 0; andar < NUM_ANDARES; andar++) {
        for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
            quartos[andar][pos].numero = (andar + 1) * 100 + (pos + 1);
            quartos[andar][pos].andar = andar + 1;
            quartos[andar][pos].status = 0; // livre
            quartos[andar][pos].valorDiaria = 150.0; // valor padrao
        }
    }
}

// Salva a matriz inteira no arquivo binario
static void salvarQuartos(void) {
    FILE *arq = fopen(ARQUIVO_QUARTOS, "wb");
    if (arq == NULL) {
        printf("Erro ao salvar quartos!\n");
        return;
    }
    fwrite(quartos, sizeof(Quarto), NUM_ANDARES * QUARTOS_POR_ANDAR, arq);
    fclose(arq);
}

// Le a matriz do arquivo. Se o arquivo nao existir ainda (primeira vez
// rodando o programa), cria os quartos padrao e ja salva no arquivo.
void inicializarMapaQuartos(void) {
    if (carregado) return;
    carregado = 1;

    FILE *arq = fopen(ARQUIVO_QUARTOS, "rb");
    if (arq == NULL) {
        criarQuartosPadrao();
        salvarQuartos();
        return;
    }

    fread(quartos, sizeof(Quarto), NUM_ANDARES * QUARTOS_POR_ANDAR, arq);
    fclose(arq);
}

void listarQuartos(void) {
    int andar, pos;
    for (andar = 0; andar < NUM_ANDARES; andar++) {
        for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
            printf("Quarto %d - Andar %d - Status: %d - R$ %.2f\n",
                   quartos[andar][pos].numero,
                   quartos[andar][pos].andar,
                   quartos[andar][pos].status,
                   quartos[andar][pos].valorDiaria);
        }
    }
}

void listarQuartosDisponiveis(void) {
    int andar, pos;
    for (andar = 0; andar < NUM_ANDARES; andar++) {
        for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
            if (quartos[andar][pos].status == 0) {
                printf("Quarto %d - Andar %d - R$ %.2f\n",
                       quartos[andar][pos].numero,
                       quartos[andar][pos].andar,
                       quartos[andar][pos].valorDiaria);
            }
        }
    }
}

Quarto* buscarQuartoPorNumero(int numero) {
    int andar, pos;
    for (andar = 0; andar < NUM_ANDARES; andar++) {
        for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
            if (quartos[andar][pos].numero == numero) {
                return &quartos[andar][pos];
            }
        }
    }
    return NULL;
}

// Funcao que o modulo de Reservas chama para marcar quarto ocupado/livre
void atualizarStatusQuarto(int numero, int novoStatus) {
    Quarto *q = buscarQuartoPorNumero(numero);
    if (q != NULL) {
        q->status = novoStatus;
        salvarQuartos(); // grava a mudanca no arquivo na hora
    } else {
        printf("Quarto %d nao encontrado!\n", numero);
    }
}

void imprimirMapaQuartos(void) {
    int andar, pos;
    printf("\n--- Mapa de Quartos ---\n");
    printf("(0 = livre, 1 = ocupado, 2 = manutencao)\n\n");
    for (andar = 0; andar < NUM_ANDARES; andar++) {
        printf("Andar %d: ", andar + 1);
        for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
            printf("[%d]%d  ", quartos[andar][pos].numero, quartos[andar][pos].status);
        }
        printf("\n");
    }
}
