#include <stdio.h>
#include <NDL.h>

int main() {
  NDL_Init(0);
  while (1) {
    uint32_t ms = NDL_GetTicks();
    if (ms % 500 == 0 ) {
      printf("current ms: %d\n", ms);
    }
  }
  return 0;
}
