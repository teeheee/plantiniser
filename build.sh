pio run -e main
cp .pio/build/main/firmware.bin scripts/opt/$(git rev-list --count HEAD).bin