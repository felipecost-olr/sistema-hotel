#include <stdio.h>
#include <string.h>
#include "../include/hospede.h"
#include "../include/quarto.h"
#include "../include/reserva.h"

/* =====================================================================
 * TESTE AUTOMATIZADO DO SISTEMA DE HOTEL
 * ---------------------------------------------------------------------
 * Este arquivo NAO faz parte do sistema principal (nao é chamado pelo
 * main.c). Ele serve so para testar se os modulos estao funcionando
 * certo, sem precisar digitar nada manualmente.
 *
 * Como compilar e rodar (linha unica):
 *   gcc -Wall -Iinclude tests/teste.c src/hospede.c src/quarto.c src/reserva.c src/persistencia.c -o teste
 *   ./teste          (Linux/Mac)
 *   .\teste.exe      (Windows)
 *
 * IMPORTANTE: apaga os arquivos dentro de data/ antes de rodar o teste,
 * senao os resultados podem ficar errados (dados de execucoes antigas).
 * ===================================================================== */

static int totalTestes = 0;
static int testesPassaram = 0;

// Funcao auxiliar: compara o resultado esperado com o obtido e imprime
void verificar(const char *nomeTeste, int condicao) {
    totalTestes++;
    if (condicao) {
        testesPassaram++;
        printf("[PASSOU] %s\n", nomeTeste);
    } else {
        printf("[FALHOU] %s\n", nomeTeste);
    }
}

void testarHospedes(void) {
    printf("\n===== Testando modulo de Hospedes =====\n");

    Hospede h1;
    strcpy(h1.nome, "Felipe Costa");
    strcpy(h1.cpf, "11122233344");
    h1.telefone = 999999999;
    cadastrarHospede(h1);

    Hospede *encontrado = buscarHospedePorCpf("11122233344");
    verificar("Hospede cadastrado e encontrado por CPF", encontrado != NULL);

    if (encontrado != NULL) {
        verificar("Nome do hospede esta correto",
                   strcmp(encontrado->nome, "Felipe Costa") == 0);
    }

    Hospede *naoExiste = buscarHospedePorCpf("00000000000");
    verificar("Busca por CPF inexistente retorna NULL", naoExiste == NULL);

    // Tenta cadastrar o mesmo CPF de novo (deve ser bloqueado)
    Hospede h2;
    strcpy(h2.nome, "Outro Nome");
    strcpy(h2.cpf, "11122233344");
    h2.telefone = 888888888;
    int totalAntes = 0;
    Hospede *antesDuplicar = buscarHospedePorCpf("11122233344");
    if (antesDuplicar != NULL) totalAntes = antesDuplicar->id;
    cadastrarHospede(h2);
    Hospede *depoisDuplicar = buscarHospedePorCpf("11122233344");
    verificar("CPF duplicado nao gera novo cadastro",
               depoisDuplicar != NULL && depoisDuplicar->id == totalAntes);
}

void testarQuartos(void) {
    printf("\n===== Testando modulo de Quartos =====\n");

    inicializarMapaQuartos();

    Quarto *q101 = buscarQuartoPorNumero(101);
    verificar("Quarto 101 existe apos inicializar mapa", q101 != NULL);

    if (q101 != NULL) {
        verificar("Quarto 101 comeca livre (status 0)", q101->status == 0);
    }

    Quarto *inexistente = buscarQuartoPorNumero(999);
    verificar("Quarto inexistente retorna NULL", inexistente == NULL);

    atualizarStatusQuarto(101, 1);
    Quarto *q101depois = buscarQuartoPorNumero(101);
    verificar("Status do quarto 101 atualizado para ocupado",
               q101depois != NULL && q101depois->status == 1);

    // devolve o quarto ao estado livre para nao afetar o teste de reservas
    atualizarStatusQuarto(101, 0);
}

void testarReservas(void) {
    printf("\n===== Testando modulo de Reservas =====\n");

    fazerCheckIn(1, 102, "17/07/2026");
    Reserva *r = buscarReservaAtivaPorQuarto(102);
    verificar("Reserva criada e encontrada pelo quarto", r != NULL);

    Quarto *q102 = buscarQuartoPorNumero(102);
    verificar("Quarto 102 ficou ocupado apos check-in",
               q102 != NULL && q102->status == 1);

    // Tenta fazer check-in de novo no mesmo quarto (deve ser bloqueado)
    int totalAntes = 0;
    if (r != NULL) totalAntes = r->idReserva;
    fazerCheckIn(2, 102, "17/07/2026");
    Reserva *rDepois = buscarReservaAtivaPorQuarto(102);
    verificar("Quarto ja ocupado nao aceita novo check-in",
               rDepois != NULL && rDepois->idReserva == totalAntes);

    if (r != NULL) {
        int idReserva = r->idReserva;
        fazerCheckOut(idReserva, "18/07/2026");

        Reserva *rAtiva = buscarReservaAtivaPorQuarto(102);
        verificar("Reserva nao aparece mais como ativa apos checkout",
                   rAtiva == NULL);

        Quarto *q102depois = buscarQuartoPorNumero(102);
        verificar("Quarto 102 ficou livre apos checkout",
                   q102depois != NULL && q102depois->status == 0);
    }

    // Checkout de reserva que nao existe
    fazerCheckOut(9999, "18/07/2026"); // so deve imprimir erro, sem travar
    verificar("Checkout de reserva inexistente nao trava o programa", 1);
}

int main(void) {
    printf("############################################\n");
    printf("#   TESTE AUTOMATIZADO - SISTEMA DE HOTEL   #\n");
    printf("############################################\n");

    testarHospedes();
    testarQuartos();
    testarReservas();

    printf("\n============================================\n");
    printf("RESULTADO: %d de %d testes passaram\n", testesPassaram, totalTestes);
    if (testesPassaram == totalTestes) {
        printf("TUDO CERTO! Todos os testes passaram.\n");
    } else {
        printf("Atencao: %d teste(s) falharam.\n", totalTestes - testesPassaram);
    }
    printf("============================================\n");

    return (testesPassaram == totalTestes) ? 0 : 1;
}
