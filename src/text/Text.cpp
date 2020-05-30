#include "Text.h"

#include <fstream>
#include <iostream>

using namespace std;

bool EndsWith(string str, string ending)
{
    int substrFrom = str.length() - ending.length();
    return substrFrom >= 0 && ending == str.substr(substrFrom);
}

string TrimLastChar(string str)
{
    return str.substr(0, str.length() - 1);
}

bool ispunct(char c)
{
    char punctuation[] = ",:";

    for (char p: punctuation) {
        if (c == p) return true;
    }

    return false;
}

bool ispunct(string str)
{
    if (str.length() != 1) return false;

    auto back = str.back();

    return ispunct(back);
}

Text Text::FromFile(string filename)
{
    ifstream inputStream;
    inputStream.open(filename);

    Text text;
    string word;
    while (inputStream >> word)
    {
        text.WriteToken(word);
    }

    inputStream.close();

    auto firstWordInTheLastSentencePtr = text._sentenceSequence.GetLast()->Value->_head;
    if (!firstWordInTheLastSentencePtr)
    {
        text.RemoveLastSentence();
    }

    return text;
}

void Text::Apply(ReplaceCommand command)
{
    auto sentence = _sentenceSequence.ElementAt(command.SentenceIndex)->Value;

    auto tokenNode = sentence->_head;
    if (!tokenNode) return;

    while (EndsWith(tokenNode->Value, command.WordEnding))
    {
        if (command.ReplaceWith != "")
        {
            tokenNode->Value = command.ReplaceWith;
            break;
        }

        sentence->_head = tokenNode->Next;
        delete tokenNode;
        tokenNode = sentence->_head;

        // если удалили последнее слово, больше с этим предложением ничего не поделаешь
        if (!tokenNode) return;
    }

    auto nextTokenNode = tokenNode->Next;
    do
    {
        if (!nextTokenNode) break;

        if (ispunct(nextTokenNode->Value)) continue;

        if (!EndsWith(nextTokenNode->Value, command.WordEnding))
        {
            tokenNode = nextTokenNode;
            continue;
        }

        if (command.ReplaceWith != "")
        {
            nextTokenNode->Value = command.ReplaceWith;
        }
        else
        {
            tokenNode->Next = nextTokenNode->Next;
            delete nextTokenNode;

            nextTokenNode = tokenNode;
        }

        tokenNode = nextTokenNode;
    } while (nextTokenNode = nextTokenNode->Next);
}

void Text::RemoveLastSentence()
{
    _sentenceSequence.RemoveLastNode();
}

void Text::WriteToken(string token)
{
    if (_sentenceSequence.IsEmpty())
    {
        BeginSentence();
    }

    auto lastSentenceNode = _sentenceSequence.GetLast();
    auto sentence = lastSentenceNode->Value;

    char tokenBack = token.back();

    if (tokenBack == '.')
    {
        sentence->Add(TrimLastChar(token));
        BeginSentence();
    }
    else if (ispunct(tokenBack))
    {
        sentence->Add(TrimLastChar(token));
        sentence->Add(string(1, tokenBack));
    }
    else
    {
        sentence->Add(token);
    }
}

void Text::BeginSentence()
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
        auto tokenNodePtr = sentenceNodePtr->Value->_head;

        if (!tokenNodePtr) continue;

        do
        {
            cout << tokenNodePtr->Value;

            if (tokenNodePtr->Next && !ispunct(tokenNodePtr->Next->Value))
            {
                cout << " ";
            }
        } while (tokenNodePtr = tokenNodePtr->Next);

        cout << endl;
    } while (sentenceNodePtr = sentenceNodePtr->Next);
}

void Text::SaveTo(string filename)
{
    ofstream output(filename);

    auto sentenceNodePtr = _sentenceSequence._head;

    do
    {
        if (sentenceNodePtr != _sentenceSequence._head)
        {
            output << " ";
        }

        auto tokenNodePtr = sentenceNodePtr->Value->_head;

        if (!tokenNodePtr) continue;

        do
        {
            output << tokenNodePtr->Value;

            if (tokenNodePtr->Next && !ispunct(tokenNodePtr->Next->Value))
            {
                output << " ";
            }
        } while (tokenNodePtr = tokenNodePtr->Next);

        output << ".";
    } while (sentenceNodePtr = sentenceNodePtr->Next);

    output.close();
}
