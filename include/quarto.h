#ifndef QUARTO_H
#define QUARTO_H

#define NUM_ANDARES 5
#define QUARTOS_POR_ANDAR 10

typedef struct {
    int numero;
    int andar;
    int status; // 0 = livre, 1 = ocupado, 2 = manutencao
    float valorDiaria;
} Quarto;

// Responsável: Pessoa 2
void inicializarMapaQuartos(void);
void listarQuartos(void);
void listarQuartosDisponiveis(void);
Quarto* buscarQuartoPorNumero(int numero);
void atualizarStatusQuarto(int numero, int novoStatus);
void imprimirMapaQuartos(void); // imprime a matriz (andar x quarto)

#endif
