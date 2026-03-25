#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../Avalanche/lib/signer.h"

// Colores para una salida limpia
#define CLR_RESET  "\x1b[0m"
#define CLR_CYAN   "\x1b[36m"
#define CLR_GREEN  "\x1b[32m"
#define CLR_YELLOW "\x1b[33m"
#define CLR_RED    "\x1b[31m"
#define CLR_BOLD   "\x1b[1m"

// Esta función ahora es genérica y eficiente
int ejecutar_consulta_rpc(const char *wallet, const char *url, char *out_response, size_t res_len) {
    char data[512];
    char command[1024];

    snprintf(data, sizeof(data),
             "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"%s\", \"latest\"],\"id\":1}", 
             wallet);

    // Usamos -k solo si es estrictamente necesario por certificados viejos
    snprintf(command, sizeof(command), 
             "curl -s -X POST -H \"Content-Type: application/json\" -d '%s' %s", 
             data, url);

    FILE *fp = popen(command, "r");
    if (!fp) return -1;

    if (fgets(out_response, res_len, fp) == NULL) {
        pclose(fp);
        return -1;
    }

    return pclose(fp);
}

void agente_visual_decidir(const char *json_response, const char *hex_sig) {
    char *result_ptr = strstr(json_response, "\"result\":\"");
    
    printf("\n" CLR_BOLD CLR_CYAN "---- UvlAuth Agent System (ERC-8004 Logic) ----" CLR_RESET "\n");
    
    if (result_ptr) {
        if (strstr(result_ptr, "\"result\":\"0x0\"")) {
            printf(CLR_YELLOW "[ AGENTE ] Estado: Fondos Insuficientes." CLR_RESET "\n");
        } else {
            printf(CLR_GREEN CLR_BOLD "[ AGENTE ] Estado: Fondos detectados!" CLR_RESET "\n");
            printf(CLR_CYAN "[ AGENTE ] Firma x402: 0x%s" CLR_RESET "\n", hex_sig);
        }
    } else {
        printf(CLR_RED "[ ERROR ] Respuesta RPC inválida." CLR_RESET "\n");
    }
    printf(CLR_CYAN "------------------------------------------------" CLR_RESET "\n");
}
