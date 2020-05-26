#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    auto inputFileName = argv[1];
    auto outputFileName = argv[2];
    auto nonRepeatedCharacter = *argv[3];

    cout << "inputFile: " << inputFileName << "\n";
    cout << "outputFile: " << outputFileName << "\n\n";

    char ch;
    fstream fin(inputFileName, fstream::in);
    fstream fout(outputFileName, fstream::out);

    while (fin >> noskipws >> ch) {

        cout << ch;
        fout.write(&ch, sizeof(char));

        if (ch != nonRepeatedCharacter) {
            cout << ch;
            fout.write(&ch, sizeof(char));
        }
    }
}
