#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    auto text = Text::FromFile(inputFileName);

    // словом CommandArgs будем называть те аргументы, из которых можно слепить ReplaceCommand.
    int nonCommandArgsCount = 3; // из этих не слепишь: `mykursach.exe`, `inputFileName.txt`, `outputFileName.txt`

    auto commandArgsPtr = argv + nonCommandArgsCount;
    auto commandArgsCount = argc - nonCommandArgsCount;

    auto commandQueue = getCommandQueueFromArgs(commandArgsPtr, commandArgsCount);

    while (!commandQueue.IsEmpty())
    {
        auto command = commandQueue.Dequeue();
        text.Apply(command);
    }

    text.Print();
    cout << endl;

    text.SaveTo(outputFileName);
}


// очень страшная логика парсинга аргументов. можно не читать.
//  превращает "-d2 wordEnd" в ReplaceCommand(2, "wordEnd")
//  превращает "-r10 wordEnd replaceWith" в ReplaceCommand(10, "wordEnd", "replaceWith")
// кладёт всё это в Queue<ReplaceCommand>.
Queue<ReplaceCommand> getCommandQueueFromArgs(char* args[], int argsCount)
{
    Queue<ReplaceCommand> queue(argsCount);

    char** argPtr = args;

    while (argsCount)
    {
        string argument(*argPtr);

        // "-d100", get 100
        int sentenceIndex = stoi(argument.substr(2));

        // "-d100 ивет", get "ивет"
        string wordEnding = *(argPtr + 1);

        ReplaceCommand command(sentenceIndex, wordEnding);

        char type = argument.at(1);

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
