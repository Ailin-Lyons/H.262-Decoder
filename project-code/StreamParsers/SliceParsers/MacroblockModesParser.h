//
// Created by elnsa on 2020-01-19.
//

#ifndef PROJECT_CODE_MACROBLOCKMODESPARSER_H
#define PROJECT_CODE_MACROBLOCKMODESPARSER_H

#include "../../StreamPackets/ESPackets/Slice/MacroblockModes.h"

class MacroblockModesParser {
private:
    struct vlc {
        bool macroblock_quant;
        bool macroblock_motion_forward;
        bool macroblock_motion_backward;
        bool macroblock_pattern;
        bool macroblock_intra;
        bool spatial_temporal_weight_code_flag;
        unsigned char spatial_temporal_weight_classes;
        unsigned char numbits;
        unsigned short key;
    };
    static vlc table_b2[];
    static size_t table_b2_size;
    static vlc table_b3[];
    static size_t table_b3_size;
    static vlc table_b4[];
    static size_t table_b4_size;

public:
    /**
     * Builds a MacroblockModes() from ESParser data, starting after the start_code/stream_id
     * and stores it at address mbm
     * H.262 6.2.5.1
     */
    static MacroblockModes *macroblock_modes();

private:
    static void decodeMacroblockType(MacroblockModes::initializerStruct *init);
};

#endif //PROJECT_CODE_MACROBLOCKMODESPARSER_H
