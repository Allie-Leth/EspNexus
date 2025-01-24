#ifndef ESP_NOW_MANAGER_H
#define ESP_NOW_MANAGER_H

#include <Arduino.h>
#include <vector>

class ESPNowManager {
public:
    // Initializes the ESP-NOW subsystem
    static void initialize();

    // Adds a peer to the ESP-NOW network
    static bool addPeer(const uint8_t* peerMac, uint8_t channel = 0);

    // Removes a peer from the ESP-NOW network
    static bool removePeer(const uint8_t* peerMac);

    // Sends data to a specific peer
    static void sendData(const uint8_t* peerMac, const uint8_t* data, size_t len);

    // Registers a callback to handle incoming ESP-NOW data
    static void onDataReceived(void (*callback)(const uint8_t* macAddr, const uint8_t* data, size_t len));

    // Logs all registered peers
    static void logPeers();

private:
    // Static callback function pointer for handling received data
    static void (*espNowDataCallback)(const uint8_t* macAddr, const uint8_t* data, size_t len);

    // Inline callback function for handling received data
    static void registerReceiveCallback();
};

#endif // ESP_NOW_MANAGER_H
