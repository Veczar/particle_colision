# Kompilator i flagi
CC = gcc
CFLAGS = -O2 -Wall -fopenmp -Iinclude $(shell sdl2-config --cflags)
LDFLAGS = -lm $(shell sdl2-config --libs)

# Nazwa programu
TARGET = particle_sim

# Katalogi
SRC_DIR = src
DATA_DIR = data

# Pliki źródłowe i obiektowe
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Domyślny cel
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Reguła kompilacji pojedynczego pliku .c → .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Uruchomienie programu
run: $(TARGET)
	./$(TARGET)

# Tryb debugowania (z symbolami i bez optymalizacji)
debug: CFLAGS = -g -Wall -Iinclude $(shell sdl2-config --cflags)
debug: LDFLAGS = -lm $(shell sdl2-config --libs)
debug: clean $(TARGET)

# Czyszczenie
clean:
	rm -f $(OBJ) $(TARGET)

# Pełne czyszczenie (łącznie z klatkami)
cleanall: clean
	rm -f $(DATA_DIR)/*.ppm

.PHONY: all run clean cleanall debug