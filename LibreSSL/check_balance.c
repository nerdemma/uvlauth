#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/signer.h"

// Definición de colores ANSI (Paleta Nord/Aurora)
#define CLR_RESET  "\x1b[0m"
#define CLR_CYAN   "\x1b[36m"   // Frost (Agente)
#define CLR_GREEN  "\x1b[32m"   // Aurora Green (OK)
#define CLR_YELLOW "\x1b[33m"   // Aurora Yellow (Warn)
#define CLR_RED    "\x1b[31m"   // Aurora Red (Error)
#define CLR_BOLD   "\x1b[1m"

void agente_decidir(const char *json_response, const char *hex_sig)
{
    // Buscamos el inicio del campo "result"
    char *result_ptr = strstr(json_response, "\"result\":\"");

    if (result_ptr) {
        // Caso: Saldo 0x0
        if (strstr(result_ptr, "\"result\":\"0x0\"")) {
            printf(CLR_YELLOW "[ AGENTE ] Estado: Fondos Insuficientes. Modo ahorro activado." CLR_RESET "\n");
        } 
        // Caso: Hay fondos
        else {
            printf(CLR_GREEN CLR_BOLD "[ AGENTE ] Estado: Fondos detectados!" CLR_RESET "\n");
            printf(CLR_CYAN "[ AGENTE ] Acción: Ejecutando firma de pago x402..." CLR_RESET "\n");
            
            // Usamos la firma generada al inicio
            printf(CLR_GREEN CLR_BOLD "[ OK ] Autorizado con firma: 0x%s" CLR_RESET "\n", hex_sig);
        }
    } else {
        printf(CLR_RED "[ ERROR ] Respuesta RPC inválida o vacía." CLR_RESET "\n");
    }
}

int main()
{
    // 1. Inicialización e Identidad
    const char *url = "https://api.avax-test.network/ext/bc/C/rpc";
    char *hex_sig = generar_cadena("Aleph Hackathon 2026");

    if(!hex_sig) {
        fprintf(stderr, CLR_RED "Error: No se pudo generar la firma" CLR_RESET "\n");
        return 1;
    }

    // 2. Seguridad de archivos (Unveil)
    unveil("/usr/bin/curl", "x");
    unveil("/usr/local/bin/curl", "x");
    unveil("/bin/sh", "x");
    unveil("/usr/lib", "r");
    unveil("/usr/local/lib", "r");
    unveil("/usr/libexec/ld.so", "r");
    unveil("/etc/ssl", "r");
    unveil("/etc/resolv.conf", "r");
    unveil(NULL, NULL);

    // 3. Payload RPC
    char data[512];
    snprintf(data, sizeof(data),
        "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"0x8db97C7cEcE249c2b98bDC0226Cc4C2A57BF52FC\", \"latest\"],\"id\":1}");

    // 4. Seguridad de procesos (Pledge)
    if(pledge("stdio exec rpath proc inet dns", NULL) == -1) {
        perror("pledge");
        free(hex_sig);
        return -1;
    }

    // 5. Ejecución del comando de red
    char command[1024];
    snprintf(command, sizeof(command), "curl -k -s -X POST -H \"Content-Type: application/json\" -d '%s' %s", data, url);

    FILE *fp = popen(command, "r");
    if(fp == NULL) {
        perror("popen");
        free(hex_sig);
        return 1;
    }

    char response[1024];
    memset(response, 0, sizeof(response));
    fgets(response, sizeof(response), fp);
    pclose(fp);

    // 6. UI en Terminal (Estilo Landing Page)
    printf("\n" CLR_BOLD CLR_CYAN "---- UvlAuth Agent System (ERC-8004 Logic) ----" CLR_RESET "\n");
    if (strlen(response) > 0) {
        printf(CLR_CYAN "[ INFO ]" CLR_RESET " Respuesta RPC: %s\n", response);
    }
    
    agente_decidir(response, hex_sig);

    printf(CLR_CYAN "------------------------------------------------" CLR_RESET "\n");

    free(hex_sig);
    return 0;
}
