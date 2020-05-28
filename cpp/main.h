#include <fstream>
#include <iostream>
#include "Queue.h"
#include "ReplaceCommand.h"

Queue<ReplaceCommand> getCommandQueueFromArgs(char* args[], int argsCount);
int main(int argc, char* argv[]);
