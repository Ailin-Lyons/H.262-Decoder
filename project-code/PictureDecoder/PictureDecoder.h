//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_PICTUREDECODER_H
#define PROJECT_CODE_PICTUREDECODER_H


#include <RegularStartCodes/PictureHeaderPacket.h>

class PictureDecoder {
private:
    bool closed_gop;
    bool broken_link;
    unsigned short temporal_reference;
    PictureHeaderPacket::picture_coding_types picture_coding_type;

public:
    PictureDecoder() = default;

    void setClosedGop(bool closedGop);

    void setBrokenLink(bool brokenLink);

    void setTemporalReference(unsigned short temporalReference);

    void setPictureCodingType(PictureHeaderPacket::picture_coding_types pictureCodingType);

    void buildPicture();
};


#endif //PROJECT_CODE_PICTUREDECODER_H
