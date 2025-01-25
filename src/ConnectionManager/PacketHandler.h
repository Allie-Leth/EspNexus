#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "LoRa/LoRaPacketHandler.h"
#include "BLE/BLEPacketHandler.h"
#include "ESPNow/ESPNowPacketHandler.h"
#include <string>
#include <vector>
#include <memory>

class PacketHandler {
public:
    // Handles an incoming packet and routes it to the appropriate handler
    void PacketHandleIncomingBLE(const std::string& packetData);
    void PacketHandleIncomingESPNow(const std::string& packetData);
    void PacketHandleIncomingLoRa(const std::string& packetData);

    // Reconstructs a fragmented packet
    void PacketReconstructFragment(const std::string& fragment, uint8_t sequenceNumber, bool isFinalFragment);

    // Returns the reconstructed packet if available
    std::string PacketGetReconstructed() const;

    // Creates a packet for dispatching to the appropriate protocol
    // These use the associated libraries to build the packets
    std::string PacketCreateBLE(const std::string& payload);
    std::string PacketCreateESPNow(const std::string& payload);
    std::string PacketCreateLoRa(const std::string& payload);

private:
    // Packet handlers for specific protocols
    LoRaPacketHandler loraHandler;
    BLEPacketHandler bleHandler;
    ESPNowPacketHandler espNowHandler;

    // For handling fragmented packets
    std::vector<std::string> fragmentBuffer;
    uint8_t expectedFragmentCount = 0;
    uint8_t receivedFragmentCount = 0;
    bool isReconstructionComplete = false;

    // Utility function to determine routing based on packet contents
    std::string PacketDetermineRouting(const std::string& packetData) const;
};

#endif // PACKET_HANDLER_H