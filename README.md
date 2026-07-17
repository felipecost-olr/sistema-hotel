# Sistema de Hotel

Trabalho em grupo - sistema de gerenciamento de hotel em C, com persistência
em arquivos binários e mapa de quartos em matriz.

## Divisão de responsabilidades

| Pessoa | Módulo | Arquivos |
|---|---|---|
| 1 | Hóspedes | `include/hospede.h`, `src/hospede.c` |
| 2 | Quartos / Matriz | `include/quarto.h`, `src/quarto.c` |
| 3 | Reservas (check-in/out) | `include/reserva.h`, `src/reserva.c` |
| 4 | Persistência (arquivos .dat) | `include/persistencia.h`, `src/persistencia.c` |
| 5 | Menu / Integração | `src/main.c` |

**Regra de ouro:** os `.h` já têm os structs e as assinaturas das funções
combinadas. Não mude a assinatura de uma função sem avisar o grupo, porque
quem depende dela vai quebrar.

## Como cada um deve trabalhar (Git)

1. Clone o repositório:
   ```
   git clone https://github.com/felipecost-olr/sistema-hotel.git
   cd sistema-hotel
   ```

2. Crie uma branch com seu módulo:
   ```
   git checkout -b feature/hospede
   ```
   (troque `hospede` pelo seu módulo: `quarto`, `reserva`, `persistencia`, `main`)

3. Implemente só dentro do seu `.c`. Não edite o `.c` dos outros.

4. Suba suas alterações:
   ```
   git add src/SEU_ARQUIVO.c
   git commit -m "Implementa cadastro de hospede"
   git push origin feature/hospede
   ```

5. Abra um Pull Request no GitHub para a branch `main` e peça pra alguém revisar.

## Como compilar

```
make        # compila e gera o executável "hotel"
make run    # compila e já executa
make clean  # remove o executável
```

## Estrutura de pastas

```
sistema-hotel/
├── include/       -> arquivos .h (contratos/structs de cada módulo)
├── src/            -> arquivos .c (implementação)
├── data/           -> arquivos .dat gerados em tempo de execução
├── Makefile
└── README.md
```
