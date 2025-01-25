#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <Arduino.h>
#include <vector>
#include <string>

#include "BLE/BLEManager.h"
#include "ESPNow/ESPNowManager.h"


class ConnectionManager {
public:
    // Initializes both the BLE and ESP-NOW subsystems
    static void initialize();

    // Handles receiving the initial WiFi Mac list from the BLE connected app
    static void handleInitialMacList(const std::vector<std::string>& macList);

    // BLE and ESP-NOW Cross-Communication
    static void startReceivingList();
    static void validateAndDistributeMacList(const std::vector<std::string>& macList);

    // Utility function for converting MAC lists to BLE-friendly formats
    static void convertToBLEFormat(const std::vector<std::string>& dataList);

    // Utility function for logging status
    static void logConnectionStatus();

private:
    // Helper methods for managing BLE and ESP-NOW interactions
    static void forwardBLEDataToESPNow(const std::string& data);
    static void forwardESPNowDataToBLE(const uint8_t* macAddr, const uint8_t* data, size_t len);

    // Internal state for managing fragments (BLE and ESP-NOW)
    static void handleBLEFragment(const std::string& fragment, uint8_t sequenceNumber, bool isFinalFragment);
    static std::string getReconstructedBLEData();

    static void handleESPNowFragment(const std::string& fragment, uint8_t sequenceNumber, bool isFinalFragment);
    static std::string getESPNowReconstructedData();

    // Callbacks
    static void onBLEDataReceived(const std::string& data);
    static void onESPNOWDataReceived(const uint8_t* macAddr, const uint8_t* data, size_t len);
};

#endif // CONNECTION_MANAGER_H
