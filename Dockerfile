FROM eclipse/platformio

WORKDIR /usr/src/build
COPY . .
CMD ["pio run -e main"]
