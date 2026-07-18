#include <stdio.h>
#include <string.h>
#include "../include/reserva.h"
#include "../include/quarto.h"

#define MAX_RESERVAS 100
#define ARQUIVO_RESERVAS "data/reservas.dat"

static Reserva reservas[MAX_RESERVAS];
static int totalReservas = 0;
static int carregado = 0;

// Carrega o arquivo pra dentro do vetor, na primeira vez que alguma
// funcao deste modulo for chamada.
static void carregarReservas(void) {
    if (carregado) return;
    carregado = 1;

    FILE *arq = fopen(ARQUIVO_RESERVAS, "rb");
    if (arq == NULL) {
        totalReservas = 0;
        return;
    }

    totalReservas = 0;
    while (fread(&reservas[totalReservas], sizeof(Reserva), 1, arq) == 1) {
        totalReservas++;
        if (totalReservas >= MAX_RESERVAS) break;
    }

    fclose(arq);
}

// Regrava o arquivo inteiro com o vetor atual.
static void salvarReservas(void) {
    FILE *arq = fopen(ARQUIVO_RESERVAS, "wb");
    if (arq == NULL) {
        printf("Erro ao salvar reservas!\n");
        return;
    }

    fwrite(reservas, sizeof(Reserva), totalReservas, arq);
    fclose(arq);
}

void fazerCheckIn(int idHospede, int numeroQuarto, const char *data) {
    carregarReservas();

    if (totalReservas >= MAX_RESERVAS) {
        printf("Limite de reservas atingido!\n");
        return;
    }

    if (buscarReservaAtivaPorQuarto(numeroQuarto) != NULL) {
        printf("Quarto %d ja esta ocupado!\n", numeroQuarto);
        return;
    }

    Reserva nova;
    nova.idReserva = totalReservas + 1;
    nova.idHospede = idHospede;
    nova.numeroQuarto = numeroQuarto;
    strncpy(nova.dataCheckIn, data, sizeof(nova.dataCheckIn) - 1);
    nova.dataCheckIn[sizeof(nova.dataCheckIn) - 1] = '\0';
    strcpy(nova.dataCheckOut, "");
    nova.finalizada = 0;

    reservas[totalReservas] = nova;
    totalReservas++;
    salvarReservas();

    atualizarStatusQuarto(numeroQuarto, 1);

    printf("Check-in realizado! Reserva #%d\n", nova.idReserva);
}

void fazerCheckOut(int idReserva, const char *data) {
    carregarReservas();

    Reserva *r = buscarReservaPorId(idReserva);
    if (r == NULL) {
        printf("Reserva nao encontrada!\n");
        return;
    }

    if (r->finalizada) {
        printf("Essa reserva ja foi finalizada!\n");
        return;
    }

    strncpy(r->dataCheckOut, data, sizeof(r->dataCheckOut) - 1);
    r->dataCheckOut[sizeof(r->dataCheckOut) - 1] = '\0';
    r->finalizada = 1;

    salvarReservas();

    atualizarStatusQuarto(r->numeroQuarto, 0);

    printf("Check-out realizado para a reserva #%d\n", idReserva);
}

void listarReservasAtivas(void) {
    carregarReservas();

    printf("\n--- Reservas Ativas ---\n");
    int encontrou = 0;

    for (int i = 0; i < totalReservas; i++) {
        if (!reservas[i].finalizada) {
            printf("Reserva #%d | Hospede ID: %d | Quarto: %d | Check-in: %s\n",
                   reservas[i].idReserva,
                   reservas[i].idHospede,
                   reservas[i].numeroQuarto,
                   reservas[i].dataCheckIn);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma reserva ativa no momento.\n");
    }
}

Reserva* buscarReservaPorId(int idReserva) {
    carregarReservas();

    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].idReserva == idReserva) {
            return &reservas[i];
        }
    }
    return NULL;
}

Reserva* buscarReservaAtivaPorQuarto(int numeroQuarto) {
    carregarReservas();

    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].numeroQuarto == numeroQuarto && !reservas[i].finalizada) {
            return &reservas[i];
        }
    }
    return NULL;
}
