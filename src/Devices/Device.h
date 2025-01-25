#ifndef DEVICE_H
#define DEVICE_H

#include "DeviceProtocols.h"
#include <string>
#include <vector>
#include <cstdint>
#include <map>

/**
 * @brief Computes a 24-bit hash from a MAC address string.
 *
 * This function uses the FNV-1a hashing algorithm to generate a 24-bit hash.
 * It takes a MAC address string as input and produces a unique 24-bit identifier
 * that is used to identify devices in the network.
 *
 * @param macAddress The MAC address string to be hashed.
 * @return uint32_t A 24-bit hash value derived from the MAC address.
 */
uint32_t hashMacAddress24(const std::string& macAddress);

struct Device {
    // Basic device information
    std::string name;                                           // 24-bit hash of the wifimac.
    std::string bleMac;                                         // BLE MAC address
    std::string wifiMac;                                        // Wi-Fi MAC address for ESP-NOW
    std::string loraAddress;                                    // LoRa address 
    
    // Protocol support flags
    std::vector<ProtocolInfo> supportedProtocols;               // List of bools indicating supported protocols

    // Connected Devices: Procotol -> List of directly connected devices
    std::map<std::string, std::vector<std::string>> directlyConnectedDevices;

    // Health attributes
    uint32_t lastHealthCheck = 0;                               // Timestamp of the last health check (in milliseconds)
    bool isHealthy = true;                                      // True if the device passed the last health check
    std::array<bool, 10> deviceHealthHistory = {false};         // History of connection health checks
};

#endif // DEVICE_H
