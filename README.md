# xv6 - Proyecto de Sistemas Operativos

## Información general

Este repositorio contiene una adaptación del sistema operativo académico xv6, desarrollada como proyecto de curso para explorar y modificar dos componentes fundamentales de un sistema operativo:

1. El algoritmo de planificación de la CPU (scheduler)
2. La gestión y asignación de memoria del sistema

El objetivo principal es comprender cómo un sistema operativo administra recursos de hardware y cómo distintos algoritmos afectan el comportamiento de los procesos y la eficiencia del sistema.

## Autores

- Jhon Esteban Acosta
- Jonathan David Borrero Viveros

Códigos estudiantiles:
- 2518388
- 2520360

## Resumen del proyecto

El proyecto busca brindar una visión práctica del funcionamiento interno de un sistema operativo mediante la modificación y evaluación de algoritmos de planificación y memoria en xv6. Para ello, se revisan los archivos fuente del kernel, se identifican estructuras y funciones clave, y se proponen mejoras que luego son implementadas y probadas.

## Objetivos

- Comprender el funcionamiento del planificador de procesos en xv6.
- Analizar la estrategia de asignación de memoria del kernel y de los procesos de usuario.
- Implementar cambios concretos y documentarlos en el código.
- Comparar el comportamiento del sistema antes y después de las modificaciones.
- Preparar una demostración clara para presentación en clase o en video.

## Desafíos abordados

- Configurar y ejecutar xv6 en un entorno de virtualización o emulación.
- Revisar la implementación actual del scheduler y del gestor de memoria.
- Diseñar modificaciones orientadas a mejorar la distribución de CPU y la visibilidad del uso de memoria.
- Implementar pruebas que permitan evidenciar el cambio en el comportamiento del sistema.

## Parte 1: Planificación de CPU

### Qué se modificó

Se incorporó soporte para trabajar con prioridades de proceso y se agregó una prueba que permite observar cómo los procesos compiten por la CPU bajo una carga intensa.

### Archivos principales modificados

- [proc.c](proc.c): se añadió la inicialización de una prioridad base para cada proceso y se ajustó la lógica del planificador para considerar prioridades.
- [proc.h](proc.h): se incluyó el campo de prioridad en la estructura del proceso.
- [syscall.c](syscall.c), [syscall.h](syscall.h): se registró el nuevo syscall de asignación de prioridad.
- [sysproc.c](sysproc.c): se implementó la función que permite cambiar la prioridad de un proceso.
- [user.h](user.h), [usys.S](usys.S): se añadieron las interfaces de usuario para el syscall.
- [sched_test.c](sched_test.c): se creó una prueba que lanza varios procesos hijos con trabajo pesado y prioridades distintas.

### Lógica de la prueba de CPU

La prueba crea varios procesos hijos que ejecutan un bucle intensivo de operaciones matemáticas. Cada proceso recibe una prioridad distinta, lo que permite observar cómo el scheduler distribuye la CPU entre ellos. La idea es comprobar que los procesos con mayor prioridad reciben más oportunidad de ejecución y que el sistema conserva un comportamiento más ordenado bajo carga.

## Parte 2: Gestión de memoria

### Qué se modificó

Se incorporó una forma de consultar la memoria física libre disponible en el kernel y se añadió una prueba que valida el uso, la escritura y la liberación de bloques de memoria.

### Archivos principales modificados

- [kalloc.c](kalloc.c): se agregó un contador de páginas libres y una función para consultar la memoria libre disponible.
- [defs.h](defs.h): se declaró la interfaz para consultar la memoria libre.
- [syscall.c](syscall.c), [syscall.h](syscall.h): se registró el syscall para consultar memoria libre.
- [sysproc.c](sysproc.c): se implementó la función que expone la información de memoria libre al espacio de usuario.
- [user.h](user.h), [usys.S](usys.S): se añadió la interfaz del syscall.
- [memtest.c](memtest.c): se creó una prueba para reservar memoria, escribir datos, verificar el contenido y liberar bloques de forma controlada.

### Lógica de la prueba de memoria

La prueba reserva dos bloques de memoria, llena cada bloque con un patrón de datos, verifica que la información se escriba y lea correctamente y luego libera los bloques. El objetivo es comprobar que el sistema administra correctamente los espacios de memoria asignados y que la memoria libre se reporta de forma consistente.

## Estructura del repositorio

Archivos relevantes del proyecto:

- [Makefile](Makefile): compila el kernel, los programas de usuario y genera la imagen de xv6.
- [proc.c](proc.c) y [kalloc.c](kalloc.c): implementaciones centrales del scheduler y del allocador de memoria.
- [sched_test.c](sched_test.c): prueba de planificación de CPU.
- [memtest.c](memtest.c): prueba de gestión de memoria.
- [README.md](README.md): documentación del proyecto.

## Requisitos de compilación

Para compilar y ejecutar este proyecto se recomienda tener instalado:

- Un compilador de C compatible con xv6
- QEMU para ejecutar la máquina virtual
- Herramientas básicas de compilación como make y gcc

En Ubuntu o Debian, se puede instalar con:

```bash
sudo apt update
sudo apt install -y build-essential gcc-multilib qemu-system-x86
```

## Compilación

Desde la raíz del repositorio, ejecute:

```bash
git clone https://github.com/Kerinc1/xv6-proyecto-Sistemas-Operativos.git
cd xv6-public
make clean
make
```

Este proceso genera el kernel de xv6 y los programas de usuario incluidos en el proyecto.

## Ejecución

Para arrancar xv6 en QEMU:

```bash
make qemu
```

Una vez dentro del shell de xv6, puede ejecutar las pruebas del proyecto:

```bash
sched_test
memtest
```

## Notas de uso

- Los cambios realizados están comentados en las secciones relevantes para facilitar su revisión.
- La ejecución de las pruebas permite comparar el comportamiento del sistema antes y después de las modificaciones.

## Conclusión

Este proyecto permite observar de forma práctica cómo un sistema operativo gestiona la CPU y la memoria. A través de la modificación del kernel de xv6 y la implementación de pruebas, se obtiene una comprensión más profunda de los mecanismos internos que hacen posible la multitarea y la administración de recursos.

