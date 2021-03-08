#ifndef __TEST__

#include "ota_hal.h"

#include <EasyOTA.h>
#include <sstream>
#include <string>

// Modify this when change the version
//////////////////////////////////////
#define FW_VERSION toString(VERSION).c_str()
//////////////////////////////////////

#define OTA_SERVER_URL "http://repo.oberjoch-ulbrich.de"
#define OTA_GET_VERSION_ENDPOINT "/version"
#define OTA_GET_FIRMWARE_ENDPOINT "/firmware"

/**
 * @brief this is a fix for the arm gcc toolchain not supporting tostring even if std=c11 is enabled
 */
template<class T>
std::string toString(const T &value) {
    std::ostringstream os;
    os << value;
    return os.str();
};

OTAConfig config(
        FW_VERSION,
        OTA_SERVER_URL,
        OTA_GET_VERSION_ENDPOINT,
        OTA_GET_FIRMWARE_ENDPOINT,
        true // Debug
);

EasyOTA ota(config);

void hal_ota_impl::init()
{
}

void hal_ota_impl::check_update()
{
    ota.runUpdateRoutine();
}

#endif
