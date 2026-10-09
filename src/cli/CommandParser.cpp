#include "CommandParser.h"
#include "filesystem/Filesystem.h"
#include <iostream>
#include <unordered_map>

CommandParser::CommandParser() {}

void CommandParser::execute(int argc, char *argv[]) {
  if (argc == 1)
    return;
  std::cout << "argc: " << argc << "\n";

  Filesystem fs;
  Command command = toCommand(argv[1]);

  switch (command) {
  case Command::List:
    if (argc > 2)
      fs.list(argv[2]);
    break;
  case Command::Delete:
    if (argc > 2)
      fs.deleteFile(argv[2]);
    break;
  case Command::Search:
    if (argc > 3)
      fs.search(argv[2], argv[3]);
    break;
  case Command::Copy:
    if (argc > 3)
      fs.copy(argv[2], argv[3]);
    break;
  case Command::Move:
    if (argc > 3)
      fs.move(argv[2], argv[3]);
    break;
  case Command::NotFound:
    return;
  }
}

Command CommandParser::toCommand(const std::string &s) {
  static const std::unordered_map<std::string, Command> commands = {
      {"list", Command::List},     {"delete", Command::Delete},
      {"search", Command::Search}, {"copy", Command::Copy},
      {"move", Command::Move},
  };
  auto it = commands.find(s);
  return it != commands.end() ? it->second : Command::NotFound;
};
