#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../Avalanche/lib/signer.h"

// Declaramos las funciones que están en check_balance.c
int ejecutar_consulta_rpc(const char *wallet, const char *url, char *out_response, size_t res_len);
void agente_visual_decidir(const char *json_response, const char *hex_sig);

typedef struct {
    char rpc_url[256];
    char wallet[42];
} Config;

int main() {
    Config cfg = {
        "https://api.avax-test.network/ext/bc/C/rpc",
        "0x8db97C7cEcE249c2b98bDC0226Cc4C2A57BF52FC"
    };

#ifdef __OpenBSD__
    unveil("/usr/bin/curl", "x");
    unveil("/etc/resolv.conf", "r");
    unveil("/etc/ssl/cert.pem", "r");
    unveil("/etc/ssl/certs", "r");  
    unveil("/bin/sh", "x");
    unveil(NULL, NULL);
    pledge("stdio rpath proc exec dns inet", NULL);
#endif

    printf("[ INICIO ] Monitoreando Agent UvlAuth...\n");

    while (1) {
        char response[1024] = {0};
        
        // 1. Generar firma de identidad para este ciclo
        char *hex_sig = generar_cadena("Aleph_Hackathon_2026_Cycle");

        if (hex_sig) {
            // 2. Ejecutar la consulta usando el motor de check_balance
            if (ejecutar_consulta_rpc(cfg.wallet, cfg.rpc_url, response, sizeof(response)) == 0) {
                // 3. Decidir visualmente
                agente_visual_decidir(response, hex_sig);
            } else {
                fprintf(stderr, "[ ERROR ] Fallo en comunicación RPC\n");
            }
            free(hex_sig);
        }

        printf("[ SLEEP ] Próxima verificación en 5 min.\n");
        sleep(300);
    }
    return 0;
}
