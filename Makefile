CC := gcc

build: src/main.c
	$(CC) src/main.c src/keyboard.c src/mouse.c -o bin/bt2usbhid

install:
	install bin/bt2usbhid      /usr/local/bin/bt2usbhid
	install bin/init_bt2usbhid /usr/local/bin/init_bt2usbhid
	install -m 644 config/init_bt2usbhid.service     /etc/systemd/system/init_bt2usbhid.service
	install -m 644 config/bt2usbhid_keyboard.service /etc/systemd/system/bt2usbhid_keyboard.service
	install -m 644 config/bt2usbhid_mouse.service    /etc/systemd/system/bt2usbhid_mouse.service
	systemctl enable init_bt2usbhid
	systemctl enable bt2usbhid_keyboard
	systemctl enable bt2usbhid_mouse

clean:
	$(RM) bin/bt2usbhid
