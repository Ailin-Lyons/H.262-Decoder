//
// Created by elnsa on 2020-01-18.
//

#ifndef PROJECT_CODE_PICTUREDECODER_H
#define PROJECT_CODE_PICTUREDECODER_H


class PictureDecoder {
private:
    bool closed_gop = true;
    bool broken_link = false;

public:
    PictureDecoder() = default;

    void setClosedGop(bool closedGop);

    void setBrokenLink(bool brokenLink);

};


#endif //PROJECT_CODE_PICTUREDECODER_H
