#include <unistd.h>
#include <linux/input.h>

#include "./mouse.h"

#define STDIN_FD  0
#define STDOUT_FD 1

typedef struct input_event input_event;

typedef struct {
  char buttons;
  char x;
  char y;
  char wheel;
} mouse_report;

void _handle_button_event (input_event *event, mouse_report *report);
void _handle_relative_axes_event (input_event *event, mouse_report *report);

void process_mouse_events () {
  mouse_report report = {0, 0, 0, 0};

  ioctl(STDIN_FD, EVIOCGRAB, 1);

  while (1) {
    input_event event;
    read(STDIN_FD, &event, sizeof(event));

    switch (event.type) {
      case EV_KEY:
        _handle_button_event(&event, &report);
        break;
      case EV_REL:
        _handle_relative_axes_event(&event, &report);
        break;
    }
  }

  ioctl(STDIN_FD, EVIOCGRAB, 0);
}

void _handle_button_event (input_event *event, mouse_report *report) {
}

void _handle_relative_axes_event (input_event *event, mouse_report *report) {
}
