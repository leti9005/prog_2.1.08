#include "main.h"

using namespace std;

Queue<ReplaceCommand> getCommandQueueFromArgs(char* args[], int argsCount)
{
    Queue<ReplaceCommand> queue(argsCount);

    char** argPtr = args;

    while (argsCount)
    {
        auto argument = new string(*argPtr);

        // "-d100", get 100
        int sentenceIndex = stoi(argument->substr(2));

        // "-d100 ивет", get "ивет"
        string wordEnding = *(argPtr + 1);

        ReplaceCommand command(sentenceIndex, wordEnding);

        auto type = argument->at(1);

        if (type == 'r') {
            string replaceWith = *(argPtr + 2);
            command.ReplaceWith = replaceWith;

            int skippedArgsCount = 3;

            argPtr += skippedArgsCount;
            argsCount -= skippedArgsCount;
        }
        else if (type == 'd') {
            int skippedArgsCount = 2;

            argPtr += skippedArgsCount;
            argsCount -= skippedArgsCount;
        }
        else {
            throw new std::invalid_argument("Wrong operation type. Must be one of: 'd' (for delete), 'r' (for replace).");
        }

        queue.Enqueue(command);
    }

    return queue;
}

int main(int argc, char* argv[])
{
    // TODO: валидация argv?

    string inputFileName = argv[1];
    string outputFileName = argv[2];
    // TODO: валидация inputFileName, outputFileName?

    std::cout << "inputFile: " << inputFileName << "\n";
    std::cout << "outputFile: " << outputFileName << "\n\n";


    // -- извлечь метод --

    std::ifstream inputStream;
    inputStream.open(inputFileName);

    auto text = new SentenceNode();
    auto firstSentencePtrPtr = &text;

    auto currentSentencePtr = *firstSentencePtrPtr;

    string word;
    WordNode* currentWordNodePtr;
    while (inputStream >> word)
    {
        // if this is a first word of sentence
        if (currentWordNodePtr == nullptr)
        {
            // create first word node
            currentWordNodePtr = new WordNode();
            currentWordNodePtr->Value = &word;
            currentSentencePtr->Value = currentWordNodePtr;

            cout << "First word: " << word << endl;
        }
        else
        {
            // else create next WordNode*
            currentWordNodePtr->Next = new WordNode();
            currentWordNodePtr = currentWordNodePtr->Next;

            currentWordNodePtr->Value = &word;
            cout << "Taking next: " << *currentWordNodePtr->Value << endl;
        }

        if (word.back() == '.')
        {
            // take the word without the dot
            auto wordWithoutDot = word.substr(0, word.length() - 1);
            currentWordNodePtr->Value = &wordWithoutDot;

            // create node for the next sentence
            cout << "Last word: " << *currentWordNodePtr->Value << endl << endl;
            currentSentencePtr->Next = new SentenceNode();
            currentSentencePtr = currentSentencePtr->Next;
        }
    }

    // delete last empty node.
    delete currentSentencePtr;

    inputStream.close();
    delete &inputStream;

    // show the firstest word
    auto firstWordPtr = (*firstSentencePtrPtr)->Value;
    cout << *firstWordPtr->Value << *text->Value->Value << endl;

    //////////////


    int nonCommandArgsCount = 3; // "mykursach.exe", `inputFileName`, `outputFileName`

    auto commandArgsPtr = argv + nonCommandArgsCount;
    auto commandArgsCount = argc - nonCommandArgsCount;

    auto commandQueue = getCommandQueueFromArgs(commandArgsPtr, commandArgsCount);

    while (!commandQueue.IsEmpty())
    {
        auto command = commandQueue.Dequeue();
        // command.Print();
    }
}
