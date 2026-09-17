#pragma once

#include <string>

class Filesystem {
public:
  Filesystem();
  void list(std::string path);
  void search(std::string path, std::string strToSearch);
  void copy();
  void move();
  void deleteFile(std::string path);
  void help();
};
