#pragma once

#include <iostream>
#include "../base/LinkedList.h"
#include "Sentence.h"

struct Text
{
private:
    LinkedList<Sentence*> _text;

public:
    static Text FromFile(std::string filename);
    void SaveTo(std::string filename);

    void Add(std::string word);
    void StartNewSentence();
    void RemoveLastSentence();

    void Print();
};
