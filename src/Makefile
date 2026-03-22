CC = cc
CFLAGS = -O2 -Wall
LIBS = -lcrypto
SRC = main.c signer.c
OBJ = uvlauth

# La regla 'all' debe tener un TAB antes del comando
all:
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC) $(LIBS)

# La regla 'clean' debe tener un TAB antes del comando
clean:
	rm -f $(OBJ)
