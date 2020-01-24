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
    spatial_temporal_weight_classes = init.spatial_temporal_weight_classes;
    frame_motion_type = init.frame_motion_type;
    field_motion_type = init.field_motion_type;
    dct_type = init.dct_type;
}

void MacroblockModes::print() {
    printf("\tMacroblockModes: q = %s, f = %s, b = %s, p = %s, i = %s, flag = %s, class = %x, frame = %x, field = %x, dct = %s\n",
           macroblock_quant ? "T" : "F", macroblock_motion_forward ? "T" : "F",
           macroblock_motion_backward ? "T" : "F", macroblock_pattern ? "T" : "F",
           macroblock_intra ? "T" : "F", spatial_temporal_weight_code_flag ? "T" : "F",
           spatial_temporal_weight_classes, frame_motion_type, field_motion_type, dct_type ? "T" : "F");
}

bool MacroblockModes::operator==(const MacroblockModes &rhs) const {
    return macroblock_quant == rhs.macroblock_quant &&
           macroblock_motion_forward == rhs.macroblock_motion_forward &&
           macroblock_motion_backward == rhs.macroblock_motion_backward &&
           macroblock_pattern == rhs.macroblock_pattern &&
           macroblock_intra == rhs.macroblock_intra &&
           spatial_temporal_weight_code_flag == rhs.spatial_temporal_weight_code_flag &&
           spatial_temporal_weight_classes == rhs.spatial_temporal_weight_classes &&
           frame_motion_type == rhs.frame_motion_type &&
           field_motion_type == rhs.field_motion_type &&
           dct_type == rhs.dct_type;
}

bool MacroblockModes::operator!=(const MacroblockModes &rhs) const {
    return !(rhs == *this);
}

bool MacroblockModes::isMacroblockQuant() const {
    return macroblock_quant;
}

bool MacroblockModes::isMacroblockMotionForward() const {
    return macroblock_motion_forward;
}

bool MacroblockModes::isMacroblockMotionBackward() const {
    return macroblock_motion_backward;
}

bool MacroblockModes::isMacroblockPattern() const {
    return macroblock_pattern;
}

bool MacroblockModes::isMacroblockIntra() const {
    return macroblock_intra;
}

unsigned char MacroblockModes::getFrameMotionType() const {
    return frame_motion_type;
}

unsigned char MacroblockModes::getFieldMotionType() const {
    return field_motion_type;
}

unsigned char MacroblockModes::getSpatialTemporalWeightClasses() const {
    return spatial_temporal_weight_classes;
}
