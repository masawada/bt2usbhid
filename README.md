Bluetooth to USB HID Converter
==============================

This tool converts Bluetooth keyboard or mouse events to USB HID Reports. It can be run on some limited devices that support the USB Gadget API, such as Raspberry Pi Zero.


## Installation

First, connect a keyboard and a mouse to your device and trust these.

```
$ sudo bluetoothctl
[bluetooth]# scan on
...
[NEW] Device 00:00:00:00:00:00 YOUR_KEYBOARD_NAME
...
[bluetooth] # pair 00:00:00:00:00:00
[bluetooth] # connect 00:00:00:00:00:00
[bluetooth] # trust 00:00:00:00:00:00
```

Second, define udev rules.

```
$ git clone git@github.com:masawada/bt2usbhid.git
$ cd bt2usbhid
$ sudo cp config/99-bluetooth.rules.example /etc/udev/rules.d/99-bluetooth.rules
$ sudo $EDITOR /etc/udev/rules.d/99-bluetooth.rules
$ cat /etc/udev/rules.d/99-bluetooth.rules
KERNEL=="event*", ATTRS{name}=="YOUR_KEYBOARD_NAME", TAG+="systemd", SYMLINK+="input/keyboard", ENV{SYSTEMD_ALIAS}="/sys/class/input/keyboard"

KERNEL=="event*", ATTRS{name}=="YOUR_MOUSE_NAME", TAG+="systemd", SYMLINK+="input/mouse", ENV{SYSTEMD_ALIAS}="/sys/class/input/mouse"
```

You can use `udevadm` command to find the name of the devices:

```
$ udevadm info -a -p $(udevadm info -q path -n /dev/input/eventN)
...
  looking at parent device '//devices/virtual/misc/uhid/0000:0000:0000.0000/input/inputN':
    KERNELS=="input0"
    SUBSYSTEMS=="input"
    DRIVERS==""
    ATTRS{phys}=="00:00:00:00:00:00"
    ATTRS{uniq}=="00:00:00:00:00:00"
    ATTRS{properties}=="0"
    ATTRS{name}=="YOUR_KEYBOARD_NAME"
...
```

After that, build and install the tool.

```
$ make
$ sudo make install
```

Restart the device after this installation process to start the tool.

If you use Raspberry Pi, setup OTG mode before restart:

```
$ echo 'dtoverlay=dwc2' | sudo tee -a /boot/config.txt
```

## License

[The MIT License](./LICENSE).

It is heavily inspired by [moguno/event2usbhid](https://github.com/moguno/event2usbhid).

## Author

Masayoshi Wada <developer@andantesoftware.com>
