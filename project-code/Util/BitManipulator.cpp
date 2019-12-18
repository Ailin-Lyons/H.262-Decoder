//
// Created by elnsa on 2019-12-03.
//
class BitManipulator { // TODO thoroughly test this class as we will use it a lot
public:
    /**
     * Reads numBits bits starting at index and returns them as a long long
     * If numBits is larger than sizeof(long long) this will return the lower digits
     * @param address: address from which to start reading
     * @param numBits: positive number of bits to be read
     * @return a long long containing number in lowest n bits
     */
    static long long ReadNBits(unsigned char *address, int numBits) {
        unsigned long long out = 0;
        int i; // declared here as it is used as address in second loop body
        for (i = 0; i < numBits / 8; i++) {
            out = (out << 8) + address[i];
        }
        for (int j = 1; j <= numBits % 8; j++) {
            out = (out << 1) + ((address[i] >> (8 - j)) & 0x1);
        }
        return out;
    }

    /**
     * Reads numBits bits starting at index+offset and returns them as long long
     * If numBits is larger than sizeof(long long) this will return the lower digits
     * @param address: address from which to start reading
     * @param numBits: a positive number of bits to be read
     * @param offset: 0-7: bits to offset from index
     * @returna a long long containing number in lowest n bits
     */
    static long long ReadNBitsOffset(unsigned char *address, int offset, int numBits) {
        unsigned long long out = 0;
        for (int o = offset; o < 8; o++) {
            out = (out << 1) + ((address[0] >> (7 - offset)) & 0x1);
            numBits--;
            if(numBits <= 0){
                return out;
            }
        }
        if(numBits > 0){
            out = (out << numBits) + ReadNBits(&address[1], numBits);
        }
        return out;
    }
};

