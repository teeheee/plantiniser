FROM eclipse/platformio

WORKDIR /usr/src/build
COPY . .
CMD ["apt-get install python"]
CMD ["build.sh"]
WORKDIR /usr/src/scripts
CMD ["python", "ota_server.py"]
