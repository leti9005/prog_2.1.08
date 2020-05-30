#pragma once

#include <iostream>
#include "../base/LinkedList.h"
#include "Sentence.h"
#include "../ReplaceCommand.h"

struct Text
{
private:
    LinkedList<Sentence*> _sentenceSequence;

public:
    static Text FromFile(std::string filename);
    void SaveTo(std::string filename);

    void Add(std::string word);
    void StartNewSentence();
    void RemoveLastSentence();

    void Print();
    void Apply(ReplaceCommand command);
};
