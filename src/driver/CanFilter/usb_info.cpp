#include <cerrno>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "usb_info.hpp"

static bool fileExists(const std::string& path)
{
    struct stat st;
    return stat(path.c_str(), &st) == 0;
}

static bool readFile(const std::string& path, std::string& out)
{
    std::ifstream f(path.c_str());
    if (!f)
        return false;

    std::getline(f, out);
    return true;
}

static bool isRoot(const std::string& path)
{
    return path == "/";
}

/*
 * Walk upward until idVendor/idProduct are found
 */
static bool findUsbInfo(const std::string& startPath, uint16_t& vendor_id, uint16_t& product_id, std::string& serial)
{
    char resolved[PATH_MAX];
    if (!realpath(startPath.c_str(), resolved))
        return false;

    std::string path(resolved);

    while (!isRoot(path)) {
        std::string vendorPath  = path + "/idVendor";
        std::string productPath = path + "/idProduct";

        if (fileExists(vendorPath) && fileExists(productPath)) {
            std::string vendorStr, productStr;
            if (!readFile(vendorPath, vendorStr))
                return false;
            if (!readFile(productPath, productStr))
                return false;

            // Convert the string values to uint16_t
            vendor_id = static_cast<uint16_t>(std::stoi(vendorStr, nullptr, 16));  // Assuming hex values
            product_id = static_cast<uint16_t>(std::stoi(productStr, nullptr, 16));  // Assuming hex values

            // Read the serial number if available
            std::string serialPath = path + "/serial";
            if (fileExists(serialPath))
                readFile(serialPath, serial);

            return true;
        }

        // Move to parent directory
        std::size_t pos = path.find_last_of('/');
        if (pos == std::string::npos || pos == 0)
            break;

        path.erase(pos);
    }

    return false;
}

/*
 * Public API: accept a device name like "can0"
 */
bool getUsbInfoFromDeviceName(const std::string& devName, uint16_t& vendor_id, uint16_t& product_id, std::string& serial)
{
    std::string netPath = "/sys/class/net/" + devName;
    if (!fileExists(netPath))
        return false;

    std::string devicePath = netPath + "/device";
    if (!fileExists(devicePath))
        return false;

    return findUsbInfo(devicePath, vendor_id, product_id, serial);
}

