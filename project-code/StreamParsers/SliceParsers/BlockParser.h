//
// Created by elnsa on 2020-01-23.
//

#ifndef PROJECT_CODE_BLOCKPARSER_H
#define PROJECT_CODE_BLOCKPARSER_H

#include "ESParser.h"
#include "../../PictureDecoder/Slice/Block.h"


#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))

class BlockParser {
private:
    struct vlc {
        unsigned char numbits;
        unsigned char value;
        unsigned short key;
    };
    struct vlc_signed {
        unsigned int key;
        unsigned char run;
        unsigned char level;
        unsigned char numbits;
    };
    static vlc table_b12[];
    static vlc table_b13[];
    static vlc_signed table_b14[];
    static vlc_signed table_b15[];
public:
    /**
     * Builds a Block() from ESParser data, starting after the start_code/stream_id
     * H.262 6.2.6
     */
    static void block(size_t i, Block **destination);

private:
    static unsigned char getDctDcSizeLuminance();

    static unsigned char getDctDcSizeChrominance();

    static unsigned char getDctDcSize(unsigned char cc);

    static void initializePatternCode(bool pattern_code[12]);

    static int readSign(int level);

    static bool checkEndCode(bool b);

    static vlc_signed getVLCCode(bool flag);

    static void populateQFS(unsigned char *n, int *QFS, int signed_level, unsigned char run);

    static short escapeSignHelper(short signed12BitValue);

    static void buildDCCoefficient(unsigned char dct_dc_size, int dct_dc_differential,
                                   unsigned char *n, int *QFS, unsigned char cc);

    static void
    handleCoefficients(bool tableFlag, unsigned char *n, int *QFS);

    static int integerPow(int base, int exp);
};


#endif //PROJECT_CODE_BLOCKPARSER_H
