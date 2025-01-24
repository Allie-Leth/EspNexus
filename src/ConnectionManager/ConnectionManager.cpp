#include "ConnectionManager.h"

// Internal state for managing fragments
static std::string bleReconstructedData;
static std::string espNowReconstructedData;
static uint8_t bleExpectedSequenceNumber = 0;
static uint8_t espNowExpectedSequenceNumber = 0;
static bool bleFinalFragmentReceived = false;
static bool espNowFinalFragmentReceived = false;

void ConnectionManager::initialize() {
    // Initialize BLE subsystem
    BLEManager::initialize();
    BLEManager::onDataReceived(onBLEDataReceived);

    // Initialize ESP-NOW subsystem
    ESPNowManager::initialize();
    ESPNowManager::onDataReceived(onESPNOWDataReceived);

    Serial.println("ConnectionManager initialized successfully.");
}

void ConnectionManager::handleInitialMacList(const std::vector<std::string>& macList) {
    for (const auto& mac : macList) {
        uint8_t peerMac[6];
        sscanf(mac.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
               &peerMac[0], &peerMac[1], &peerMac[2], &peerMac[3], &peerMac[4], &peerMac[5]);
        ESPNowManager::addPeer(peerMac, 0);
    }
    Serial.println("Initial MAC list processed.");
}

void ConnectionManager::startReceivingList() {
    Serial.println("Starting to receive the MAC list.");
    // Implementation can include BLE commands to request the list
}

void ConnectionManager::validateAndDistributeMacList(const std::vector<std::string>& macList) {
    Serial.println("Validating and distributing MAC list...");
    for (const auto& mac : macList) {
        Serial.printf("Validating MAC: %s\n", mac.c_str());
    }
    // Further validation and distribution logic
}

void ConnectionManager::convertToBLEFormat(const std::vector<std::string>& dataList) {
    Serial.println("Converting data to BLE-friendly format...");
    for (const auto& data : dataList) {
        Serial.printf("Converted: %s\n", data.c_str());
    }
}

void ConnectionManager::logConnectionStatus() {
    BLEManager::logStatus();
    ESPNowManager::logPeers();
}

void ConnectionManager::forwardBLEDataToESPNow(const std::string& data) {
    Serial.println("Forwarding BLE data to ESP-NOW...");
    uint8_t broadcastMac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    ESPNowManager::sendData(broadcastMac, reinterpret_cast<const uint8_t*>(data.c_str()), data.size());
}

void ConnectionManager::forwardESPNowDataToBLE(const uint8_t* macAddr, const uint8_t* data, size_t len) {
    Serial.println("Forwarding ESP-NOW data to BLE...");
    std::string bleData(reinterpret_cast<const char*>(data), len);
    BLEManager::sendData(bleData);
}

void ConnectionManager::handleBLEFragment(const std::string& fragment, uint8_t sequenceNumber, bool isFinalFragment) {
    if (sequenceNumber != bleExpectedSequenceNumber) {
        Serial.println("BLE fragment sequence mismatch!");
        return;
    }
    bleReconstructedData += fragment;
    bleExpectedSequenceNumber++;
    bleFinalFragmentReceived = isFinalFragment;
    if (bleFinalFragmentReceived) {
        Serial.println("BLE data fully reconstructed:");
        Serial.println(bleReconstructedData.c_str());
    }
}

std::string ConnectionManager::getReconstructedBLEData() {
    return bleReconstructedData;
}

void ConnectionManager::handleESPNowFragment(const std::string& fragment, uint8_t sequenceNumber, bool isFinalFragment) {
    if (sequenceNumber != espNowExpectedSequenceNumber) {
        Serial.println("ESP-NOW fragment sequence mismatch!");
        return;
    }
    espNowReconstructedData += fragment;
    espNowExpectedSequenceNumber++;
    espNowFinalFragmentReceived = isFinalFragment;
    if (espNowFinalFragmentReceived) {
        Serial.println("ESP-NOW data fully reconstructed:");
        Serial.println(espNowReconstructedData.c_str());
    }
}

std::string ConnectionManager::getESPNowReconstructedData() {
    return espNowReconstructedData;
}

void ConnectionManager::onBLEDataReceived(const std::string& data) {
    Serial.printf("BLE data received: %s\n", data.c_str());
    forwardBLEDataToESPNow(data);
}
// Due an unknown error with ESP IDF, this function handles esp now data received
void ConnectionManager::onESPNOWDataReceived(const uint8_t* macAddr, const uint8_t* data, size_t len) {
    Serial.printf("ESP-NOW data received from MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
    forwardESPNowDataToBLE(macAddr, data, len);
}
