//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_PICTUREPAYLOAD_H
#define DIRECTED_STUDIES_PICTUREPAYLOAD_H

#include "../ESPacket.h"

class PictureHeaderPacket : public ESPacket {
public:
    enum class picture_coding_types {
        reserved_forbidden = 0x0,
        intra_coded = 0x1,
        predictive_coded = 0x2,
        bidirectionally_predictive_coded = 0x3
    };

    static PictureHeaderPacket::picture_coding_types toPictureCodingType(unsigned char x);

    struct initializerStruct {
        unsigned short temporal_reference; //10-bits
        PictureHeaderPacket::picture_coding_types picture_coding_type; //3-bits
        unsigned short vbv_delay; //16-bits
    };

    /**
     * Constructor
     */
    PictureHeaderPacket(initializerStruct init);

    void print() override;

    bool operator==(const PictureHeaderPacket &rhs) const;

    bool operator!=(const PictureHeaderPacket &rhs) const;

    ~PictureHeaderPacket() = default;

    unsigned short getTemporalReference() const;

    picture_coding_types getPictureCodingType() const;

    std::string getPictureCodingTypeString() const;

private:
    unsigned short temporal_reference; //10-bits
    PictureHeaderPacket::picture_coding_types picture_coding_type; //3-bits
    unsigned short vbv_delay; //16-bits
//    bool full_pel_forward_vector; //1-bit always '0' in H262
//    unsigned char forward_f_code ; //3-bits always '111' in H262
//    bool full_pel_backward_vector; //1-bit always '0' in H262
//    unsigned char backward_f_code ; //3-bits always '111' in H262
//    bool extra_bit_picture; //1-bit ignore in H262
//    unsigned char extra_information_picture; //8-bits ignore in H262
};


#endif //DIRECTED_STUDIES_PICTUREPAYLOAD_H
