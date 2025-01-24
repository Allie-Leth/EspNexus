#ifndef LORA_PACKET_HANDLER_H
#define LORA_PACKET_HANDLER_H

#include <string>
#include <vector>
#include <cstdint>

class LoRaPacketHandler {
public:
    // Processes an incoming LoRa packet
    void ProcessIncomingLoRaPacket(const std::string& packetData);

    // Constructs a LoRa packet from payload data
    std::string CreateLoRaPacket(const std::string& payload);

    // Validates the integrity of a LoRa packet
    bool ValidateLoRaPacket(const std::string& packetData) const;

    // Fragments a large LoRa packet for transmission
    std::vector<std::string> FragmentLoRaPacket(const std::string& packetData, uint8_t maxFragmentSize);

    // Reconstructs a LoRa packet from fragments
    std::string ReconstructLoRaPacket(const std::vector<std::string>& fragments) const;

private:
    // Utility function to calculate checksum for a LoRa packet
    uint16_t CalculateLoRaChecksum(const std::string& packetData) const;
};

#endif // LORA_PACKET_HANDLER_H
