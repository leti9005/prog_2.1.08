#pragma once

#include <iostream>

class ReplaceCommand
{
public:
    int SentenceIndex;
    std::string WordEnding;
    std::string ReplaceWith;

    ReplaceCommand();
    ReplaceCommand(int sentenceIndex, std::string wordEnding, std::string replaceWith = "");

    void Print();

    // void ApplyToSentence(std::string sentence);
};
