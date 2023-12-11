#include <string>
#include "word.hpp"

class Verb : public Word {
public:
    Verb() : Word() { this->tense = "Undefined"; }; // shouldn't really be called
    Verb(std::string w, std::string d, int f, std::string t) : Word(w, d, 1, f) { settense(t); }
    Verb(std::string w, std::string d, std::string t) : Word(w, d, 1, 0) { settense(t); }
    void settense (std::string tense) {
        this->tense = tense;
    }
    std::string gettense () const {
        return tense;
    }

    std::string getinfo () const {
         return "Verb: " + this->getword() + 
            ", Definition: " + this->getdefinition() + 
            ", Grammar: " + this->getgrammar() + 
            ", Familiarity: " + this->getfamiliarity() +
            ", Tense: " + tense; 
    }

private:
    // string for now, describing the kind of conjugation this particular word is
    // i.e. past, present, future, gerund, infinitive, etc.
    std::string tense;
};
