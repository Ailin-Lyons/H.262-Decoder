//
// Created by elnsa on 2020-01-05.
//

#include "../TransportPacketStructure/TransportPacket.h"
#include "../TSPayloadPackets/PASPacket.h"

class PASParser{
public:
    /**
     * Parses the next packet as a PASPacket if possible and if necessary reads additional TSPackets
     * @return a PASPacket representing the the PASPacket that starts in tPacket
     */
    static PASPacket* getPASPacket(TransportPacket* tPacket) {
        return nullptr; // TODO
    }
};
