#include <iostream>
#include "ReplaceCommand.h"

ReplaceCommand::ReplaceCommand()
{
}

ReplaceCommand::ReplaceCommand(int sentenceIndex, std::string wordEnding, std::string replaceWith)
{
    this->SentenceIndex = sentenceIndex;
    this->WordEnding = wordEnding;
    this->ReplaceWith = replaceWith;
}

void ReplaceCommand::Print()
{
    std::cout << "sentenceIndex: " << this->SentenceIndex << "\n";
    std::cout << "wordEnding: " << this->WordEnding << "\n";
    std::cout << "replaceWith: " << this->ReplaceWith << "\n";

    std::cout << '\n';
}
