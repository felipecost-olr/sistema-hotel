#include <stdio.h>
#include <string.h>
#include "../include/quarto.h"
#include "../include/persistencia.h"

static Quarto quartos[NUM_ANDARES][QUARTOS_POR_ANDAR];
static int carregado = 0;

static void criarQuartosPadrao(void) {
    int andar, pos;
    for (andar = 0; andar < NUM_ANDARES; andar++) {
        for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
            quartos[andar][pos].numero = (andar + 1) * 100 + (pos + 1);
            quartos[andar][pos].andar = andar + 1;
            quartos[andar][pos].status = 0;
            quartos[andar][pos].valorDiaria = 150.0;
        }
    }
}

void inicializarMapaQuartos(void) {
    if (carregado) return;
    carregado = 1;

    int totalLido = lerTodosRegistros(ARQ_QUARTOS, quartos,
                                       sizeof(Quarto), NUM_ANDARES * QUARTOS_POR_ANDAR);

    if (totalLido == 0) {
        criarQuartosPadrao();
        // grava todos os quartos padrao, um por um
        int andar, pos;
        for (andar = 0; andar < NUM_ANDARES; andar++) {
            for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
                salvarRegistro(ARQ_QUARTOS, &quartos[andar][pos], sizeof(Quarto));
            }
        }
    }
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

void atualizarStatusQuarto(int numero, int novoStatus) {
    int andar, pos, indice = 0;
    for (andar = 0; andar < NUM_ANDARES; andar++) {
        for (pos = 0; pos < QUARTOS_POR_ANDAR; pos++) {
            if (quartos[andar][pos].numero == numero) {
                quartos[andar][pos].status = novoStatus;
                atualizarRegistro(ARQ_QUARTOS, &quartos[andar][pos], sizeof(Quarto), indice);
                return;
            }
            indice++;
        }
    }
    printf("Quarto %d nao encontrado!\n", numero);
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
