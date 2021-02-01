#include <stdio.h>
#include <stdlib.h>

void show_help (char *program_name);

int main (int argc, char *argv[]) {
  char *program_name = argv[0];

  show_help(program_name);

  return 0;
}

void show_help (char *program_name) {
  printf("Usage: %s [OPTION]... < /dev/input/eventN > /dev/hidgN\n", program_name);
  printf("bt2usbhid converts Bluetooth keyboard or mouse events to USB HID reports.");
  printf("\n");
  printf("\n");
  printf("OPTIONS\n");
  printf("  -k Keyboard mode\n");
  printf("  -m Mouse mode\n");
  exit(EXIT_SUCCESS);
}
