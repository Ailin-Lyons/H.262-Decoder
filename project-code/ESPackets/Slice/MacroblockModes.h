//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_MACROBLOCKMODES_H
#define PROJECT_CODE_MACROBLOCKMODES_H


class MacroblockModes {
    unsigned short macroblock_type;
    unsigned char spatial_temporal_weight_code;
    unsigned char frame_field_motion_type;
    bool dct_type;
};


#endif //PROJECT_CODE_MACROBLOCKMODES_H
