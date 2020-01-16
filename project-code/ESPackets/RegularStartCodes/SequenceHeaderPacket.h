//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_SEQUENCEHEADERPAYLOAD_H
#define DIRECTED_STUDIES_SEQUENCEHEADERPAYLOAD_H

#include "../ESPacket.h"

/**
 * H.262 6.2.2.1
 */
class SequenceHeaderPacket : public ESPacket {
private:
    unsigned short horizontal_size_value; //12-bits
    unsigned short vertical_size_value; //12-bits
    unsigned char aspect_ratio_information; //4-bits
    unsigned char frame_rate_code; //4-bits
    unsigned int bit_rate_value; //18-bits
    unsigned short vbv_buffer_size_value; //10-bits
    bool constrained_parameters_flag; //1-bit
    bool load_intra_quantiser_matrix; //1-bit
    unsigned char *intra_quantiser_matrix; //8*64bits
    bool load_non_intra_quantiser_matrix; //1-bit
    unsigned char *non_intra_quantiser_matrix; //8*64bits

public:
    struct initializerStruct {
        unsigned short horizontal_size_value; //12-bits
        unsigned short vertical_size_value; //12-bits
        unsigned char aspect_ratio_information; //4-bits
        unsigned char frame_rate_code; //4-bits
        unsigned int bit_rate_value; //18-bits
        unsigned short vbv_buffer_size_value; //10-bits
        bool constrained_parameters_flag; //1-bit
        bool load_intra_quantiser_matrix; //1-bit
        unsigned char *intra_quantiser_matrix; //8*64bits
        bool load_non_intra_quantiser_matrix; //1-bit
        unsigned char *non_intra_quantiser_matrix; //8*64bits
    };

    /**
     * Constructor
     */
    SequenceHeaderPacket(initializerStruct init);

    void print() override;

    bool operator==(const SequenceHeaderPacket &rhs) const;

    bool operator!=(const SequenceHeaderPacket &rhs) const;

    ~SequenceHeaderPacket();
};


#endif //DIRECTED_STUDIES_SEQUENCEHEADERPAYLOAD_H
