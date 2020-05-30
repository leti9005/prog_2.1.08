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

bool EndsWith(string str, string ending)
{
    int substrFrom = str.length() - ending.length();
    return substrFrom >= 0 && ending == str.substr(substrFrom);
}

void Text::Apply(ReplaceCommand command)
{
    auto sentence = _sentenceSequence.ElementAt(command.SentenceIndex)->Value;

    ListNode<string>* word = sentence->_head;
    if (!word) return;

    while (EndsWith(word->Value, command.WordEnding))
    {
        if (command.ReplaceWith != "")
        {
            word->Value = command.ReplaceWith;
            break;
        }

        sentence->_head = word->Next;
        delete word;
        word = sentence->_head;

        // ой, удалили последнее слово!
        if (!word) return;
    }

    auto nextWord = word->Next;
    do
    {
        if (!nextWord) break;

        if (!EndsWith(nextWord->Value, command.WordEnding))
        {
            word = nextWord;
            continue;
        }

        if (command.ReplaceWith != "")
        {
            nextWord->Value = command.ReplaceWith;
        }
        else
        {
            word->Next = nextWord->Next;
            delete nextWord;

            nextWord = word;
        }

        word = nextWord;
    } while (nextWord = nextWord->Next);

}

void Text::RemoveLastSentence()
{
    _sentenceSequence.RemoveLastNode();
}

void Text::Add(string word)
{
    if (_sentenceSequence.IsEmpty())
    {
        StartNewSentence();
    }

    auto lastSentenceNode = _sentenceSequence.GetLast();
    auto sentence = lastSentenceNode->Value;

    sentence->Add(word);
}

void Text::StartNewSentence()
{
    _sentenceSequence.Add(new Sentence());
}

void Text::Print()
{
    auto sentenceNodePtr = _sentenceSequence._head;

    if (!sentenceNodePtr)
    {
        cerr << "# Text is empty." << endl;
        return;
    }

    do
    {
        auto sentence = *sentenceNodePtr;
        auto wordNode = sentence.Value->_head;

        if (!wordNode) continue;

        cout << (*wordNode).Value << " ";

        while (wordNode = wordNode->Next)
        {
            cout << (*wordNode).Value << " ";
        }

        cout << endl;
    } while (sentenceNodePtr = sentenceNodePtr->Next);
}
