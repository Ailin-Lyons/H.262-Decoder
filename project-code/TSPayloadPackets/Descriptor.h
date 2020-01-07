//
// Created by elnsa on 2020-01-07.
//

#ifndef PROJECT_CODE_DESCRIPTOR_H
#define PROJECT_CODE_DESCRIPTOR_H

/**
 * This class only handles video_stream_descriptors. All other descriptors will end up as stubs
 */
class Descriptor{
    enum class descriptor_type{
        video_stream_descriptor,
        unhandled_desriptor_type
    };
    static descriptor_type getDescriptorType(unsigned char descriptor_tag){
        switch (descriptor_tag){
            case 0x02:
                return descriptor_type::video_stream_descriptor;
            default:
                return descriptor_type::unhandled_desriptor_type;
        }

    };

    unsigned char descriptor_tag; // 8-bit
    unsigned char descriptor_length; // 8-bit
    unsigned char multiple_frame_rate_flag; // 1-bit
    unsigned char frame_rate_code; // 4-bit
    unsigned char MPEG_1_only_flag; // 1-bit
    unsigned char constrained_parameter_flag;
    unsigned char still_picture_flag;
    unsigned char profile_and_level_indication;
    unsigned char chroma_format;
    unsigned char frame_rate_extension_flag;
};
#endif //PROJECT_CODE_DESCRIPTOR_H
