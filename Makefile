CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/hospede.c src/quarto.c src/reserva.c src/persistencia.c
OUT = hotel

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
