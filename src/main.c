
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/signer.h" 

void agente_decidir(const char *json_response, const char *hex_sig) {
    
    if (strstr(json_response, "\"result\":\"0x0\""))
	{
		printf("[ AGENTE ] Estado: Fondos Insuficientes. Esperando recarga...\n");
    } else {
        printf("[ AGENTE ] Estado: Fondos detectados. Ejecutando firma de pago x402...\n");
        printf("[ AGENTE ] Autorizando con firma: 0x%s\n", hex_sig);
    }
}

int main() {
    const char *url = "https://api.avax-test.network/ext/bc/C/rpc";
    
    char *hex_sig = generar_cadena("Aleph Hackathon 2026");
    if(!hex_sig) {
        fprintf(stderr, "Error: No se pudo generar la firma.\n");
        return 1;
    }

    char data[512];
    
    snprintf(data, sizeof(data),
        "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"0x8db97C7cEcE249c2b98bDC0226Cc4C2A57BF52FC\", \"latest\"],\"id\":1}");

 
if (pledge("stdio exec rpath proc inet dns", NULL) == -1) {
    perror("pledge");
    free(hex_sig);
    return -1;
}

    
    char command[1024];
    snprintf(command, sizeof(command), "curl -s -X POST -H \"Content-Type: application/json\" -d '%s' %s", data, url);

    
    FILE *fp = popen(command, "r");
    if(fp == NULL) {
        perror("popen");
        free(hex_sig);
        return 1;
    }

    char response[1024];
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
