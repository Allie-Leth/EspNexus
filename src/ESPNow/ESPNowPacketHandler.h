#ifndef ESPNOW_PACKET_HANDLER_H
#define ESPNOW_PACKET_HANDLER_H

#include <string>
#include <vector>
#include <cstdint>

class ESPNowPacketHandler {
public:
    // Processes an incoming ESP-NOW packet
    void ProcessIncomingESPNowPacket(const std::string& packetData);

    // Constructs an ESP-NOW packet from payload data
    std::string CreateESPNowPacket(const std::string& payload);

    // Validates the integrity of an ESP-NOW packet
    bool ValidateESPNowPacket(const std::string& packetData) const;

    // Fragments a large ESP-NOW packet for transmission
    std::vector<std::string> FragmentESPNowPacket(const std::string& packetData, uint8_t maxFragmentSize);

    // Reconstructs an ESP-NOW packet from fragments
    std::string ReconstructESPNowPacket(const std::vector<std::string>& fragments) const;

private:
    // Utility function to calculate checksum for an ESP-NOW packet
    uint16_t CalculateESPNowChecksum(const std::string& packetData) const;
};

#endif // ESPNOW_PACKET_HANDLER_H
