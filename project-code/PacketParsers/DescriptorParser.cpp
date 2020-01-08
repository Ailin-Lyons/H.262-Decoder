#include "../TSPayloadSections/Descriptor.h"
#include "ESParser.h"

//
// Created by elnsa on 2020-01-07.
//
class DescriptorParser{
public:
    static Descriptor::decriptor_struct buildDescriptors(unsigned short descriptor_length){
        ESParser* esParser = ESParser::getInstance();
        for(int i = 0; i < descriptor_length; i++){
            esParser->popNBits(8);
        }
        return Descriptor::decriptor_struct{}; //TODO
    }
};
