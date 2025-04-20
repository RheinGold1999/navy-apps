#include <stdio.h>
#include <NDL.h>

int main() {
  NDL_Init(0);
  volatile uint32_t cnt = 0;
  while (1) {
    char buf[64];
    if ((cnt % 10000 == 0) && NDL_PollEvent(buf, sizeof(buf))) {
      printf("receive event: %s\n", buf);
      break;
    }
    cnt++;
  }
  printf("[%s,%d,%s] return 0\n", __FILE__, __LINE__, __FUNCTION__);
  return 0;
}
