#include <stdio.h>
#include <string.h>
#include "../include/hospede.h"
#include "../include/persistencia.h"

#define MAX_HOSPEDES 200

static Hospede hospedes[MAX_HOSPEDES];
static int totalHospedes = 0;
static int carregado = 0;

static void carregarHospedes(void) {
    if (carregado) return;
    carregado = 1;
    totalHospedes = lerTodosRegistros(ARQ_HOSPEDES, hospedes, sizeof(Hospede), MAX_HOSPEDES);
}

void cadastrarHospede(Hospede h) {
    carregarHospedes();

    if (totalHospedes >= MAX_HOSPEDES) {
        printf("Limite de hospedes atingido!\n");
        return;
    }

    if (buscarHospedePorCpf(h.cpf) != NULL) {
        printf("Ja existe um hospede cadastrado com esse CPF!\n");
        return;
    }

    h.id = totalHospedes + 1;
    h.ativo = 1;

    hospedes[totalHospedes] = h;
    totalHospedes++;

    salvarRegistro(ARQ_HOSPEDES, &h, sizeof(Hospede));

    printf("Hospede cadastrado! ID: %d\n", h.id);
}

void listarHospedes(void) {
    carregarHospedes();

    printf("\n--- Hospedes Cadastrados ---\n");
    int encontrou = 0;

    for (int i = 0; i < totalHospedes; i++) {
        if (hospedes[i].ativo) {
            printf("ID: %d | Nome: %s | CPF: %s | Tel: %d\n",
                   hospedes[i].id,
                   hospedes[i].nome,
                   hospedes[i].cpf,
                   hospedes[i].telefone);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum hospede cadastrado.\n");
    }
}

Hospede* buscarHospedePorId(int id) {
    carregarHospedes();

    for (int i = 0; i < totalHospedes; i++) {
        if (hospedes[i].id == id && hospedes[i].ativo) {
            return &hospedes[i];
        }
    }
    return NULL;
}

Hospede* buscarHospedePorCpf(const char *cpf) {
    carregarHospedes();

    for (int i = 0; i < totalHospedes; i++) {
        if (hospedes[i].ativo && strcmp(hospedes[i].cpf, cpf) == 0) {
            return &hospedes[i];
        }
    }
    return NULL;
}

void editarHospede(int id, Hospede novosDados) {
    carregarHospedes();

    for (int i = 0; i < totalHospedes; i++) {
        if (hospedes[i].id == id && hospedes[i].ativo) {
            novosDados.id = id;         // mantem o id original
            novosDados.ativo = 1;
            hospedes[i] = novosDados;

            atualizarRegistro(ARQ_HOSPEDES, &hospedes[i], sizeof(Hospede), i);

            printf("Hospede %d atualizado!\n", id);
            return;
        }
    }
    printf("Hospede nao encontrado!\n");
}

void removerHospede(int id) {
    carregarHospedes();

    for (int i = 0; i < totalHospedes; i++) {
        if (hospedes[i].id == id && hospedes[i].ativo) {
            hospedes[i].ativo = 0; // remocao logica (nao apaga do arquivo)

            atualizarRegistro(ARQ_HOSPEDES, &hospedes[i], sizeof(Hospede), i);

            printf("Hospede %d removido!\n", id);
            return;
        }
    }
    printf("Hospede nao encontrado!\n");
}
