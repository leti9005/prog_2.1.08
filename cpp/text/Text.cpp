#include "Text.h"

#include <fstream>
#include <iostream>

using namespace std;

Text Text::FromFile(string filename)
{
    ifstream inputStream;
    inputStream.open(filename);

    Text text;
    string word;
    while (inputStream >> word)
    {
        if (word.back() != '.')
        {
            text.Add(word);
        }
        else
        {
            auto wordWithoutDot = word.substr(0, word.length() - 1);

            text.Add(wordWithoutDot);
            text.StartNewSentence();

            cout << "Last word: " << wordWithoutDot << endl << endl;
        }
    }

    text.RemoveLastSentence();

    inputStream.close();

    return text;
}

void Text::SaveTo(string filename)
{
    // todo: implement me!
}

void Text::RemoveLastSentence()
{
    _text.RemoveLastNode();
}

void Text::Add(string word)
{
    cout << "checking last sentence: " << endl;

    if (_text.IsEmpty())
    {
        cout << "starting new sentence" << endl;
        StartNewSentence();
    }

    auto lastSentenceNode = _text.GetLast();
    auto sentence = lastSentenceNode->Value;

    sentence->Add(word);
}

void Text::StartNewSentence()
{
    _text.Add(new Sentence());
}

void Text::Print()
{
    auto sentenceNodePtr = _text.GetHead();

    if (!sentenceNodePtr)
    {
        cerr << "# Text is empty." << endl;
        return;
    }

    do
    {
        auto sentence = *sentenceNodePtr;
        auto wordNode = sentence.Value->_head;

        cout << (*wordNode).Value << " ";

        while (wordNode = wordNode->Next)
        {
            cout << (*wordNode).Value << " ";
        }

        cout << endl;
    } while (sentenceNodePtr = sentenceNodePtr->Next);
}
