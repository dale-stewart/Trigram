////////////////////////////////////////////////////////////////////////////////
///
/// @file   TrigramTest.cpp
/// @brief  Brief description here.
///

#include <gtest/gtest.h>
#include <iostream>
#include "Trigram.h"

class FakeRandomizer : public Randomizer
{
public:
    FakeRandomizer(int index = 0) : index_(index) {}

    virtual int Random(int modulo) { return index_ % modulo; }

private:
    int index_;
};

class TrigramTest : public ::testing::Test
{
public:
    TrigramTest() :
        text("I wish I may I wish I might"),
        trigram(text)
    {}

    std::string text;
    Trigram trigram;
};

TEST_F(TrigramTest, TrigramProducesExpectedTuples)
{
    Trigram trigram(text);

    word_pair I_wish("I", "wish");
    word_pair wish_I("wish", "I");
    word_pair I_may("I", "may");
    word_pair may_I("may", "I");

    ASSERT_EQ(size_t(2), trigram[I_wish].size());
    EXPECT_TRUE(trigram[I_wish][0] == "I");
    EXPECT_TRUE(trigram[I_wish][1] == "I");

    ASSERT_EQ(size_t(2), trigram[wish_I].size());
    EXPECT_STREQ(trigram[wish_I][0].c_str(), "may");
    EXPECT_STREQ(trigram[wish_I][1].c_str(), "might");

    ASSERT_EQ(size_t(1), trigram[I_may].size());
    EXPECT_TRUE(trigram[I_may][0] == "I");

    ASSERT_EQ(size_t(1), trigram[may_I].size());
    EXPECT_TRUE(trigram[may_I][0] == "wish");
}

TEST_F(TrigramTest, CanGenerateSentence)
{
    FakeRandomizer randomizer;

    Trigram trigram(text, &randomizer);

    std::string generatedSentence = trigram.generateSentence(7);

    EXPECT_GT(generatedSentence.length(), static_cast<size_t>(0));
    EXPECT_STREQ("I may I wish I may I", generatedSentence.c_str());
}

TEST_F(TrigramTest, CanGenerateDifferentSentence)
{
    FakeRandomizer randomizer(1);

    Trigram trigram(text, &randomizer);

    std::string generatedSentence = trigram.generateSentence(7);

    EXPECT_STREQ("I wish I might", generatedSentence.c_str());
}

TEST_F(TrigramTest, CanGenerateAnotherDifferentSentence)
{
    FakeRandomizer randomizer(2);

    Trigram trigram(text, &randomizer);

    std::string generatedSentence = trigram.generateSentence(7);

    EXPECT_STREQ("may I wish I may I wish", generatedSentence.c_str());
}

TEST_F(TrigramTest, CanGenerateStillAnotherDifferentSentence)
{
    FakeRandomizer randomizer(3);

    Trigram trigram(text, &randomizer);

    std::string generatedSentence = trigram.generateSentence(7);

    EXPECT_STREQ("wish I might", generatedSentence.c_str());
}

