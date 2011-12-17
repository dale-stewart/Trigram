////////////////////////////////////////////////////////////////////////////////
///
/// @file   Trigram.h
/// @brief  Brief description here.
///

#ifndef TRIGRAM_H
#define TRIGRAM_H

#include <map>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>

typedef std::pair<std::string, std::string> word_pair;
typedef std::vector<std::string> word_vector;
typedef std::map<word_pair, word_vector> tuple_map;
typedef boost::char_separator<char> separator;
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

class Randomizer
{
public:
    virtual int Random(int modulo) = 0;
};

class Trigram
{
public:
    Trigram(const std::string& text, Randomizer* randomizer = 0);

    word_vector operator[](const word_pair& wordPair);
    std::string generateSentence(int maxLength = 20);

private:
    tuple_map tuples;
    Randomizer* randomizer_;

    word_pair getStartingWordPair();
};

#endif // TRIGRAM_H
