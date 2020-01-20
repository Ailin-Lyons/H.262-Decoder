//
// Created by elnsa on 2020-01-18.
//

#include <cstdio>
#include "MacroblockModes.h"

MacroblockModes::MacroblockModes(MacroblockModes::initializerStruct init) {
    macroblock_quant = init.macroblock_quant;
    macroblock_motion_forward = init.macroblock_motion_forward;
    macroblock_motion_backward = init.macroblock_motion_backward;
    macroblock_pattern = init.macroblock_pattern;
    macroblock_intra = init.macroblock_intra;
    spatial_temporal_weight_code_flag = init.spatial_temporal_weight_code_flag;
    spatal_temporal_weight_classes = init.spatal_temporal_weight_classes;
    frame_motion_type = init.frame_motion_type;
    field_motion_type = init.field_motion_type;
    dct_type = init.dct_type;
}

void MacroblockModes::print() {
    printf("MacroblockModes: q %s, f %s, b %s, p  %s, i  %s, flag  %s, class  %x, frame  %x, field  %x, dct  %s\n",
           macroblock_quant ? "true" : "false", macroblock_motion_forward ? "true" : "false",
           macroblock_motion_backward ? "true" : "false", macroblock_pattern ? "true" : "false",
           macroblock_intra ? "true" : "false", spatial_temporal_weight_code_flag ? "true" : "false",
           spatal_temporal_weight_classes, frame_motion_type, field_motion_type, dct_type ? "true" : "false");
}

bool MacroblockModes::operator==(const MacroblockModes &rhs) const {
    return macroblock_quant == rhs.macroblock_quant &&
           macroblock_motion_forward == rhs.macroblock_motion_forward &&
           macroblock_motion_backward == rhs.macroblock_motion_backward &&
           macroblock_pattern == rhs.macroblock_pattern &&
           macroblock_intra == rhs.macroblock_intra &&
           spatial_temporal_weight_code_flag == rhs.spatial_temporal_weight_code_flag &&
           spatal_temporal_weight_classes == rhs.spatal_temporal_weight_classes &&
           frame_motion_type == rhs.frame_motion_type &&
           field_motion_type == rhs.field_motion_type &&
           dct_type == rhs.dct_type;
}

bool MacroblockModes::operator!=(const MacroblockModes &rhs) const {
    return !(rhs == *this);
}
