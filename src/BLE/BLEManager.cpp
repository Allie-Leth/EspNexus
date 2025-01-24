#include "BLEManager.h"
#include <NimBLECharacteristic.h>
#include <map>
#include <vector>

// Static variables for internal state
static bool bleConnected = false;
static void (*dataReceivedCallback)(const std::string& data) = nullptr;
static std::map<uint8_t, std::string> fragmentBuffer; // Buffer to store fragments by sequence number
static std::string reconstructedData; // Stores the fully reconstructed data

class BLECallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override {
        bleConnected = true;
        Serial.printf("BLE device connected. Connection info:\n");
        Serial.printf("Peer MAC: %s\n", connInfo.getAddress().toString().c_str());
    }

    void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override {
        bleConnected = false;
        Serial.printf("BLE device disconnected. Connection info:\n");
        Serial.printf("Peer MAC: %s\n", connInfo.getAddress().toString().c_str());
        Serial.printf("Reason Code: %d\n", reason);
        fragmentBuffer.clear(); // Clear the fragment buffer on disconnect
        reconstructedData.clear();
    }
};

class CustomCharacteristicCallbacks : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
        std::string data = pCharacteristic->getValue();

        // Extract sequence number and fragment data from the received string
        if (data.length() >= 2) {
            uint8_t sequenceNumber = static_cast<uint8_t>(data[0]);
            bool isFinalFragment = static_cast<bool>(data[1]);
            std::string fragment = data.substr(2);

            // Store the fragment in the buffer
            fragmentBuffer[sequenceNumber] = fragment;
            Serial.printf("Received fragment %d (final: %d): %s\n", sequenceNumber, isFinalFragment, fragment.c_str());

            // If it's the final fragment, reconstruct the data
            if (isFinalFragment) {
                reconstructData();
                if (dataReceivedCallback) {
                    dataReceivedCallback(reconstructedData);
                }
                reconstructedData.clear(); // Clear the reconstructed data after callback
            }
        } else {
            Serial.println("Invalid fragment received.");
        }
    }

    void reconstructData() {
        reconstructedData.clear();

        // Combine fragments in order of sequence number
        for (const auto& fragment : fragmentBuffer) {
            reconstructedData += fragment.second;
        }
        fragmentBuffer.clear(); // Clear the buffer after reconstruction

        Serial.printf("Reconstructed data: %s\n", reconstructedData.c_str());
    }
};

void BLEManager::initialize() {
    Serial.println("Initializing BLE...");
    NimBLEDevice::init("ESP32_BTManager");
    NimBLEServer* pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new BLECallbacks());

    // Create a service
    NimBLEService* pService = pServer->createService("12345678-1234-1234-1234-123456789abc");

    // Create a characteristic
    NimBLECharacteristic* pCharacteristic = pService->createCharacteristic(
        "abcd1234-abcd-1234-abcd-123456789abc",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
    );

    pCharacteristic->setCallbacks(new CustomCharacteristicCallbacks());
    pService->start();

    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(pService->getUUID());
    pAdvertising->start();
    Serial.println("BLE advertising started.");
}

void BLEManager::startAdvertising() {
    Serial.println("Starting BLE advertising...");
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->start();
}

void BLEManager::stopAdvertising() {
    Serial.println("Stopping BLE advertising...");
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->stop();
}

bool BLEManager::isConnected() {
    return bleConnected;
}

void BLEManager::sendData(const std::string& data) {
    if (bleConnected) {
        NimBLEServer* pServer = NimBLEDevice::getServer();
        NimBLEService* pService = pServer->getServiceByUUID("12345678-1234-1234-1234-123456789abc");
        if (pService) {
            NimBLECharacteristic* pCharacteristic = pService->getCharacteristic("abcd1234-abcd-1234-abcd-123456789abc");
            if (pCharacteristic) {
                pCharacteristic->setValue(data);
                pCharacteristic->notify();
                Serial.print("Data sent: ");
                Serial.println(data.c_str());
            } else {
                Serial.println("Characteristic not found.");
            }
        } else {
            Serial.println("Service not found.");
        }
    } else {
        Serial.println("No BLE device connected. Data not sent.");
    }
}

void BLEManager::onDataReceived(void (*callback)(const std::string& data)) {
    dataReceivedCallback = callback;
}

void BLEManager::logStatus() {
    Serial.printf("BLE connected: %s\n", bleConnected ? "Yes" : "No");
}
