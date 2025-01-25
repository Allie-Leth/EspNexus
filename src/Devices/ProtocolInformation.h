#ifndef PROTOCOL_INFORMATION_H
#define PROTOCOL_INFORMATION_H

#include <string>
#include <map>
#include <vector>

// Enum for different protocol types
enum class ProtocolType {
    BLE,
    ESPNow,
    LoRa
};

// Struct to hold information specific to each protocol
struct ProtocolInfo {
    bool isAvailable = false;        // Whether the protocol is supported
    std::string macAddress;         // Protocol-specific MAC address
    int signalStrength = 0;         // Optional, protocol-specific signal strength

    // Boolean flags for support and reachability
    bool supportsBLE = false;
    bool supportsESPNow = false;
    bool supportsLoRa = false;

    bool reachableBLE = false;
    bool reachableESPNow = false;
    bool reachableLoRa = false;

    // Pointers to other ProtocolInfo structs for routing
    std::vector<ProtocolInfo*> reachableProtocols;  // Protocols that can be reached
    std::vector<ProtocolInfo*> supportedProtocols;  // Protocols that are supported

    // Additional protocol-specific attributes can be added here
};

#endif // PROTOCOL_INFORMATION_H
