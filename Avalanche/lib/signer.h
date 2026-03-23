#ifndef SIGNER_H
#define SIGNER_H

#include <openssl/ecdsa.h>

/*estructura para manejar el estado del firmador sin exponer SSL directamente*/
typedef struct{
EC_KEY *key;
}CryptoContext;

/*inicializa la libreria y genera las llaves*/
CryptoContext* signer_init();

/*funcion para generar cadena hash*/
char* generar_cadena(const char *input);



/*firma un mensaje y devuelve la firma en hex*/
char* signer_sign_message(CryptoContext *ctx, const char *message);
/*limpia la memoria*/
void signer_free(CryptoContext *ctx);

#endif
