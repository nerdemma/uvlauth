
#include "../lib/signer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>

CryptoContext* signer_init()
{
CryptoContext *ctx = malloc(sizeof(CryptoContext));
if(!ctx) return NULL;
ctx->key = EC_KEY_new_by_curve_name(NID_secp256k1);
        if (!ctx->key || !EC_KEY_generate_key(ctx->key))
        {
        free(ctx);
        return NULL;
        }
return ctx;
}


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
        
        hex_output = malloc((sig_len * 2) + 1);
        if (hex_output) {
            for (unsigned int i = 0; i < sig_len; i++) {
                sprintf(&hex_output[i * 2], "%02x", sig[i]);
            }
            hex_output[sig_len * 2] = '\0';
        }
    }


    free(sig);
    EC_KEY_free(key);

    return hex_output; 
}


char* signer_sign_message(CryptoContext *ctx, const char *message) 
{
unsigned char hash[SHA256_DIGEST_LENGTH];
unsigned char *sig;
unsigned int sig_len;

SHA256((unsigned char*)message, strlen(message), hash);
sig_len = ECDSA_size(ctx-> key);
sig = calloc(1, sig_len);
if(!sig) return NULL;
      
        if(!ECDSA_sign(0, hash, SHA256_DIGEST_LENGTH, sig, &sig_len, ctx->key))
        {
        free(sig);
        return NULL;
        }

// convertir a hex
char *hex_sig = malloc(sig_len * 2 + 1);

        for(unsigned int i = 0; i < sig_len; i++)
        {
        sprintf(&hex_sig[i * 2], "%02x", sig[i]);
        }
hex_sig[sig_len * 2]='\0';
free(sig);
return hex_sig;
}

void signer_free(CryptoContext *ctx)
{
        if(ctx)
        {
        if(ctx -> key) EC_KEY_free(ctx->key);
        free(ctx);
        }
}

