# 🛡️ UvlAuth: Agente Autónomo ERC-8004

**Agente autónomo nativo en C, de baja huella y alta seguridad para kernels protegidos.**

---

## 🚀 Descripción General

**UvlAuth** es un agente autónomo (ERC-8004) de alta seguridad diseñado para ejecutarse en hardware restringido y entornos de misión crítica. Desarrollado en **C** para la arquitectura **OpenBSD i386**, demuestra que el futuro de la identidad soberana y los pagos autónomos (**x402**) no requiere recursos masivos en la nube, sino código eficiente y seguridad a nivel de kernel.

Mientras que la mayoría de los agentes modernos dependen de stacks pesados y vulnerables de JavaScript/Node.js, **UvlAuth** opera con una huella de memoria **inferior a 15MB**, permitiendo su despliegue en dispositivos IoT, controladores industriales y hardware "legacy" que otros consideran obsoleto.

## 🛡️ Seguridad: La Filosofía OpenBSD

En **UvlAuth**, la clave privada es tratada como un recurso crítico. El sistema protege esta integridad utilizando las primitivas de seguridad más avanzadas del kernel de OpenBSD:

* **`unveil(2)`**: El agente aplica el principio de menor privilegio sobre el sistema de archivos. Tras cargar su configuración, el resto del disco se vuelve invisible para el proceso, mitigando ataques de lectura de archivos sensibles.
* **`pledge(2)`**: Tras la inicialización, el agente restringe sus propias llamadas al sistema a un subconjunto mínimo (`stdio`, `rpath`, `exec`). Cualquier intento de inyección de código que busque abrir un socket no autorizado o escalar privilegios provoca que el kernel termine el proceso instantáneamente.
* **Binarios Estáticos**: Compilación vinculada a **LibreSSL**, eliminando riesgos asociados a bibliotecas compartidas dinámicamente.

## 🏗️ Stack Tecnológico

- **Lenguaje:** C (C99) / C++
- **S.O.:** OpenBSD 7.0 (Arquitectura i386)
- **Hardware:** Intel Celeron M 410 @ 1.464GHz | 2GB RAM
- **Criptografía:** LibreSSL (Curva elíptica secp256k1)
- **Red:** Interfaz JSON-RPC sobre HTTP (integración nativa con `curl`)
- **Estándares:** ERC-8004 (Autonomous Agents) y x402 (HTTP Payments)

## 🔧 Característica

- [x] **Criptografía de Bajo Nivel**: Generación y firma ECDSA optimizada para procesadores de 32 bits.
- [x] **Sandboxing Proactivo**: Implementación dual de `pledge` y `unveil` para seguridad post-explotación.
- [x] **Toma de Decisiones Autónoma**: El agente interactúa con **Avalanche Fuji Testnet**, consulta estados on-chain y autoriza firmas basadas en lógica interna.
- [x] **Eficiencia Energética**: Diseñado para ejecutarse en procesadores de un solo núcleo sin sacrificar rendimiento.

## 📁 Estructura del Proyecto

```text
.
├── src/
│   ├── main.c          # Lógica de decisión y flujo del agente
│   └── signer.c        # Motor criptográfico y manejo de LibreSSL
│   └── check_balance.c        # Interactuar con el ecosistema Avalanche
├── lib/
│   ├── signer.h        # Definiciones y estructuras de hardware
├── config.txt          # Parámetros de misión del agente
└── Makefile            # Sistema de construcción nativo BSD
