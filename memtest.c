#include "types.h"
#include "stat.h"
#include "user.h"

// Registro de bloques activos.
// Permite guardar la direccion, el tamano y si cada bloque sigue en uso
struct TrackedBlock {
  void *ptr;
  int size;
  int active;
};

// Llena un bloque con un patron repetido 
// Para comprobar que la memoria asignada puede escribirse y leerse
static void
fill_pattern(char *p, int size, char seed)
{
  int i;
  for(i = 0; i < size; i++)
    p[i] = (char)(seed + (i % 29));
}

// Se verifica  que el contenido del bloque coincida con el patron esperado
// Si no se coincide indica un problema de escritura
static int
check_pattern(char *p, int size, char seed)
{
  int i;
  for(i = 0; i < size; i++)
    if(p[i] != (char)(seed + (i % 29)))
      return 0;
  return 1;
}

int
main(int argc, char *argv[])
{
  int initial = freemem();
  int size = 4096;
  struct TrackedBlock blocks[2];

  // Inicio de la prueba 
  printf(1, "Prueba final: con rastreo de memoria\n");
  printf(1, "El programa mantiene una tabla de bloques activos.\n");
  printf(1, "Gracias a este rastreo, puede identificar que bloque esta en uso y liberarlo con precision.\n");
  printf(1, "Memoria libre inicial: %d bytes\n", initial);

  // Reserva el primer bloque y lo registra
  blocks[0].ptr = sbrk(size);
  if(blocks[0].ptr == (void*)-1){
    printf(1, "Error al asignar el primer bloque\n");
    exit();
  }
  blocks[0].size = size;
  blocks[0].active = 1;
  fill_pattern((char*)blocks[0].ptr, size, 17);
  if(!check_pattern((char*)blocks[0].ptr, size, 17)){
    printf(1, "Error en la verificacion del primer bloque\n");
    exit();
  }
  printf(1, "Bloque 1 reservado y verificado: %d bytes\n", size);

  // Reserva el segundo bloque y lo registra 
  blocks[1].ptr = sbrk(size);
  if(blocks[1].ptr == (void*)-1){
    printf(1, "Error al asignar el segundo bloque\n");
    sbrk(-size);
    exit();
  }
  blocks[1].size = size;
  blocks[1].active = 1;
  fill_pattern((char*)blocks[1].ptr, size, 41);
  if(!check_pattern((char*)blocks[1].ptr, size, 41)){
    printf(1, "Error en la verificacion del segundo bloque\n");
    sbrk(-size);
    sbrk(-size);
    exit();
  }
  printf(1, "Bloque 2 reservado y verificado: %d bytes\n", size);
  printf(1, "Memoria libre despues de asignar dos bloques: %d bytes\n", freemem());

  // Permite conocer exactamente que bloques siguen ocupados.
  printf(1, "Rastreo activo: se sabe que los bloques 1 y 2 siguen en uso.\n");

  // Libera el segundo bloque usando la informacion registrada
  if(sbrk(-blocks[1].size) == (void*)-1){
    printf(1, "Error al liberar el segundo bloque\n");
    exit();
  }
  blocks[1].active = 0;
  printf(1, "Bloque 2 liberado mediante el rastreo.\n");
  printf(1, "Memoria libre despues de liberar el bloque 2: %d bytes\n", freemem());

  // Libera el primer bloque usando la misma informacion de seguimiento
  if(sbrk(-blocks[0].size) == (void*)-1){
    printf(1, "Error al liberar el primer bloque\n");
    exit();
  }
  blocks[0].active = 0;
  printf(1, "Bloque 1 liberado mediante el rastreo.\n");
  printf(1, "Memoria libre final: %d bytes\n", freemem());

  // Cierre de la prueba con el resultado del rastreo
  printf(1, "Resultado: con rastreo, cada bloque puede localizarse y liberarse de forma precisa.\n");
  printf(1, "Prueba finalizada\n");
  exit();
}