#pragma once

#include <string>

enum class Command { List, Delete, Search, NotFound };

class CommandParser {
public:
  CommandParser();
  void execute(int argc, char *argv[]);

private:
  Command toCommand(const std::string &s);
};
