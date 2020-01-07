//
// Created by elnsa on 2020-01-05.
//

#include "../TransportPacketStructure/TransportPacket.h"
#include "../TSPayloadSections/ProgramMapSection.h"

class PMSParser{
public:
    /**
     * Parses the next TransportPacket as a ProgramMapSection if possible and if necessary reads additional TransportPackets
     * @return a ProgramMapSection representing the ProgramMapSection that starts in tPacket
     */
    static ProgramMapSection* getPMSPacket(TransportPacket* tPacket) {
        return nullptr; // TODO
    }
};
