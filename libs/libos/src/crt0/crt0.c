#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[], char *envp[]);
extern char **environ;
void call_main(uintptr_t *args) {
  // char *empty[] =  {NULL };
  // environ = empty;
  // exit(main(0, empty, empty));

  // printf("args: %p\n", args);
  int argc = *((int *)args);
  char **argv = (char **)(args + 1);
  char **envp = (char **)(args + 1 + argc + 1);
  environ = envp;
  // printf("argc: %d\n", argc);
  // for (int i = 0; i < argc; ++i) {
  //   printf("argv[%d]: %s\n", i, argv[i]);
  // }
  // printf("argv[%d]: %s\n", argc, argv[argc]);
  exit(main(argc, argv, envp));
  assert(0);
}
