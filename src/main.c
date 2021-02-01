#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include "./keyboard.h"
#include "./mouse.h"

#define NO_MODE 0
#define KEYBOARD_MODE 1
#define MOUSE_MODE 2

int parse_options (int argc, char *argv[]);
void show_help (char *program_name);

int main (int argc, char *argv[]) {
  char *program_name = argv[0];

  switch (parse_options(argc, argv)) {
    case KEYBOARD_MODE:
      process_keyboard_events();
      break;
    case MOUSE_MODE:
      process_mouse_events();
      break;
    default:
      show_help(program_name);
      break;
  }

  return 0;
}

int parse_options (int argc, char *argv[]) {
  int opt, result = NO_MODE;

  while ((opt = getopt(argc, argv, "mk")) != -1) {
    switch (opt) {
      case 'k': result = KEYBOARD_MODE; break;
      case 'm': result = MOUSE_MODE; break;
    }
    if (result != NO_MODE) {
      break;
    };
  }

  return result;
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
