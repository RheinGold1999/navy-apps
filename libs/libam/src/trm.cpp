#include <am.h>

Area heap;

void putch(char ch) {
  int fd = open("stdout", 0, 0);
  write(fd, &ch, 1);
  close(fd);
}

void halt(int code) {
  exit(code);
}
