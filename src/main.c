#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/signer.h"

typedef struct
{
    char rpc_url[256];
    char wallet[42];
    float min_balance;
};

void cargar_config(Config *c)
{
    strcpy(c->rpc_url, "https://api.avax-test.network/ext/bc/C/rpc");
    strcpy(c->wallet, "0x8db97C7cEcE249c2b98bDC0226Cc4C2A57BF52FC");
    c->min_balance = 0.01;
}

void agente_decidir(const char *json_response)
{

    char *result_ptr = strstr(json_response, "\"result\":\"");

    if (result_ptr)
    {

        if (strstr(result_ptr, "\"result\":\"0x0\""))
        {
            printf("\n[ AGENTE ] Estado: Saldo 0x0. Modo ahorro de energía activado...\n");
        }

        else
        {
            printf("\n[ AGENTE ] Estado: Fondos detectados on-chain!\n");
            printf("[ AGENTE ] Acción: Generando firma de pago x402 para API de Cómputo...\n");

            char *pago_sig = generar_cadena("PAGO_DE_SERVICIO_AVALANCHE_2026");
            if (pago_sig)
            {
                printf("[ AGENTE ] ✅ Pago Autorizado. Hash de transacción local: 0x%s\n", pago_sig);
                free(pago_sig);
            }
        }
    }
    else
    {
        printf("\n[ AGENTE ] ❌ ERROR: Respuesta RPC inválida o malformada.\n");
    }
}

int main()
{
    Config mi_config;
    cargar_config(&mi_config);

    // --- SEGURIDAD OPENBSD ---
    unveil("/usr/bin/curl", "x");
    unveil("/etc/resolv.conf", "r");
    unveil("/etc/ssl/cert.pem", "r");
    unveil(NULL, NULL);

    if (pledge("stdio rpath proc exec dns inet", NULL) == -1)
    {
        perror("pledge");
        exit(1);
    }

    printf("[ AGENTE ] Iniciando monitoreo para: %s\n", mi_config.wallet);

    while (1)
    {
        char response[1024] = {0};
        char command[1024];

        snprintf(command, sizeof(command),
                 "curl -s -X POST -H \"Content-Type: application/json\" "
                 "-d '{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"%s\", \"latest\"],\"id\":1}' %s",
                 mi_config.wallet, mi_config.rpc_url);

        printf("\n[ AGENTE ] Consultando balance...");

        FILE *fp = popen(command, "r");
        if (fp)
        {
            fgets(response, sizeof(response), fp);
            pclose(fp);

            printf("\n---- UvlAuth Agent System (ERC-8004 Logic) ----\n");
            agente_decidir(response);
        }
        else
        {
            perror("popen");
        }

        printf("[ AGENTE ] Esperando 5 minutos para la próxima validación...\n");
        sleep(300);
    }

    return 0;
}

int main()
{
    Config mi_config;
    cargar_config(&mi_config);

    unveil("/usr/bin/curl", "x");
    unveil("/etc/resolv.conf", "r");
    unveil("/etc/ssl/cert.pem", "r");
    unveil(NULL, NULL);

    if (pledge("stdio rpath proc exec dns inet", NULL) == -1)
    {
        perror("pledge");
        exit(1);
    }

    printf("[ AGENTE ] Iniciando monitoreo para: %s\n", mi_config.wallet);

    while (1)
    {
        char response[1024] = {0};
        char command[1024];

        snprintf(command, sizeof(command),
                 "curl -s -X POST -H \"Content-Type: application/json\" "
                 "-d '{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"%s\", \"latest\"],\"id\":1}' %s",
                 mi_config.wallet, mi_config.rpc_url);

        printf("\n[ AGENTE ] Consultando balance...");

        FILE *fp = popen(command, "r");
        if (fp)
        {
            fgets(response, sizeof(response), fp);
            pclose(fp);

            printf("\n---- UvlAuth Agent System (ERC-8004 Logic) ----\n");
            agente_decidir(response);
        }
        else
        {
            perror("popen");
        }

        printf("[ AGENTE ] Esperando 5 minutos para la próxima validación...\n");
        sleep(300);
    }

    return 0;
}