#pragma once

#include <filesystem>

namespace fs = std::filesystem;

class Filesystem {
public:
  Filesystem();
  void list(fs::path path);
  void search(fs::path path, fs::path searchStr);
  void copy(fs::path path, fs::path pastePath);
  void move();
  void deleteFile(fs::path path);
  void help();
};
