/* * PROGRAMA DE PRUEBA: sched_test.c
 * Lanza 4 procesos hijos concurrentes con cargas matemáticas idénticas.
 * Objetivo: Verificar la distribución justa de CPU en Round Robin.
 */
#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_CHILDREN 4
#define LOAD_LIMIT 50000000

void do_heavy_work(int id, int pid) {
    volatile long long x = 0;
    
    // Ejecuta un bucle intensivo para consumir ciclos de CPU de forma continua.
    // Esto mantiene al proceso en estado 'running' el mayor tiempo posible para estresar el planificador.
    for (long long i = 0; i < LOAD_LIMIT; i++) {
        x += i * 2;
    }
    
    // Ejecuta la impresion en una unica llamada al sistema (syscall).
    // Esto garantiza la atomicidad de la escritura en la salida estandar, evitando condiciones 
    // de carrera (race conditions) donde los caracteres de distintos procesos se intercalen.
    printf(1, "[PROCESO TERMINADO] -> Hijo #%d (PID asignado: %d) finalizo su carga de trabajo.\n", id, pid);
    exit();
}

int main(void) {
    printf(1, "\n============================================================\n");
    printf(1, "   INICIANDO PRUEBA BASE DEL PLANIFICADOR (ROUND ROBIN)     \n");
    printf(1, "============================================================\n");
    printf(1, "Explicacion: Se crearan %d procesos hijos en paralelo.\n", NUM_CHILDREN);
    printf(1, "Cada uno realizara una carga pesada de operaciones matemáticas.\n");
    printf(1, "Bajo Round Robin, todos deberian terminar casi al mismo tiempo.\n");
    printf(1, "------------------------------------------------------------\n\n");

    // Bucle responsable de la creacion de multiples procesos mediante llamadas a fork().
    for (int i = 0; i < NUM_CHILDREN; i++) {
        
        // fork() duplica el proceso actual. Devuelve 0 al proceso hijo y el PID del hijo al padre.
        int pid = fork();
        
        if (pid < 0) {
            printf(1, "Error critico al ejecutar fork()\n");
            exit();
        } else if (pid == 0) {
            // Contexto de ejecucion del PROCESO HIJO.
            // Se asigna una prioridad distinta a cada hijo justo despues del fork.
            int prioridad = 15;
            if (i == 1) prioridad = 10;
            else if (i == 2) prioridad = 5;
            else if (i == 3) prioridad = 1;
            setpriority(getpid(), prioridad);
            printf(1, "[PRIORIDAD ASIGNADA] Hijo #%d (PID %d) prioridad %d\n", i, getpid(), prioridad);
            do_heavy_work(i, getpid());
        } else {
            // Contexto de ejecucion del PROCESO PADRE.
            // La variable 'pid' contiene el identificador real del hijo que se acaba de crear.
            printf(1, "[PROCESO CREADO] -> Lanzando Hijo #%d en segundo plano...\n", i);
        }
    }

    // Cada iteracion recoge el estado de terminacion (exit status) de un hijo, liberando sus recursos en memoria.
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait();
    }

    printf(1, "\n============================================================\n");
    printf(1, "   PRUEBA FINALIZADA: Todos los procesos hijos culminaron.  \n");
    printf(1, "============================================================\n\n");
    exit();
}