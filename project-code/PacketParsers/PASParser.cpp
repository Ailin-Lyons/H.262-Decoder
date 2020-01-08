//
// Created by elnsa on 2020-01-05.
//

#include "../TransportPacketStructure/TransportPacket.h"
#include "../TSPayloadSections/ProgramAssosciationSection.h"

class PASParser {
public:
    /**
     * Parses the next packet as a ProgramAssosciationSection if possible and if necessary reads additional TSPackets
     * @return a ProgramAssosciationSection representing the the ProgramAssosciationSection that starts in tPacket
     */
    static ProgramAssosciationSection *getPASPacket() {
        return nullptr; // TODO
    }
};
