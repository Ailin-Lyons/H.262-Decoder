#include <cstdio>

//
// Created by elnsa on 2019-12-03.
//
class BitManipulator {
public:
    /**
     * Reads numBits bits starting at index and returns them as a long long
     * @param index: address from which to start reading
     * @param numBits: positive number of bits to be read
     * @return a long long containing number in lowest n bits
     */
    static long long ReadNBits(unsigned char *index, int numBits) {
        unsigned long long out = 0;
        int i;
        unsigned int arr[numBits / 8 + 1];
        for (int x = 0; x < numBits / 8 + 1; x++) {
            arr[x] = (unsigned int) index[x];
        }
        for (i = 0; i < numBits / 8; i++) {
            out = (out << 8) + index[i];
        }
        for (int j = 1; j <= numBits % 8; j++) {
            out = (out << 1) + ((index[i] >> (8 - j)) & 0x1);
        }
        return out;
    }

    /**
     * Reads numBits bits starting at index+offset and returns them as long long
     * @param index: address from which to start reading
     * @param numBits: a positive number of bits to be read
     * @param offset: a non-negative number of bits to offset from index
     * @returna a long long containing number in lowest n bits
     */
    static long long ReadNBitsOffset(unsigned char *index, int offset, int numBits) {
        unsigned long long out = 0;
        return out; // TODO implement
    }
};

