#ifndef DEVICE_UTILITIES_H
#define DEVICE_UTILITIES_H

#include "Device.h"
#include "RegisteredDevice.h"
#include <vector>
#include <string>

class DeviceUtilies {
public:
    /**
     * @brief Updates the health status of a given device.
     *
     * This method updates the `isHealthy` status and tracks consecutive health
     * check failures. If the device is unhealthy, increments `healthFailures`.
     *
     * @param device Reference to the device to update.
     * @param healthy True if the device is healthy, false otherwise.
     */
    static void updateHealth(Device& device, bool healthy);

    /**
     * @brief Adds a reachable device to a protocol's list.
     *
     * Updates the `reachableDevices` map for the specified protocol, adding
     * the provided device to the list if it's not already present.
     *
     * @param device Reference to the device whose reachability map is being updated.
     * @param protocol The protocol used to reach the device (e.g., "BLE", "ESPNow", "LoRa").
     * @param reachableDevice The MAC address or identifier of the reachable device.
     */
    static void addConnectedDevice(Device& device, const std::string& protocol, const std::string& reachableDevice);

    /**
     * @brief Validates the reachability map of a device.
     *
     * Checks the `reachableDevices` map to ensure all entries are valid and updates
     * if any devices are no longer reachable.
     *
     * @param device Reference to the device to validate.
     * @return True if all entries in the reachability map are valid, false otherwise.
     */
    static bool validateConnection(const Device& device);

    /**
     * @brief Routes a message from one device to another.
     *
     * This method determines the routing path for a message, updating reachability
     * information as necessary. If a direct route is not available, it attempts
     * to find intermediate devices to relay the message.
     *
     * @param source Reference to the source device.
     * @param destinationMac The MAC address or identifier of the destination device.
     * @return True if the message can be routed, false otherwise.
     */
    static bool routeMessage(Device& source, const std::string& destinationMac);

    /**
     * @brief Logs the status of a device for debugging purposes.
     *
     * Prints the device's information, including its health status, reachable devices,
     * and protocol support.
     *
     * @param device Reference to the device to log.
     */
    static void logDeviceStatus(const Device& device);
};

#endif // DEVICE_UTILITIES_H
