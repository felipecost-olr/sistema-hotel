#include <stdio.h>
#include <string.h>
#include "../include/hospede.h"
#include "../include/quarto.h"
#include "../include/reserva.h"
#include "../include/persistencia.h"

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu(void) {
    printf("\n===== SISTEMA DE HOTEL =====\n");
    printf("1 - Cadastrar hospede\n");
    printf("2 - Listar hospedes\n");
    printf("3 - Ver mapa de quartos\n");
    printf("4 - Fazer check-in\n");
    printf("5 - Fazer check-out\n");
    printf("6 - Listar reservas ativas\n");
    printf("7 - Listar quartos disponiveis\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

int main(void) {
    int opcao;

    inicializarMapaQuartos();

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: {
                Hospede h;
                printf("Nome: ");
                fgets(h.nome, MAX_NOME, stdin);
                h.nome[strcspn(h.nome, "\n")] = '\0'; // remove o \n do final

                printf("CPF: ");
                fgets(h.cpf, MAX_CPF, stdin);
                h.cpf[strcspn(h.cpf, "\n")] = '\0';

                printf("Telefone (somente numeros): ");
                scanf("%d", &h.telefone);
                limparBufferEntrada();

                cadastrarHospede(h);
                break;
            }
            case 2:
                listarHospedes();
                break;
            case 3:
                imprimirMapaQuartos();
                break;
            case 4: {
                int idHospede, numeroQuarto;
                char data[11];

                printf("ID do hospede: ");
                scanf("%d", &idHospede);
                limparBufferEntrada();

                printf("\nQuartos disponiveis:\n");
                listarQuartosDisponiveis();

                printf("\nNumero do quarto: ");
                scanf("%d", &numeroQuarto);
                limparBufferEntrada();

                printf("Data do check-in (DD/MM/AAAA): ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';

                fazerCheckIn(idHospede, numeroQuarto, data);
                break;
            }
            case 5: {
                int idReserva;
                char data[11];

                printf("Numero da reserva: ");
                scanf("%d", &idReserva);
                limparBufferEntrada();

                printf("Data do check-out (DD/MM/AAAA): ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';

                fazerCheckOut(idReserva, data);
                break;
            }
            case 6:
                listarReservasAtivas();
                break;
            case 7:
                listarQuartosDisponiveis();
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
