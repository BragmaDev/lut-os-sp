#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int reset = 0, sysnum = 0;
  if (argc > 3) {
      printf(1, "usage: getrc [reset 0/1] [syscall number]\n");
      exit();
  }
  if (argc == 3) {
      sysnum = atoi(argv[2]);
  }
  if (argc >= 2) {
      if (atoi(argv[1]) != 0) {
          reset = 1;
      }
  }
  printf(1, "%d\n", getreadcount(reset, sysnum));
  exit();
}
