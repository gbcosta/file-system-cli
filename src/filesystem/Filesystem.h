#pragma once

#include <string>

class Filesystem {
public:
  Filesystem();
  void list(std::string path);
  std::string search();
  void copy();
  void move();
  void deletePath();
  void deleteFile(std::string path);
  void help();
};
