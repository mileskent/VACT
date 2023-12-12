#ifndef WORDPROCESSOR_HPP
#define WORDPROCESSOR_HPP
#include <string>

class WordProcessor {
public:
    virtual ~WordProcessor() {};
    virtual std::string process () = 0;
protected:
    std::string wordblock; 
};

#endif
