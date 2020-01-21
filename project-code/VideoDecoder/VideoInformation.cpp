//
// Created by elnsa on 2020-01-16.
//
#include "VideoInformation.h"
#include "../PacketParsers/PacketException.cpp"
#include "VideoException.cpp"

VideoInformation *VideoInformation::instance = nullptr;

unsigned short VideoInformation::getHorizontalSize() const {
    return horizontal_size;
}

unsigned short VideoInformation::getVerticalSize() const {
    return vertical_size;
}

void VideoInformation::setHorizontalSize(unsigned short horizontalSize) {
    horizontal_size = horizontalSize;
}

void VideoInformation::setVerticalSize(unsigned short verticalSize) {
    vertical_size = verticalSize;
}

void VideoInformation::setAspectRatio(unsigned char aspect_ratio_information) {
    switch (aspect_ratio_information) {
        case 0b0000:
            throw PacketException("VideoInformation::getAspectRatio: Forbidden Aspect Ratio\n");
        case 0b0001:
            aspectRatio = aspect_ratio::square_sample;
            break;
        case 0b0010:
            aspectRatio = aspect_ratio::ar_3_by_4;
            break;
        case 0b0011:
            aspectRatio = aspect_ratio::ar_9_by_16;
            break;
        case 0b0100:
            aspectRatio = aspect_ratio::ar_1_by_2_p_21;
            break;
        default:
            aspectRatio = aspect_ratio::reserved_a_r;
    }
}

void VideoInformation::setFrameRate(unsigned char frame_code, unsigned char frame_ext_n, unsigned char frame_ext_d) {
    double factor = (double) (frame_ext_n + 1) / (double) (frame_ext_d + 1);
    switch (frame_code) {
        case 0b0000:
            throw VideoException("VideoInformation::getAspectRatio: Forbidden Frame Rate\n");
        case 0b0001:
            frameRate = (double) 24000 / (double) 1001 * factor;
            break;
        case 0b0010:
            frameRate = (double) 24 * factor;
            break;
        case 0b0011:
            frameRate = (double) 25 * factor;
            break;
        case 0b0100:
            frameRate = (double) 30000 / (double) 1001 * factor;
            break;
        case 0b0101:
            frameRate = (double) 30 * factor;
            break;
        case 0b0110:
            frameRate = (double) 50 * factor;
            break;
        case 0b0111:
            frameRate = (double) 60000 / (double) 1001 * factor;
            break;
        case 0b1000:
            frameRate = ((double) 60) * factor;
            break;
        default:
            throw VideoException("VideoInformation::setFrameRate: unhandled frame rate type.\n");
    }
}

void VideoInformation::setBitRate(unsigned int bitRate) {
    bit_rate = bitRate;
}

void VideoInformation::setVBVBufSize(unsigned int vbvBufferSize) {
    vbv_buffer_size = vbvBufferSize;
}

void VideoInformation::setProfileLevel(unsigned char profile_and_level_indication) {
    bool escape = (bool) (profile_and_level_indication & 0b1000000) >> 7;
    if (escape) {
        throw VideoException("VideoInformation::setProfileLevel: Unhandled profile_level_indication\n");
    }
    setProfile((profile_and_level_indication & 0b0111000) >> 4);
    setLevel(profile_and_level_indication & 0b0001111);
}

void VideoInformation::setProfile(unsigned char profile_bits) {
    switch (profile_bits) {
        case 0b101:
            profile = video_profile::p_simple;
            break;
        case 0b100:
            profile = video_profile::p_main;
            break;
        case 0b011:
            profile = video_profile::p_snr_scalable;
            break;
        case 0b010:
            profile = video_profile::p_spatially_scalable;
            break;
        case 0b001:
            profile = video_profile::p_high;
            break;
        default:
            profile = video_profile::p_reserved;
    }
}

void VideoInformation::setLevel(unsigned char level_bits) {
    switch (level_bits) {
        case 0b1010:
            level = video_level::l_low;
            break;
        case 0b1000:
            level = video_level::l_main;
            break;
        case 0b0110:
            level = video_level::l_high_1440;
            break;
        case 0b0100:
            level = video_level::l_high;
            break;
        default:
            level = video_level::l_reserved;
    }
}

void VideoInformation::setProgressiveSequence(bool prog_sequence) {
    progressive_sequence = prog_sequence;
}

void VideoInformation::setChromaFormat(unsigned char chroma_bits) {
    switch (chroma_bits) {
        case 0b00:
            chroma_format = chroma_types::c_reserved;
            break;
        case 0b01:
            chroma_format = chroma_types::c_4_2_0;
            break;
        case 0b10:
            chroma_format = chroma_types::c_4_2_2;
            break;
        case 0b11:
            chroma_format = chroma_types::c_4_4_4;
    }
}

void VideoInformation::setLowDelay(bool d) {
    low_delay = d;
}

void VideoInformation::print() {//TODO make a pretty print for this class
    printf("Video Information:\n\tResolution: %d by %d\n\tAspect Ratio code: %x\n\tFrame rate: %lf\n\tBit Rate: %ld\n\tVBV Buffer: %ld\n\tVideo Profile code: %x\n\tVideo Level Code: %x\n\tIsProgressive: %s\n\tchroma type code: %x\n\tlow_delay:%s\n",
           horizontal_size, vertical_size, aspectRatio, frameRate, bit_rate, vbv_buffer_size, profile, level,
           progressive_sequence ? "true" : "false", chroma_format, low_delay ? "true" : "false");
}
