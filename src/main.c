#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/signer.h" 

void agente_decidir(const char *json_response, const char *hex_sig) 
{

    char *result_ptr = strstr(json_response, "\"result\":\"");

    if (result_ptr) {

        if (strstr(result_ptr, "\"result\":\"0x0\"")) {
            printf("\n[ AGENTE ] Estado: Saldo 0x0. Modo ahorro de energía activado...\n");
        } 

        else {
            printf("\n[ AGENTE ] Estado: Fondos detectados on-chain!\n");
            printf("[ AGENTE ] Acción: Generando ticket de pago x402 para API de Cómputo...\n");
            

            char *pago_sig = generar_cadena("PAGO_DE_SERVICIO_AVALANCHE_2026");
            if (pago_sig) {
                printf("[ AGENTE ] ✅ Pago Autorizado. Hash de transacción local: 0x%s\n", pago_sig);
                free(pago_sig);
            }
        }
    } else {
        printf("\n[ AGENTE ] ❌ ERROR: Respuesta RPC inválida o malformada.\n");
    }
}

int main() {
    const char *url = "https://api.avax-test.network/ext/bc/C/rpc";
    

    char *hex_sig = generar_cadena("Aleph Hackathon 2026");
    if (!hex_sig) {
        fprintf(stderr, "Error crítico: Fallo en el motor criptográfico.\n");
        return 1;
    }


    unveil("/usr/bin/curl", "x");
    unveil("/usr/local/bin/curl", "x");
    unveil("/bin/sh", "x");               
    unveil("/usr/lib", "r");
    unveil("/usr/local/lib", "r");
    unveil("/usr/libexec/ld.so", "r");
    unveil("/etc/ssl", "r");              
    unveil("/etc/resolv.conf", "r");      
    unveil("/etc/hosts", "r");
    unveil(NULL, NULL);                   

    
    char data[512];
    snprintf(data, sizeof(data),
        "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"0x8db97C7cEcE249c2b98bDC0226Cc4C2A57BF52FC\", \"latest\"],\"id\":1}");

    
    if (pledge("stdio exec rpath proc inet dns", NULL) == -1) {
        perror("pledge");
        free(hex_sig);
        return -1;
    }

    
    char command[1024];
    
    snprintf(command, sizeof(command), "curl -k -s -X POST -H \"Content-Type: application/json\" -d '%s' %s", data, url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        free(hex_sig);
        return 1;
    }

    char response[2048]; 
    memset(response, 0, sizeof(response));

    if (fgets(response, sizeof(response), fp) == NULL) {
        printf("[ ERROR ] No se recibió respuesta del nodo RPC.\n");
    }

    pclose(fp);


    printf("\n---- UvlAuth Agent System (ERC-8004 Logic) ----\n");
    printf("Respuesta RPC: %s\n", response);
    
    agente_decidir(response, hex_sig);


    free(hex_sig);
    return 0;
}
