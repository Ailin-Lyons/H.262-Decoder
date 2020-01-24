//
// Created by elnsa on 2019-12-29.
//

#ifndef DIRECTED_STUDIES_EXTENSIONPAYLOAD_H
#define DIRECTED_STUDIES_EXTENSIONPAYLOAD_H

#include "ExtensionPacket.h"

class SequenceExtensionPacket : public ExtensionPacket {
public:
    enum class chroma_format_type {
        reserved,
        cf_420,
        cf_422,
        cf_444
    };
private:
    unsigned char profile_and_level_indication; //8-bits
    bool progressive_sequence; //1-bit
    chroma_format_type chroma_format;
    unsigned char horizontal_size_extension; //2-bits
    unsigned char vertical_size_extension;    //2-bits
    unsigned short bit_rate_extension; //12-bits
    unsigned char vbv_buffer_size_extension; //8-bits
    bool low_delay; //1-bit
    unsigned char frame_rate_extension_n; //2-bits
    unsigned char frame_rate_extension_d; //5-bits

public:
    struct initializerStruct {
        ExtensionPacket::extension_type e_type;
        unsigned char profile_and_level_indication; //8-bits
        bool progressive_sequence; //1-bit
        chroma_format_type chroma_format;
        unsigned char horizontal_size_extension; //2-bits
        unsigned char vertical_size_extension; //2-bits
        unsigned short bit_rate_extension; //12-bits
        unsigned char vbv_buffer_size_extension; //8-bits
        bool low_delay; //1-bit
        unsigned char frame_rate_extension_n; //2-bits
        unsigned char frame_rate_extension_d; //5-bits
    };

    /**
     * Constructor
     */
    SequenceExtensionPacket(initializerStruct init);

    void print() override;

    bool operator==(const SequenceExtensionPacket &rhs) const;

    bool operator!=(const SequenceExtensionPacket &rhs) const;

    ~SequenceExtensionPacket() = default;

    unsigned short getHExt() const;

    unsigned short getVExt() const;

    unsigned int getBitRateExt() const;

    unsigned int getVBVBufVal();

    unsigned char getProfileAndLevelIndication() const;

    bool getProgSeq() const;

    chroma_format_type getChromaFormat();

    bool getLowDelay();

    unsigned char getFrameExtD();

    unsigned char getFrameExtN();

    static chroma_format_type getChromaFormatCode(unsigned char bits);
};

#endif //DIRECTED_STUDIES_EXTENSIONPAYLOAD_H
