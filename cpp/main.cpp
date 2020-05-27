#include "main.h"

using namespace std;

ListNode<ReplaceCommand> getCommandsFromArgs(char* args[], int argsCount)
{
    ListNode<ReplaceCommand>* firstCommandNode = nullptr;

    auto commandNodePtr = &firstCommandNode;

    for (char** argPtr = args;;) // переделать на while?
    {
        auto argument = new string(*argPtr);

        // "-d100", get 100
        int sentenceIndex = stoi(argument->substr(2));

        // "-d100 ивет", get "ивет"
        string wordEnding = *(argPtr + 1);

        *commandNodePtr = new ListNode<ReplaceCommand>();
        auto commandNode = *commandNodePtr;
        commandNode->Value = new ReplaceCommand(sentenceIndex, wordEnding);

        auto type = argument->at(1);

        if (type == 'r') {
            string replaceWith = *(argPtr + 2);
            commandNode->Value->ReplaceWith = replaceWith;
            argPtr += 3;
            argsCount -= 3;
        }
        else if (type == 'd') {
            argPtr += 2;
            argsCount -= 2;
        }
        else {
            throw new std::invalid_argument("wrong type. must be one of: 'd', 'r'.");
        }

        if (!argsCount) break;

        commandNode->Next = new ListNode<ReplaceCommand>();
        commandNodePtr = &commandNode->Next;
    }

    return *firstCommandNode;
}

int main(int argc, char* argv[])
{
    // TODO: валидация argv?

    string inputFileName = argv[1];
    string outputFileName = argv[2];
    // TODO: валидация inputFileName, outputFileName?

    std::cout << "inputFile: " << inputFileName << "\n";
    std::cout << "outputFile: " << outputFileName << "\n\n";

    auto count = argc - 3; // exclude `mykursach.exe`, `inputFileName` and `outputFileName`
    auto commandArgsPtr = argv + 3; // skip those

    auto firstCommandNode = getCommandsFromArgs(commandArgsPtr, count); // TODO: count

    int i = 0;
    for (auto commandNode = &firstCommandNode; commandNode != nullptr; commandNode = commandNode->Next)
    {
        commandNode->Value->Print();
        cout << i++ << endl << endl;
    }

    // commandsFirstNode.Value.Print();
    // cout << endl;
}
