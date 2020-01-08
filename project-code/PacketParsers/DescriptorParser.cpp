#include "../TSPayloadSections/Descriptor.h"
#include "ESParser.h"

//
// Created by elnsa on 2020-01-07.
//

#define read(n) (ESParser::getInstance()->popNBits((n)))
#define marker(x, y) (valueChecks((x), (y), __func__))

class DescriptorParser{
public:
    static Descriptor::decriptor_struct buildDescriptors(unsigned short descriptor_length){
        for(int i = 0; i < descriptor_length; i++){
            read(8);
        }
        return Descriptor::decriptor_struct{}; //TODO
    }

private:
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
