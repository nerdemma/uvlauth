# Compilador y banderas
CC = cc
CFLAGS = -O2 -Wall
# -I añade la carpeta de las cabeceras para que encuentre signer.h
INCLUDES = -I/Avalanche/lib -I./src

# Directorio de librerías y las librerías a enlazar
# -L añade la ruta de tus librerías personalizadas
LDFLAGS = -L/Avalanche/lib
LIBS = -lcrypto

# Archivos fuente (asumiendo que estás parado en la raíz del proyecto)
# Agregamos check_balance.c que mencionaste
SRC = src/main.c LibreSSL/check_balance.c src/signer.c
OBJ = uvlauth

# Regla principal
all:
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OBJ) $(SRC) $(LDFLAGS) $(LIBS)

# Regla para limpiar el binario
clean:
	rm -f $(OBJ)

# Regla de ayuda para depuración (opcional pero útil)
debug:
	$(CC) -g $(INCLUDES) -o $(OBJ)_debug $(SRC) $(LDFLAGS) $(LIBS)
