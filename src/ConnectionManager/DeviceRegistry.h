#ifndef DEVICE_REGISTRY_H
#define DEVICE_REGISTRY_H

#include "Devices/RegisteredDevice.h"
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <queue>
#include <algorithm>

class DeviceRegistry {
public:
    // Registers a new device or updates its connectivity info
    void registerDevice(const std::shared_ptr<RegisteredDevice>& device);

    // Removes a device from the registry
    void unregisterDevice(const std::string& mac);

    // Finds a device by its MAC address on ESP WiFi MAC address
    std::shared_ptr<RegisteredDevice> findDeviceByMac(const std::string& mac) const;

    // Updates connectivity map based on self-reported data
    void updateConnectivity(const std::string& mac, const std::vector<std::string>& reachableNodes);

    // Finds all devices supporting a specific protocol
    std::vector<std::shared_ptr<RegisteredDevice>> findDevicesByProtocol(const std::string& protocol) const;

    // Finds a route between two devices
    std::vector<std::string> findRoute(const std::string& sourceMac, const std::string& destinationMac) const;

    // Lists all registered devices
    std::vector<std::shared_ptr<RegisteredDevice>> listAllDevices() const;

    // Health management
    void performHealthChecks();
    void logUnhealthyDevices() const;

private:
    std::map<std::string, std::shared_ptr<RegisteredDevice>> deviceMap; // Device registry
    std::map<std::string, std::vector<std::string>> connectivityMap;   // Global connectivity map
};

#endif // DEVICE_REGISTRY_H
