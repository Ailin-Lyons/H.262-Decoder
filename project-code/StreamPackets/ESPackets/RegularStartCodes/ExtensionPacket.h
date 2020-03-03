//
// Created by elnsa on 2020-01-17.
//

#ifndef PROJECT_CODE_EXTENSIONPACKET_H
#define PROJECT_CODE_EXTENSIONPACKET_H

#include <iostream>
#include "../ESPacket.h"

/**
 * This is an interface for all elementary stream packets.
 */
class ExtensionPacket : public ESPacket {
public:
    enum class extension_type {
        reserved,
        sequence,
        sequence_display,
        quant_matrix,
        copyright,
        sequence_scalable,
        picture_display,
        picture_coding,
        picture_spatial_scalable,
        picture_temporal_scalable,
        camera_parameters,
        itu_t
    };

/**
 * Converts the 4-bit value of the identifier to the correct enum value for extension_type
 * @param identifier - 4-bit value representing the extension_type
 * @return ESPacket::extension_type - the enum value
 */
    static extension_type getExtensionCode(unsigned char identifier) {
        switch (identifier) {
            case 0x01 :
                return extension_type::sequence;
            case 0x02 :
                return extension_type::sequence_display;
            case 0x03 :
                return extension_type::quant_matrix;
            case 0x04 :
                return extension_type::copyright;
            case 0x05 :
                return extension_type::sequence_scalable;
            case 0x07 :
                return extension_type::picture_display;
            case 0x08 :
                return extension_type::picture_coding;
            case 0x09 :
                return extension_type::picture_spatial_scalable;
            case 0x0A :
                return extension_type::picture_temporal_scalable;
            case 0x0B :
                return extension_type::camera_parameters;
            case 0x0C :
                return extension_type::itu_t;
            default:
                return extension_type::reserved;
        }
    }

    extension_type getExtensionType() const {
        return e_type;
    }

protected:
    ExtensionPacket::extension_type e_type = extension_type::reserved;
};

#endif //PROJECT_CODE_EXTENSIONPACKET_H
