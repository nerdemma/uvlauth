#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/sign.h"


//llamar a la libreria que genera la cadena encriptada
char* generar_direccion(char* msg)
{
char cadena* = generar_cadena(msg);
if(cadena){return cadena;}
free(cadena);
}

int main()
{
const char *url;
const char *address = generar_direccion("Aleph Hackathon 2026\0");
//payload json-rpc 2.0
char data[256];
sprintf(data, sizeof(data),"{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"%s\", \"latest\"],\"id\":1}",address);

printf("---- Consultando Avalanche Fuji RPC ----\n");


/*bloqueamos el sistema antes de ejecutar comando externo*/
if(pledge("stdio exec rpath", NULL) == -1)
{
perror("pledge");
return 1;
}

// usamos curl para el transporte
char command[512];
snprintf(command, sizeof(command), "curl -s -X POST -H \"Content-Type: application/json\" --data '%s' %s", data, url);
system(command);
printf(\n[ OK ] Consulta enviada\n);
return 0;
}
