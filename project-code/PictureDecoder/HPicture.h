//
// Created by elnsa on 2020-01-28.
//

#ifndef PROJECT_CODE_HPICTURE_H
#define PROJECT_CODE_HPICTURE_H


#include "../PictureDecoder/Slice/Slice.h"

class HPicture {
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
    HPicture();

    ~HPicture() = default;//TODO

    void addSlice(Slice *slice);
};


#endif //PROJECT_CODE_HPICTURE_H
