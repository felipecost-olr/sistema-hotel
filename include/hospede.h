#ifndef HOSPEDE_H
#define HOSPEDE_H

#define MAX_NOME 50
#define MAX_CPF 15

typedef struct {
    int id;
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    int telefone;
    int ativo; // 1 = ativo, 0 = removido
} Hospede;

// Responsável: Pessoa 1
void cadastrarHospede(Hospede h);
void listarHospedes(void);
Hospede* buscarHospedePorId(int id);
Hospede* buscarHospedePorCpf(const char *cpf);
void editarHospede(int id, Hospede novosDados);
void removerHospede(int id);

#endif
