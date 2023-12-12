#ifndef WORDCOLORIZER_HPP
#define WORDCOLORIZER_HPP
#include "wordprocessor.hpp"
#include <string>

class WordColorizer : public WordProcessor {
public:
    std::string process () {
        // do colorizing
        return wordblock;
    }
    ~WordColorizer() {};
};

#endif


