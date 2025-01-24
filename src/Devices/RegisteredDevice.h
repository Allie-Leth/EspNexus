#ifndef REGISTEREDDEVICE_H
#define REGISTEREDDEVICE_H

#include "Device.h"
#include <string>
#include <vector>
#include <cstdint>

struct RegisteredDevice : public Device {
    // Additional attributes specific to registered devices

    // Connection status
    std::string connectedTo;        // Identifier of the device it is connected to
    bool isOnline = false;          // True if the device is online

    // Health management attributes
    uint32_t lastHealthCheck = 0;   // Timestamp of the last health check (in milliseconds)
    bool isHealthy = true;          // True if the device passed the last health check
    uint8_t healthFailures = 0;     // Number of consecutive failed health checks
};

#endif // REGISTEREDDEVICE_H
