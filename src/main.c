#include <stdio.h>
#include "../include/hospede.h"
#include "../include/quarto.h"
#include "../include/reserva.h"
#include "../include/persistencia.h"

// Responsável: Pessoa 5
// Este arquivo integra todos os módulos através do menu principal.
// Só deve ser mexido depois que os outros módulos tiverem funções prontas.

void exibirMenu(void) {
    printf("\n===== SISTEMA DE HOTEL =====\n");
    printf("1 - Cadastrar hospede\n");
    printf("2 - Listar hospedes\n");
    printf("3 - Ver mapa de quartos\n");
    printf("4 - Fazer check-in\n");
    printf("5 - Fazer check-out\n");
    printf("6 - Listar reservas ativas\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

int main(void) {
    int opcao;

    inicializarMapaQuartos();

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // TODO: chamar cadastrarHospede()
                break;
            case 2:
                listarHospedes();
                break;
            case 3:
                imprimirMapaQuartos();
                break;
            case 4:
                // TODO: chamar fazerCheckIn()
                break;
            case 5:
                // TODO: chamar fazerCheckOut()
                break;
            case 6:
                listarReservasAtivas();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
