#ifndef PROTOCOL_INFORMATION_H
#define PROTOCOL_INFORMATION_H

#include <string>

// Enum for different protocol types
enum class ProtocolType {
    BLE,
    ESPNow,
    LoRa
};

// Struct to represent protocol capabilities
struct ProtocolInfo {
    bool supportsBLE = false;      // True if the device supports BLE
    bool supportsESPNow = false;  // True if the device supports ESP-NOW
    bool supportsLoRa = false;    // True if the device supports LoRa
};

#endif // PROTOCOL_INFORMATION_H
