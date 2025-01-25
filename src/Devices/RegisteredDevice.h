#ifndef REGISTEREDDEVICE_H
#define REGISTEREDDEVICE_H

#include "Device.h"
#include "DeviceProtocols.h"
#include <string>
#include <vector>
#include <cstdint>

struct RegisteredDevice : public Device {
    // Connection information for devices registered on the entire network

    // Connection status
    bool isOnline = false;                                      // True if the device is online

    // Connection Health Management attributes
    uint32_t lastHealthCheck = 0;                               // Timestamp of the last health check
    bool ConnectionHealthy = true;                              // True if the device is healthy - this is a calculation based on healthHistory
    std::array<bool, 10> ConnectionHealthHistory = {false};     // History of health checks




    std::vector<ProtocolInfo*> directConnectionProtocols;      // Protocols that can be used to connect directly to the device


};

#endif // REGISTEREDDEVICE_H
