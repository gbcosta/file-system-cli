#include "cli/CommandParser.h"

int main(int argc, char *argv[]) {
  CommandParser commandParser;
  commandParser.execute(argc, argv);
  return 0;
}
