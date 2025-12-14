#pragma once

#include <string>
#include <cstdint>

/* given socketcan device name (e.g. can0) return usb vendor id, usb product id, and usb serial number */

bool getUsbInfoFromDeviceName(const std::string& devName, uint16_t& vendor_id, uint16_t& product_id, std::string& serial);

