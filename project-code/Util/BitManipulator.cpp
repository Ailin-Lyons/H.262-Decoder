//
// Created by elnsa on 2019-12-03.
//
#ifndef __BITMANIPULATOR
#define __BITMANIPULATOR

#include <cstdlib>

class BitManipulator {
public:
    /**
     * Reads numBits bits starting at index and returns them as a long long
     * If numBits is larger than sizeof(long long) this will return the numBits lower order digits
     * @param address: address from which to start reading
     * @param numBits: number of bits to be read
     * @return a long long containing lowest order n bits
     */
    static unsigned long long readNBits(const unsigned char *address, unsigned int numBits) {
        unsigned long long out = 0;
        if (numBits == 0) {
            return out;
        }
        size_t i; // declared here as it is used as address in second loop body
        for (i = 0; i < numBits / 8; i++) {
            out = (out << 8u) + address[i];
        }
        for (size_t j = 1; j <= numBits % 8; j++) {
            out = (out << 1u) + ((unsigned int) address[i] >> ((unsigned int) (8 - j)) & 0x1u);
        }
        return out;
    }

    /**
     * Reads numBits bits starting at address+offset and returns them as long long
     * If numBits is larger than sizeof(long long) this will return the numBits lower order digits
     * @param address: address from which to start reading
     * @param numBits: a positive number of bits to be read
     * @param offset: 0-7: bits to offset from index
     * @returna a long long containing lowest order n bits
     */
    static unsigned long long readNBitsOffset(unsigned char *address, unsigned int offset, unsigned int numBits) {
        unsigned long long out = 0;
        if (numBits == 0) {
            return out;
        }
        for (size_t o = offset; o < 8; o++) {
            out = (out << 1u) + (((unsigned int) address[0] >> (7 - o)) & 0x1u);
            numBits--;
            if (numBits <= 0) {
                return out;
            }
        }
        if (numBits > 0) {
            out = (out << numBits) + readNBits(&address[1], numBits);
        }
        return out;
    }
};

#endif

