//
// Created by elnsa on 2020-01-05.
//

#include "../TransportPacketStructure/TransportPacket.h"
#include "../TSPayloadPackets/PMSPacket.h"

class PMSParser{
public:
    /**
     * Parses the next TransportPacket as a PMSPacket if possible and if necessary reads additional TransportPackets
     * @return a PMSPacket representing the PMSPacket that starts in tPacket
     */
    static PMSPacket* getPMSPacket(TransportPacket* tPacket) {
        return nullptr; // TODO
    }
};
