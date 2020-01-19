//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_MACROBLOCKMODES_H
#define PROJECT_CODE_MACROBLOCKMODES_H


class MacroblockModes {
private: //TODO add VLC fields
    unsigned short macroblock_type;
    unsigned char spatial_temporal_weight_code;
    unsigned char frame_field_motion_type;
    bool dct_type;
public:
    struct initializerStruct {
        bool bla;
        //TODO
    };

    MacroblockModes(initializerStruct init);

    ~MacroblockModes() = default;

    void print();

    bool operator==(const MacroblockModes &rhs) const;

    bool operator!=(const MacroblockModes &rhs) const;
};


#endif //PROJECT_CODE_MACROBLOCKMODES_H
