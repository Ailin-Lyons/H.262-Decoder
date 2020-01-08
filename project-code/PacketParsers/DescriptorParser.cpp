#include "../TSPayloadSections/Descriptor.h"
#include "ESParser.h"

//
// Created by elnsa on 2020-01-07.
//

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define marker(x, y) (valueChecks((x), (y), __func__))

class DescriptorParser{
public:
    static Descriptor::decriptor_struct buildDescriptors(unsigned short total_descriptor_length){
        auto descriptors = (Descriptor*) malloc(sizeof(char) * total_descriptor_length);
        unsigned int numDescriptorsKept = 0;
        unsigned int numDescriptorsDropped = 0;
        unsigned int bytesKept = 0;
        unsigned int bytesRead = 0;
        while (bytesRead < total_descriptor_length) {
            Descriptor* descriptor = buildDescriptor();
            if (descriptor->getTag() == Descriptor::descriptor_type::video_stream_descriptor) {
                descriptors[numDescriptorsKept++] = *descriptor;
                bytesKept += 2 + descriptor->getLength();
            } else {
                numDescriptorsDropped++;
            }
            free(descriptor);
            bytesRead += 2 + descriptor->getLength();
        }
        descriptors = (Descriptor*) realloc(descriptors, sizeof(char) * bytesKept);
        return Descriptor::decriptor_struct{numDescriptorsKept, numDescriptorsDropped, descriptors};
    }

private:

    static Descriptor* buildDescriptor() {
        Descriptor::descriptor_type tag = Descriptor::getDescriptorType(read(8));
        unsigned char length = read(8);
        unsigned char mf_rate_flag = 0;
        unsigned char rate_code = 0;
        unsigned char MPEG1_flag = 0;
        unsigned char param_flag = 0;
        unsigned char picture_flag = 0;
        unsigned char profile_and_level_indication = 0;
        unsigned char chroma_format = 0;
        unsigned char frame_rate_extension_flag = 0;
        if (tag == Descriptor::descriptor_type::video_stream_descriptor) {
            mf_rate_flag = read(1);
            rate_code = read(4);
            MPEG1_flag = read(1);
            param_flag = read(1);
            picture_flag = read(1);
            if (MPEG1_flag == 0) {
                profile_and_level_indication = read(8);
                chroma_format = read(2);
                frame_rate_extension_flag = read(1);
                marker(5, 0b11111);
            }
        } else {
            for (unsigned int i = 0; i < length; i++) {
                read(8);
            }
        }
        return new Descriptor(tag, length, mf_rate_flag, rate_code, MPEG1_flag, param_flag, picture_flag, profile_and_level_indication,
                chroma_format, frame_rate_extension_flag);
    }


    static void valueChecks(unsigned int numBits, unsigned long long expectedVal, const std::string& funcName) {
        unsigned long long readVal = read(numBits);
        if(readVal != expectedVal) {
            std::string s = "PASParser::";
            s.append(funcName);
            s.append(": bad packet! Expected value = ");
            s.append(std::to_string(expectedVal));
            s.append(", ReadVal = ");
            s.append(std::to_string(readVal));
            throw PacketException(s);
        }
    }
};
