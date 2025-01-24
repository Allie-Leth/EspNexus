#ifndef BASE_DEVICE_H
#define BASE_DEVICE_H

#include <string>
#include <vector>
#include <cstdint>
#include <map>

struct Device {
    // Basic device information
    std::string name;                // Friendly name of the device
    std::string bleMac;             // BLE MAC address
    std::string wifiMac;            // Wi-Fi MAC address for ESP-NOW
    std::string loraAddress;        // LoRa address

    // Protocol support flags
    bool supportsBLE = false;       // True if the device supports BLE
    bool supportsESPNow = false;    // True if the device supports ESP-NOW
    bool supportsLoRa = false;      // True if the device supports LoRa

    // Reachability map: Protocol -> List of reachable devices
    std::map<std::string, std::vector<std::string>> reachableDevices;

    // Health attributes
    uint32_t lastHealthCheck = 0;   // Timestamp of the last health check (in milliseconds)
    bool isHealthy = true;          // True if the device passed the last health check
    uint8_t healthFailures = 0;     // Number of consecutive failed health checks
};

#endif // BASE_DEVICE_H
