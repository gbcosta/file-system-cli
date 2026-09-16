#include "cli/CommandParser.h"
#include "filesystem/Filesystem.h"

int main(int argc, char *argv[]) {
  Filesystem fs;
  CommandParser commandParser;
  commandParser.execute(argc, argv);
  return 0;
}
