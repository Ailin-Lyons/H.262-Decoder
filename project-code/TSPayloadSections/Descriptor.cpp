//
// Created by bhave on 1/7/2020.
//

#include <cstdio>
#include "Descriptor.h"

//Descriptor::~Descriptor() = 0;//TODO

Descriptor::Descriptor(Descriptor::descriptor_type tag, unsigned char length, unsigned char mf_rate_flag,
                       unsigned char rate_code, unsigned char MPEG1_flag, unsigned char param_flag,
                       unsigned char picture_flag, unsigned char pl_ind, unsigned char cf, unsigned char ext_flag) {

    this->descriptor_tag = tag;
    this->descriptor_length = length;
    this->multiple_frame_rate_flag = mf_rate_flag;
    this->frame_rate_code = rate_code;
    this->MPEG_1_only_flag = MPEG1_flag;
    this->constrained_parameter_flag = param_flag;
    this->still_picture_flag = picture_flag;
    this->profile_and_level_indication = pl_ind;
    this->chroma_format = cf;
    this->frame_rate_extension_flag = ext_flag;
}

Descriptor::descriptor_type Descriptor::getTag() {
    return this->descriptor_tag;
}

unsigned char Descriptor::getLength() {
    return this->descriptor_length;
}

void Descriptor::print() {
    std::printf(
            "Descriptor: tag %x, length %hhx, mf_rate %hhx, rate_code %hhx, MP1_flag %hhx, pflag %hhx, pl_ind %hhx, cf %hhx, extf %hhx",
            descriptor_tag, descriptor_length, multiple_frame_rate_flag, frame_rate_code, MPEG_1_only_flag,
            still_picture_flag, profile_and_level_indication, frame_rate_extension_flag);
}
