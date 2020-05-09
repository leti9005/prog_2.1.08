#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "ReplaceCommand.cpp"

using namespace std;

vector<ReplaceCommand> getCommandsFromArgs(vector<string> args) {
    vector<ReplaceCommand> commands;

    for (size_t i = 0; i < args.size();) {
        auto arg = args[i];

        // "-d100", get 100
        auto sentenceIndex = stoi(arg.substr(2));

        // "-d100 ивет", get "ивет"
        auto wordEnding = args[i + 1];

        auto command = new ReplaceCommand(
            sentenceIndex,
            wordEnding
        );

        auto type = arg[1];

        if (type == 'r') {
            command->replaceWith = args[i + 2];
            i += 3;
        }
        else {
            i += 2;
        }

        cout << "sentenceIndex: " << command->sentenceIndex << "\n";
        cout << "wordEnding: " << command->wordEnding << "\n";
        cout << "replaceWith: " << command->replaceWith << "\n\n";

        commands.push_back(*command);
    }

    return commands;
}

string readFile(string filePath) {
    std::ifstream t(filePath);
    std::stringstream buffer;
    buffer << t.rdbuf();

    return buffer.str();
}

int main(int argc, char* argv[]) {
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    cout << "inputFile: " << inputFileName << "\n";
    cout << "outputFile: " << outputFileName << "\n\n";

    vector<string> args(&argv[3], &argv[argc]);

    auto commands = getCommandsFromArgs(args);

    auto text = readFile(inputFileName);

    cout << "old text: \n" << text << "\n\n";

    for (auto c: commands) {
        text = c.ApplyTo(text);
    }
    cout << "new text: \n" << text << "\n\n";
}
