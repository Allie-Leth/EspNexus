#ifndef BLE_PACKET_HANDLER_H
#define BLE_PACKET_HANDLER_H

#include <string>
#include <vector>
#include <cstdint>

class BLEPacketHandler {
public:
    // Processes an incoming BLE packet
    void ProcessIncomingBLEPacket(const std::string& packetData);

    // Constructs a BLE packet from payload data
    std::string CreateBLEPacket(const std::string& payload);

    // Validates the integrity of a BLE packet
    bool ValidateBLEPacket(const std::string& packetData) const;

    // Fragments a large BLE packet for transmission
    std::vector<std::string> FragmentBLEPacket(const std::string& packetData, uint8_t maxFragmentSize);

    // Reconstructs a BLE packet from fragments
    std::string ReconstructBLEPacket(const std::vector<std::string>& fragments) const;

private:
    // Utility function to calculate checksum for a BLE packet
    uint16_t CalculateBLEChecksum(const std::string& packetData) const;
};

#endif // BLE_PACKET_HANDLER_H
