
.PHONY: default
default:
	platformio run -v

.PHONY: all
all: default;

.PHONY: firmware
firmware:
	platformio run --target upload

.PHONY: spiffs
spiffs:
	platformio run --target uploadfs

.PHONY: monitor
monitor:
	platformio device monitor -b 115200

.PHONY: flash
flash: firmware monitor;

.PHONY: flashall
flashall: firmware spiffs monitor;

.PHONY: clean
clean:
	platformio run --target clean

.PHONY: distclean
distclean: clean
	rm -rf .platformio
