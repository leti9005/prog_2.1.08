#include "base/Queue.h"
#include "text/Sentence.h"
#include "text/Text.h"
#include "ReplaceCommand.h"

Queue<ReplaceCommand> getCommandQueueFromArgs(char* args[], int argsCount);
int main(int argc, char* argv[]);
