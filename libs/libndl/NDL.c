#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;

uint32_t NDL_GetTicks() {
  uint64_t time[2];
  _gettimeofday(&time, NULL);
  return (uint32_t)(time[1] / 1000);
}

int NDL_PollEvent(char *buf, int len) {
  int fd = _open("/dev/events", 0, 0);
  return read(fd, buf, len);
}

void NDL_OpenCanvas(int *w, int *h) {
  // if (getenv("NWM_APP")) {
  //   int fbctl = 4;
  //   fbdev = 5;
  //   screen_w = *w; screen_h = *h;
  //   char buf[64];
  //   int len = sprintf(buf, "%d %d", screen_w, screen_h);
  //   // let NWM resize the window and create the frame buffer
  //   write(fbctl, buf, len);
  //   while (1) {
  //     // 3 = evtdev
  //     int nread = read(3, buf, sizeof(buf) - 1);
  //     if (nread <= 0) continue;
  //     buf[nread] = '\0';
  //     if (strcmp(buf, "mmap ok") == 0) break;
  //   }
  //   close(fbctl);
  // }
  int fd = _open("/proc/dispinfo", 0, 0);
  const size_t LEN = 64;
  char buf[LEN];
  read(fd, buf, LEN);
  // printf("read /proc/dispinfo: %s\n", buf);
  int colon_1 = -1;
  int colon_2 = -1;
  for (int i = 0; i < LEN; ++i) {
    if (buf[i] == ':') {
      if (colon_1 == -1) {
        colon_1 = i;
      } else {
        colon_2 = i;
        break;
      }
    }
  }
  // printf("colon_1: %d, colon_2: %d\n", colon_1, colon_2);
  *w = atoi(buf + colon_1 + 1);
  *h = atoi(buf + colon_2 + 1);
  close(fd);
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  int fd = open("/dev/fb", 0, 0);
  int screen_w = 0;
  int screen_h = 0;
  NDL_OpenCanvas(&screen_w, &screen_h);
  lseek(fd, (x + y * screen_w), 0);
  for (int i = 0; i < h; ++i) {
    write(fd, (pixels + i * w), w);
    lseek(fd, w, 1);
  }
  close(fd);
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  return 0;
}

void NDL_Quit() {
}
