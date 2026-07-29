#include <stdio.h>
#include <string.h>
#include "../include/reserva.h"
#include "../include/quarto.h"
#include "../include/persistencia.h"

#define MAX_RESERVAS 100

static Reserva reservas[MAX_RESERVAS];
static int totalReservas = 0;
static int carregado = 0;

static void carregarReservas(void) {
    if (carregado) return;
    carregado = 1;
    totalReservas = lerTodosRegistros(ARQ_RESERVAS, reservas, sizeof(Reserva), MAX_RESERVAS);
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

    salvarRegistro(ARQ_RESERVAS, &nova, sizeof(Reserva));

    atualizarStatusQuarto(numeroQuarto, 1);

    printf("Check-in realizado! Reserva #%d\n", nova.idReserva);
}

void fazerCheckOut(int idReserva, const char *data) {
    carregarReservas();

    int indice = -1;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].idReserva == idReserva) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Reserva nao encontrada!\n");
        return;
    }

    if (reservas[indice].finalizada) {
        printf("Essa reserva ja foi finalizada!\n");
        return;
    }

    strncpy(reservas[indice].dataCheckOut, data, sizeof(reservas[indice].dataCheckOut) - 1);
    reservas[indice].dataCheckOut[sizeof(reservas[indice].dataCheckOut) - 1] = '\0';
    reservas[indice].finalizada = 1;

    atualizarRegistro(ARQ_RESERVAS, &reservas[indice], sizeof(Reserva), indice);

    atualizarStatusQuarto(reservas[indice].numeroQuarto, 0);

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
