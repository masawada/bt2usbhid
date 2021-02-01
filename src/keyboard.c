#include <unistd.h>
#include <linux/input.h>

#include "./keyboard.h"

#define STDIN_FD  0
#define STDOUT_FD 1

#define LEFTCTRL_CODE   1
#define LEFTSHIFT_CODE  2
#define LEFTALT_CODE    4
#define LEFTMETA_CODE   8
#define RIGHTCTRL_CODE  16
#define RIGHTSHIFT_CODE 32
#define RIGHTALT_CODE   64
#define RIGHTMETA_CODE  128

typedef struct input_event input_event;

typedef struct {
  unsigned char modifiers;
  unsigned char reserved;
  unsigned char keys[6];
} keyboard_report;

void _handle_modifier_key (input_event *event, keyboard_report *report, int key_code);
void _handle_key (input_event *event, keyboard_report *report);

void process_keyboard_events () {
  keyboard_report report = {0, 0, {0, 0, 0, 0, 0, 0}};

  ioctl(STDIN_FD, EVIOCGRAB, 1);

  while (1) {
    input_event event;
    read(STDIN_FD, &event, sizeof(event));

    if (event.type != EV_KEY || event.value > 1) {
      continue;
    }

    switch (event.code) {
      case KEY_LEFTCTRL:   _handle_modifier_key(&event, &report, LEFTCTRL_CODE);   break;
      case KEY_LEFTSHIFT:  _handle_modifier_key(&event, &report, LEFTSHIFT_CODE);  break;
      case KEY_LEFTALT:    _handle_modifier_key(&event, &report, LEFTALT_CODE);    break;
      case KEY_LEFTMETA:   _handle_modifier_key(&event, &report, LEFTMETA_CODE);   break;
      case KEY_RIGHTCTRL:  _handle_modifier_key(&event, &report, RIGHTCTRL_CODE);  break;
      case KEY_RIGHTSHIFT: _handle_modifier_key(&event, &report, RIGHTSHIFT_CODE); break;
      case KEY_RIGHTALT:   _handle_modifier_key(&event, &report, RIGHTALT_CODE);   break;
      case KEY_RIGHTMETA:  _handle_modifier_key(&event, &report, RIGHTMETA_CODE);  break;
      default:             _handle_key(&event, &report);                           break;
    }
  }

  ioctl(STDIN_FD, EVIOCGRAB, 0);
}

void _handle_modifier_key (input_event *event, keyboard_report *report, int key_code) {
}

void _handle_key (input_event *event, keyboard_report *report) {
}
