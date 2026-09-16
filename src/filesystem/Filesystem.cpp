#include "Filesystem.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Filesystem::Filesystem() {}

void Filesystem::list(std::string path) {
  for (const auto &input : fs::directory_iterator(path)) {
    std::cout << input.path() << std::endl;
  }
}
