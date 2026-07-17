#ifndef RESERVA_H
#define RESERVA_H

typedef struct {
    int idReserva;
    int idHospede;
    int numeroQuarto;
    char dataCheckIn[11];  // "DD/MM/AAAA"
    char dataCheckOut[11]; // "DD/MM/AAAA" ou "" se ainda hospedado
    int finalizada; // 0 = em andamento, 1 = finalizada
} Reserva;

// Responsável: Pessoa 3
void fazerCheckIn(int idHospede, int numeroQuarto, const char *data);
void fazerCheckOut(int idReserva, const char *data);
void listarReservasAtivas(void);
Reserva* buscarReservaPorId(int idReserva);
Reserva* buscarReservaAtivaPorQuarto(int numeroQuarto);

#endif
