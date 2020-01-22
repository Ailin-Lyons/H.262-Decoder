//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_MACROBLOCKMODES_H
#define PROJECT_CODE_MACROBLOCKMODES_H


class MacroblockModes {
private:
    bool macroblock_quant;
    bool macroblock_motion_forward;
    bool macroblock_motion_backward;
    bool macroblock_pattern;
    bool macroblock_intra;
    bool spatial_temporal_weight_code_flag;
    unsigned char spatal_temporal_weight_classes; //not needed as we are not handling spacial scalability
    unsigned char frame_motion_type;
    unsigned char field_motion_type;
    bool dct_type;
public:
    struct initializerStruct {
        bool macroblock_quant;
        bool macroblock_motion_forward;
        bool macroblock_motion_backward;
        bool macroblock_pattern;
        bool macroblock_intra;
        bool spatial_temporal_weight_code_flag;
        unsigned char spatial_temporal_weight_classes; //not needed as we are not handling spacial scalability
        unsigned char frame_motion_type;
        unsigned char field_motion_type;
        bool dct_type;
    };

    MacroblockModes(initializerStruct init);

    ~MacroblockModes() = default;

    void print();

    bool operator==(const MacroblockModes &rhs) const;

    bool operator!=(const MacroblockModes &rhs) const;

    bool isMacroblockQuant() const;

    bool isMacroblockMotionForward() const;

    bool isMacroblockMotionBackward() const;

    bool isMacroblockPattern() const;

    bool isMacroblockIntra() const;
};


#endif //PROJECT_CODE_MACROBLOCKMODES_H
