#include <stdio.h>
#include <stdlib.h>
#include "../lib/signer.h"

int main() {
    printf("--- Iniciando Prueba de Aleph Crypto Signer Library ---\n");

    // 1. Inicializar el contexto (genera par de llaves secp256k1 internamente)
    printf("[1/4] Inicializando contexto criptográfico...\n");
    CryptoContext *ctx = signer_init();
    if (!ctx) {
        fprintf(stderr, "Error: No se pudo inicializar el contexto de cifrado.\n");
        return 1;
    }
    printf("      [OK] Contexto inicializado (llaves generadas).\n");

    // 2. Definir un mensaje de prueba
    // En el futuro, esto podría ser una transacción serializada de Avalanche
    const char *mensaje = "Esta es una transacción de prueba para Avalanche C-Chain";
    printf("[2/4] Mensaje a firmar: '%s'\n", mensaje);

    // 3. Firmar el mensaje
    printf("[3/4] Generando firma ECDSA...\n");
    char *firma_hex = signer_sign_message(ctx, mensaje);
    if (!firma_hex) {
        fprintf(stderr, "Error: Fallo al firmar el mensaje.\n");
        signer_free(ctx);
        return 1;
    }

    // 4. Mostrar resultado
    printf("      [OK] Firma generada exitosamente (formato HEX DER):\n\n");
    printf("%s\n\n", firma_hex);

    // Limpieza
    printf("[4/4] Limpiando memoria y cerrando...\n");
    free(firma_hex); // Debemos liberar la cadena HEX devuelta por la librería
    signer_free(ctx);

    printf("--- Prueba finalizada exitosamente ---\n");
    return 0;
}
