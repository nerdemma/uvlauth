CC = cc
CFLAGS = -Wall -Wextra -O2 -I../lib
LIBS = -lssl -lcrypto

# Definimos la ubicación del header para que Make sepa dónde vigilar cambios
HEADER = ../lib/signer.h

all: test_signer

# Enlazamos el test con la librería estática
test_signer: test_signer.c libsigner.a
	$(CC) $(CFLAGS) main.c -o main -L. -lsigner $(LIBS)

# Creamos la librería estática
libsigner.a: signer.o
	ar rcs libsigner.a signer.o

# Compilamos el objeto indicando explícitamente la dependencia del header en ../lib
signer.o: signer.c $(HEADER)
	$(CC) $(CFLAGS) -c signer.c

clean:
	rm -f *.o *.a test_signer
