#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <Arduino.h>
#include <NimBLEDevice.h>
#include <map>
#include <vector>

class BLEManager {
public:
    // Initializes the BLE subsystem
    static void initialize();

    // Starts advertising BLE services
    static void startAdvertising();

    // Stops advertising BLE services
    static void stopAdvertising();

    // Checks if a BLE device is connected
    static bool isConnected();

    // Sends data over BLE
    static void sendData(const std::string& data);

    // Registers a callback to handle incoming BLE data
    static void onDataReceived(void (*callback)(const std::string& data));

    // Logs the current BLE status
    static void logStatus();

    // Starts receiving a fragmented list
    static void startReceivingList();

    // Handles a fragment of the data
    static void handleFragment(const std::string& fragment, uint8_t sequenceNumber, bool isFinalFragment);

    // Gets the fully reconstructed list after all fragments are received
    static std::string getReconstructedData();
};

#endif // BLE_MANAGER_H
