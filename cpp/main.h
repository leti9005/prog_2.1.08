#include <fstream>
#include <iostream>
#include "Queue.h"
#include "WordNode.h"
#include "SentenceNode.h"
#include "ReplaceCommand.h"

Queue<ReplaceCommand> getCommandQueueFromArgs(char* args[], int argsCount);
int main(int argc, char* argv[]);
