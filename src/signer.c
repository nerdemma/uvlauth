
#include "../lib/signer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>


char* generar_cadena(const char *input) {
    if (!input) return NULL; 

    EC_KEY *key = NULL;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char *sig = NULL;
    unsigned int sig_len = 0;
    char *hex_output = NULL;

    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (!key || !EC_KEY_generate_key(key)) {
        if (key) EC_KEY_free(key);
        return NULL;
    }

    SHA256((const unsigned char*)input, strlen(input), hash);

    sig_len = ECDSA_size(key);
    sig = calloc(1, sig_len);
    if (!sig) {
        EC_KEY_free(key);
        return NULL;
    }

    if (ECDSA_sign(0, hash, SHA256_DIGEST_LENGTH, sig, &sig_len, key)) {

        hex_output = calloc(1, (sig_len * 2) + 1);
        if (hex_output) {
            for (unsigned int i = 0; i < sig_len; i++) {

                snprintf(&hex_output[i * 2], 3, "%02x", sig[i]);
            }
        }
    }

    free(sig);
    EC_KEY_free(key);
    return hex_output; 
}


