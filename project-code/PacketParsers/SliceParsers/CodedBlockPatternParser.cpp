//
// Created by elnsa on 2020-01-19.
//
#include "ESParser.h"
#include "CodedBlockPatternParser.h"


#define read(n) (ESParser::getInstance()->popNBits((n)))
#define peek(n) (ESParser::getInstance()->peekNBits((n)))


CodedBlockPattern *CodedBlockPatternParser::coded_block_pattern(CodedBlockPattern **out) {
    return nullptr;//TODO
}
