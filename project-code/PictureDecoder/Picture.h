//
// Created by elnsa on 2020-01-28.
//

#ifndef PROJECT_CODE_PICTURE_H
#define PROJECT_CODE_PICTURE_H


#include "../PictureDecoder/Slice/Slice.h"

class Picture {
public:
    enum class decoding_state{
        variable_length_decoded,
        inverse_scanned,
        inverse_quantised,
        discrete_cosine_transformed
    };
private:
    decoding_state state;
    size_t numSlices;
    Slice** slices;

public:
    Picture();

    ~Picture() = default;//TODO

    void addSlice(Slice *slice);

    void performInverseScan();

    void performInverseQuantisation();

    void performDCT();
};


#endif //PROJECT_CODE_PICTURE_H
