#include "ESPNowManager.h"
#include <esp_now.h>
#include <WiFi.h>
#include <vector>
#include <map>
#include <string>

// Static variables for internal state
static std::vector<uint8_t> peerMacAddresses; // List of peer MAC addresses
void (*ESPNowManager::espNowDataCallback)(const uint8_t* macAddr, const uint8_t* data, size_t data_len) = nullptr;

void ESPNowManager::initialize() {
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    Serial.println("ESP-NOW initialized successfully");
}

void ESPNowManager::onDataReceived(void (*callback)(const uint8_t* macAddr, const uint8_t* data, size_t data_len)) {
    espNowDataCallback = callback;

    // Inline callback function to handle incoming ESP-NOW data because of unknown ESP IDF compiler issue
    esp_now_register_recv_cb([](const uint8_t* macAddr, const uint8_t* data, int data_len) {
        Serial.printf("Data received from MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                      macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
        if (espNowDataCallback) {
            espNowDataCallback(macAddr, data, static_cast<size_t>(data_len));
        }
    });
}

bool ESPNowManager::addPeer(const uint8_t* peerMac, uint8_t channel) {
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerMac, 6);
    peerInfo.channel = channel;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) == ESP_OK) {
        Serial.printf("Peer added: %02X:%02X:%02X:%02X:%02X:%02X\n",
                      peerMac[0], peerMac[1], peerMac[2], peerMac[3], peerMac[4], peerMac[5]);
        peerMacAddresses.push_back(*peerMac);
        return true;
    } else {
        Serial.println("Failed to add peer");
        return false;
    }
}

bool ESPNowManager::removePeer(const uint8_t* peerMac) {
    if (esp_now_del_peer(peerMac) == ESP_OK) {
        Serial.printf("Peer removed: %02X:%02X:%02X:%02X:%02X:%02X\n",
                      peerMac[0], peerMac[1], peerMac[2], peerMac[3], peerMac[4], peerMac[5]);
        return true;
    } else {
        Serial.println("Failed to remove peer");
        return false;
    }
}

void ESPNowManager::sendData(const uint8_t* peerMac, const uint8_t* data, size_t len) {
    if (esp_now_send(peerMac, data, len) != ESP_OK) {
        Serial.println("Error sending data");
    } else {
        Serial.println("Data sent successfully");
    }
}

void ESPNowManager::logPeers() {
    Serial.println("Registered ESP-NOW peers:");
    for (const auto& mac : peerMacAddresses) {
        Serial.printf("Peer MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                      mac, mac + 1, mac + 2, mac + 3, mac + 4, mac + 5);
    }
}
