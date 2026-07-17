#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <stdio.h>

#define ARQ_HOSPEDES  "data/hospedes.dat"
#define ARQ_QUARTOS   "data/quartos.dat"
#define ARQ_RESERVAS  "data/reservas.dat"

// Responsável: Pessoa 4
// Funções genéricas de gravação/leitura binária.
// Cada módulo (hospede.c, quarto.c, reserva.c) chama estas funções
// passando o struct e o arquivo correspondente.

int salvarRegistro(const char *arquivo, void *registro, size_t tamanho);
int lerTodosRegistros(const char *arquivo, void *vetor, size_t tamanho, int maxRegistros);
int atualizarRegistro(const char *arquivo, void *registroAtualizado, size_t tamanho, int posicao);
int contarRegistros(const char *arquivo, size_t tamanho);

#endif
