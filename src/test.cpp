#include <iostream>
#include <variant>
#include "word.hpp"
#include "verb.hpp"
#include <string>

using AnyWord = std::variant<Word, Verb>;

int main (void)
{
    vector<AnyWord> words;
    Word w1 ("Word One", "It's the first word", 0);
    Verb v1 ("Verb One", "It's the first verb", "Tense");
    std::cout << v1.getinfo() << std::endl;
    words.push_back (w1);
    words.push_back (v1);
    for (const auto& obj : words) {
        std::visit([](const auto& obj) { 
            std::cout << obj.getinfo() << std::endl; 
        }, obj);
    }
    return 0;
}
