#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, "Memoria libre inicial: %d bytes\n", freemem());
  
  printf(1, "Asignando memoria artificialmente (sbrk)...\n");
  void *m1 = sbrk(4096 * 5); // Pedimos 5 páginas
  
  if (m1 == (void*)-1) {
    printf(1, "Error asignando memoria\n");
    exit();
  }

  printf(1, "Memoria libre actual: %d bytes\n", freemem());
  
  printf(1, "Liberando memoria...\n");
  sbrk(-(4096 * 5)); // Devolvemos la memoria
  
  printf(1, "Memoria libre final: %d bytes\n", freemem());
  
  exit();
}