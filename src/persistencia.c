#include <stdio.h>
#include <string.h>
#include "../include/persistencia.h"

// Adiciona um registro no final do arquivo
int salvarRegistro(const char *arquivo, void *registro, size_t tamanho) {
    FILE *arq = fopen(arquivo, "ab"); // "ab" = append binario (adiciona no final)
    if (arq == NULL) {
        printf("Erro ao abrir arquivo %s para salvar!\n", arquivo);
        return 0;
    }

    fwrite(registro, tamanho, 1, arq);
    fclose(arq);
    return 1;
}

// Le todos os registros do arquivo para dentro de um vetor.
// Retorna quantos registros foram lidos.
int lerTodosRegistros(const char *arquivo, void *vetor, size_t tamanho, int maxRegistros) {
    FILE *arq = fopen(arquivo, "rb");
    if (arq == NULL) {
        return 0; // arquivo ainda nao existe = nenhum registro
    }

    int total = 0;
    char *ptr = (char *) vetor;

    while (total < maxRegistros && fread(ptr + (total * tamanho), tamanho, 1, arq) == 1) {
        total++;
    }

    fclose(arq);
    return total;
}

// Sobrescreve um registro em uma posicao especifica do arquivo (baseado
// em indice, comecando em 0). Usado para atualizar (ex: check-out).
int atualizarRegistro(const char *arquivo, void *registroAtualizado, size_t tamanho, int posicao) {
    FILE *arq = fopen(arquivo, "r+b"); // le e escreve, sem apagar o arquivo
    if (arq == NULL) {
        printf("Erro ao abrir arquivo %s para atualizar!\n", arquivo);
        return 0;
    }

    // Move o "cursor" ate a posicao certa dentro do arquivo
    fseek(arq, posicao * tamanho, SEEK_SET);
    fwrite(registroAtualizado, tamanho, 1, arq);

    fclose(arq);
    return 1;
}

// Conta quantos registros existem no arquivo, sem carregar tudo na memoria
int contarRegistros(const char *arquivo, size_t tamanho) {
    FILE *arq = fopen(arquivo, "rb");
    if (arq == NULL) {
        return 0;
    }

    fseek(arq, 0, SEEK_END);   // vai para o final do arquivo
    long tamanhoArquivo = ftell(arq); // pega a posicao (= tamanho em bytes)
    fclose(arq);

    return (int) (tamanhoArquivo / tamanho);
}
