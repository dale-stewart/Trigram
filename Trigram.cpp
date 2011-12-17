////////////////////////////////////////////////////////////////////////////////
///
/// @file   Trigram.cpp
/// @brief  Brief description here.
///

#include "Trigram.h"

Trigram::Trigram(const std::string& text, Randomizer* randomizer) :
    randomizer_(randomizer)
{
    separator sep(" ");
    tokenizer tokens(text, sep);

    tokenizer::iterator iter;
    tokenizer::iterator iter2;

    word_pair wordPair;

    for (iter = tokens.begin(); iter != tokens.end(); iter++)
    {
        iter2 = iter;
        wordPair.first = *iter2;
        iter2++;
        if (iter2 != tokens.end())
        {
            wordPair.second = *iter2;
            iter2++;
            if (iter2 != tokens.end())
                tuples[wordPair].push_back(*iter2);
        }
    }
}

word_vector Trigram::operator[](const word_pair& wordPair)
{
    word_vector returnValue;

    tuple_map::iterator iter;

    iter = tuples.find(wordPair);

    if (iter != tuples.end())
        returnValue = (*iter).second;

    return returnValue;
}

std::string Trigram::generateSentence(int maxLength)
{
    std::string returnValue;

    if (randomizer_)
    {
        word_pair wordPair = getStartingWordPair();

        returnValue += wordPair.first;
        returnValue += " ";
        returnValue += wordPair.second;

        maxLength -= 2;

        word_vector words;
        int wordIndex;
        std::string word;

        tuple_map::iterator iter = tuples.find(wordPair);
        while (maxLength-- && iter != tuples.end())
        {
            words = (*iter).second;
            wordIndex = randomizer_->Random(words.size());
            word = words[wordIndex];
            returnValue += " ";
            returnValue += word;

            wordPair = word_pair(wordPair.second, word);

            iter = tuples.find(wordPair);
        }
    }

    return returnValue;
}

word_pair Trigram::getStartingWordPair()
{
    word_pair wordPair;

    int selectedTuple = randomizer_->Random(tuples.size());

    tuple_map::iterator iter;

    for (iter = tuples.begin(); iter != tuples.end(); iter++)
    {
        if (selectedTuple == 0)
        {
            wordPair = (*iter).first;
            int selectedWord = randomizer_->Random((*iter).second.size());
            std::string word = (*iter).second[selectedWord];
            break;
        }

        --selectedTuple;
    }

    return wordPair;
}
