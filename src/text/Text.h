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

    void WriteToken(std::string token);
    void BeginSentence();
    void RemoveLastSentence();

    void Print();
    void Apply(ReplaceCommand command);
};
