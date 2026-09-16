#pragma once

#include <string>

class Filesystem {
public:
  Filesystem();
  void list(std::string path);
  std::string search();
  void copy();
  void move();
  std::string deletePath();
  std::string help();
};
