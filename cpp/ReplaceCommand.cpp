#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "Extensions.cpp"

using namespace std;

class ReplaceCommand
{
public:
    int sentenceIndex;
    string wordEnding;
    string replaceWith;

    ReplaceCommand(int sentenceIndex, string wordEnding, string replaceWith = "")
    {
        this->sentenceIndex = sentenceIndex;
        this->wordEnding = wordEnding;
        this->sentenceIndex = sentenceIndex;
    }

    string ApplyTo(string text)
    {
        auto dotIndex = findCharIndex(text, this->sentenceIndex, ".");

        string firstPart;
        string sentence;
        string restPart;

        if (this->sentenceIndex == 0)
        {
            firstPart = "";
            sentence = text.substr(0, dotIndex);
            restPart = text.substr(dotIndex + 1);
        }
        else
        {
            auto prevDotIndex = findCharIndex(text, this->sentenceIndex - 1, ".");
            firstPart = text.substr(0, prevDotIndex);
            sentence = text.substr(prevDotIndex + 1, dotIndex);
            restPart = text.substr(dotIndex + 1);
        }

        if (sentence == "")
            return text;


        cout << "\n\nreplacing word *" << this->wordEnding << " with: " << this->replaceWith << "\n";

        auto newSentence = ReplaceWord(sentence);

        cout << "old sentence:\n" << sentence << "\n\n";
        cout << "new sentence:\n" << newSentence << "\n\n";

        string newNext = firstPart + "." + newSentence + "." + restPart;

        return newNext;
    }

private:
    string ReplaceWord(string sentence)
    {
        // "hello world"
        // "rld"

        auto words = split(sentence, ' ');

        auto wordEndingLength = this->wordEnding.length();

        string newSentence = "";

        for (auto word: words)
        {
            auto wordLength = word.length();
            string newWord = word;

            if (wordLength >= wordEndingLength
             && word.substr(wordLength - wordEndingLength) == this->wordEnding)
            {
                newWord = this->replaceWith;

                cout << word << " => " << newWord << "\n";
            }

            if (newWord != "")
            {
                if (newSentence != "") newSentence += " ";

                newSentence += newWord;
            }
        }

        return newSentence;
    }
};
