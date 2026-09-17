#include "CommandParser.h"
#include "filesystem/Filesystem.h"
#include <unordered_map>

CommandParser::CommandParser() {}

void CommandParser::execute(int argc, char *argv[]) {
  if (argc == 1)
    return;

  Filesystem fs;
  Command command = toCommand(argv[1]);

  switch (command) {
  case Command::List:
    fs.list(argv[2]);
    break;
  case Command::Delete:
    fs.deleteFile(argv[2]);
    break;
  case Command::NotFound:
    return;
  }
}

Command CommandParser::toCommand(const std::string &s) {
  static const std::unordered_map<std::string, Command> commands = {
      {"list", Command::List},
      {"delete", Command::Delete},
  };
  auto it = commands.find(s);
  return it != commands.end() ? it->second : Command::NotFound;
};
