#ifndef WORDWRAPPER_HPP
#define WORDWRAPPER_HPP
#include "wordprocessor.hpp"
#include <string>

class WordWrapper : public WordProcessor {
public:
    std::string process () {
        // do wrapping
        return wordblock;
    }
    ~WordWrapper() {};
};

#endif

