#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

// TODO: вынести это в класс который этим всем будет заниматься?

// возвращает индекс number'ового-вхождения символа delimiter'а.
// Короче: находит, в какой позиции находится number-овый делимитер.
// Например: десятая точка, сотая запятая, пятый твёрдый знак. Вернут индекс символа в text.
int findCharIndex(const string& text, int number, string delimiter)
{
    auto delimIndex = text.find(delimiter);
    auto sentence = text.substr(0, delimIndex);

    if (number == 0)
        return delimIndex;

    auto restText = text.substr(delimIndex + 1);

    for (int i = 1; i < number; i++)
    {
        delimIndex = restText.find(delimiter);
        restText = text.substr(delimIndex + 1);
    }

    return delimIndex;
}

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
