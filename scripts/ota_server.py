import glob
import os
import pathlib
from bottle import run, static_file, response, get

OTA_GET_VERSION_ENDPOINT = "/version"
OTA_GET_FIRMWARE_ENDPOINT = "/firmware"
OTA_FIRMWARE_DIR = "opt"
OTA_SERVER_PORT = 8266
FIRMWARE_FILE_EXTENSION = '.bin'


class OTAServer:
    def __init__(self, port: int, debug_mode: bool = False):
        self.debug_mode = debug_mode
        self.port = port

    def start(self):
        run(host='0.0.0.0', port=self.port, debug=self.debug_mode)

    @staticmethod
    def get_latest_fw_version() -> str:
        """Returns the version of the latest (most recent) firmware file in OTA_FIRMWARE_DIR  dir"""
        list_of_files = glob.glob('{}/*{}'.format(OTA_FIRMWARE_DIR, FIRMWARE_FILE_EXTENSION))
        if not list_of_files:
            return None
        return max(list_of_files, key=os.path.getctime)\
            .replace(FIRMWARE_FILE_EXTENSION, "").replace(OTA_FIRMWARE_DIR+'/', "")

    # ------- ENDPOINTS ------- #

    @staticmethod
    @get(OTA_GET_VERSION_ENDPOINT)
    def get_version() -> str:
        raw_version = OTAServer.get_latest_fw_version()
        if raw_version is None or len(raw_version) == 0:
            response.status = 404
            return ""
        response.status = 200
        return str(raw_version)

    @staticmethod
    @get(OTA_GET_FIRMWARE_ENDPOINT)
    def get_firmware():
        version = OTAServer.get_latest_fw_version()
        if version is None or version == '':
            response.status = 404
            return ""
        return static_file(root=OTA_FIRMWARE_DIR, filename=version + FIRMWARE_FILE_EXTENSION)


if __name__ == '__main__':
    path = pathlib.Path(OTA_FIRMWARE_DIR)
    last_modified = path.stat().st_mtime
    run(host='0.0.0.0', port=OTA_SERVER_PORT, debug=True) 