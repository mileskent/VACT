#include <string>
#include "word.hpp"

class Verb : public Word {
public:
    Verb() : Word() { this->tense = "Undefined"; };
    Verb(std::string w, std::string d, int g, int f, std::string t) : Word(w, d, g, f) { settense(t); }
    void settense (std::string tense) {
        this->tense = tense;
    }
private:
    // string for now, describing the kind of conjugation this particular word is
    // i.e. past, present, future, gerund, infinitive, etc.
    std::string tense;
};
