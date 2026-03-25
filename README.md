<div align="center">
<img src="/docs/logo.png" alt="UvlAuth Logo" />
<br/>


**Agente Autónomo ERC-8004 · OpenBSD i386 · C Nativo**

<br/>

[![Estándar](https://img.shields.io/badge/Estándar-ERC--8004-blueviolet?style=flat-square&logo=ethereum)](https://eips.ethereum.org/)
[![Pagos](https://img.shields.io/badge/Pagos-x402-orange?style=flat-square)](https://x402.org/)
[![Lenguaje](https://img.shields.io/badge/Lenguaje-C99%2FC%2B%2B-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C99)
[![Sistema](https://img.shields.io/badge/S.O.-OpenBSD%207.0%20i386-yellow?style=flat-square)](https://www.openbsd.org/)
[![Criptografía](https://img.shields.io/badge/Cripto-LibreSSL%20secp256k1-green?style=flat-square)](https://www.libressl.org/)
[![Huella](https://img.shields.io/badge/Memoria-%3C15MB-red?style=flat-square)](.)
[![Red](https://img.shields.io/badge/Red-Avalanche%20Fuji-ff0000?style=flat-square)](https://subnets-test.avax.network/)

<br/>

> *"El futuro de la identidad soberana no requiere recursos masivos en la nube,*
> *sino código eficiente y seguridad a nivel de kernel."*

</div>

---
<img src="/docs/demo.png" alt="UvlAuth Demo" />
## 📖 Descripción General

**UvlAuth** es un agente autónomo certificado bajo el estándar **ERC-8004** de alta seguridad, diseñado para ejecutarse en hardware restringido y entornos de misión crítica. Desarrollado íntegramente en **C** para la arquitectura **OpenBSD i386**, demuestra que el futuro de la identidad soberana y los pagos autónomos (**x402**) no requiere stacks pesados ni infraestructura cloud.

Mientras que la mayoría de los agentes modernos dependen de ecosistemas vulnerables de JavaScript/Node.js, **UvlAuth** opera con una huella de memoria **inferior a 15MB**, permitiendo su despliegue en:

| Entorno | Descripción |
|---|---|
| 🌐 Dispositivos IoT | Controladores con recursos mínimos |
| 🏭 Entornos industriales | Hardware de misión crítica |
| 🖥️ Hardware "legacy" | Máquinas que otros consideran obsoletas |
| 🔒 Kernels protegidos | Entornos con sandboxing estricto |

---

## 🛡️ Seguridad: La Filosofía OpenBSD

En **UvlAuth**, la clave privada es tratada como un recurso absolutamente crítico. El sistema protege esta integridad utilizando las primitivas de seguridad más avanzadas del kernel de OpenBSD, siguiendo el principio de **defensa en profundidad**.

### `unveil(2)` — Mínimo Privilegio sobre el Sistema de Archivos

> Tras cargar su configuración, el **resto del disco se vuelve invisible** para el proceso.

El agente aplica restricciones de visibilidad del sistema de archivos en tiempo de ejecución. Ningún vector de ataque puede leer archivos fuera del scope declarado, mitigando completamente ataques de lectura de archivos sensibles y escalada lateral.

```c
unveil("/etc/uvlauth/uvlauth.conf", "r");
unveil(NULL, NULL);  /* Congela el filesystem: nada más es visible */
```

### `pledge(2)` — Reducción de Superficie de Ataque del Kernel

> Cualquier intento de inyección que abra un socket no autorizado provoca **terminación instantánea** del proceso.

Tras la inicialización, el agente restringe sus propias llamadas al sistema a un subconjunto mínimo. No hay posibilidad de evasión post-explotación.

```c
pledge("stdio rpath exec", NULL);
/* El proceso ahora sólo puede: leer, escribir stdio y ejecutar. Nada más. */
```

### Binarios Estáticos con LibreSSL

> **Sin dependencias dinámicas en tiempo de ejecución.** El vector de ataque de bibliotecas compartidas comprometidas es eliminado por diseño.

La compilación vinculada estáticamente a **LibreSSL** garantiza que el binario es autónomo, reproducible y verificable. No existe superficie de ataque por `LD_PRELOAD` ni sustitución de `.so`.

---

## 🏗️ Stack Tecnológico

<div align="center">

| Componente | Tecnología | Detalle |
|---|---|---|
| **Lenguaje** | C99 / C++ | Compilación optimizada para 32-bit |
| **Sistema Operativo** | OpenBSD 7.0 | Arquitectura i386 |
| **Hardware** | Intel Celeron M 410 | 1.464GHz · 2GB RAM |
| **Criptografía** | LibreSSL | Curva elíptica `secp256k1` |
| **Red** | JSON-RPC / HTTP | Integración nativa con `libcurl` |
| **Blockchain** | Avalanche Fuji Testnet | Consultas on-chain y firma |
| **Estándar de Agente** | ERC-8004 | Autonomous Agents |
| **Protocolo de Pago** | x402 | HTTP Payments nativo |

</div>

---

## ✅ Características

- [x] **Criptografía de Bajo Nivel** — Generación y firma ECDSA optimizada para procesadores de 32 bits mediante `secp256k1` sobre LibreSSL.
- [x] **Sandboxing Proactivo** — Implementación dual de `pledge(2)` y `unveil(2)` para seguridad inmune a post-explotación, incluso con root comprometido.
- [x] **Toma de Decisiones Autónoma** — El agente interactúa con **Avalanche Fuji Testnet**, consulta estados on-chain y autoriza firmas basadas en lógica interna sin intervención humana.
- [x] **Eficiencia Energética** — Diseñado para ejecutarse en procesadores de un solo núcleo sin sacrificar rendimiento criptográfico ni throughput de red.
- [x] **Huella Mínima** — Consumo de memoria por debajo de **15MB**, apto para entornos con restricciones de RAM severas.
- [x] **Binario Autónomo** — Sin dependencias dinámicas en runtime. Un único binario estático, verificable y reproducible.

---

## 📁 Estructura del Proyecto

```text
Avalanche/
├── lib/
│   ├── signer.h 
├──LibreSSL/
│   └── check_balance.c
├ Makefile
├ README.md
├──docs/
│   └── index.html           
│   └── index.js
│   └── logo.png
├──src/
├── main.c
├── signer.c
│
uvlauth.conf


```

---

## ⚡ Inicio Rápido

### Prerrequisitos

```sh
# OpenBSD 7.0 — i386
pkg_add libressl curl
```

### Compilación

```sh
git clone https://github.com/nerdemma/uvlauth.git
cd uvlauth
make
```

### Configuración

Edita `config.txt` con los parámetros de tu agente antes de ejecutar:

```ini
# config.txt — Parámetros de misión del agente UvlAuth
rpc_endpoint=https://api.avax-test.network/ext/bc/C/rpc
wallet_address=0xTU_DIRECCION
private_key_path=/etc/uvlauth/key.pem
```

### Ejecución

```sh
./uvlauth
```

> ⚠️ Una vez iniciado, `pledge` y `unveil` se activan. El proceso opera en sandbox total.

---

## 🔐 Modelo de Seguridad

```
┌─────────────────────────────────────────────────┐
│                  KERNEL OpenBSD                  │
│                                                  │
│  ┌──────────────────────────────────────────┐   │
│  │            unveil(2) — FS Jail           │   │
│  │  ┌────────────────────────────────────┐  │   │
│  │  │       pledge(2) — Syscall Jail     │  │   │
│  │  │  ┌──────────────────────────────┐  │  │   │
│  │  │  │   UvlAuth Agent Process     │  │  │   │
│  │  │  │   • ECDSA Signer            │  │  │   │
│  │  │  │   • JSON-RPC Client         │  │  │   │
│  │  │  │   • Decision Engine         │  │  │   │
│  │  │  └──────────────────────────────┘  │  │   │
│  │  └────────────────────────────────────┘  │   │
│  └──────────────────────────────────────────┘   │
└─────────────────────────────────────────────────┘
```

Cualquier intento de escape de cualquier capa resulta en **SIGKILL inmediato** por el kernel.

---

## 📜 Licencia

Este proyecto se distribuye bajo los términos de la licencia **MIT**.  
Consulta el archivo [`LICENSE`](./LICENSE) para más detalles.

---

<div align="center">

**UvlAuth** · Construido con 🔒 sobre OpenBSD · Soberanía computacional real

*"Small binary. Full sovereignty."*

</div>
