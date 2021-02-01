#include <unistd.h>
#include <linux/input.h>

#include "./mouse.h"

#define STDIN_FD  0
#define STDOUT_FD 1

#define LEFT_CODE   1
#define RIGHT_CODE  2
#define MIDDLE_CODE 4
#define SIDE_CODE   8

typedef struct input_event input_event;

typedef struct {
  char buttons;
  char x;
  char y;
  char wheel;
} mouse_report;

int _clamp(int v, int min, int max);
void _send_mouse_report (mouse_report *report);
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

int _clamp (int v, int min, int max) {
  return v > max ? max : v < min ? min : v;
}

void _send_mouse_report (mouse_report *report) {
  write(STDOUT_FD, report, sizeof(*report));

  report->x     = 0;
  report->y     = 0;
  report->wheel = 0;
}

void _handle_button_event (input_event *event, mouse_report *report) {
  switch (event->code) {
    case BTN_LEFT:
      event->value ? (report->buttons |= LEFT_CODE) : (report->buttons &= ~LEFT_CODE);
      break;
    case BTN_RIGHT:
      event->value ? (report->buttons |= RIGHT_CODE) : (report->buttons &= ~RIGHT_CODE);
      break;
    case BTN_MIDDLE:
      event->value ? (report->buttons |= MIDDLE_CODE) : (report->buttons &= ~MIDDLE_CODE);
      break;
    case BTN_SIDE:
      event->value ? (report->buttons |= SIDE_CODE) : (report->buttons &= ~SIDE_CODE);
      break;
  }

  _send_mouse_report(report);
}

void _handle_relative_axes_event (input_event *event, mouse_report *report) {
  switch (event->code) {
    case REL_X:
      report->x = _clamp(event->value, -127, 127);
      break;
    case REL_Y:
      report->y = _clamp(event->value, -127, 127);
      break;
    case REL_WHEEL:
      report->wheel = _clamp(event->value, -127, 127);
      break;
  }

  _send_mouse_report(report);
}
