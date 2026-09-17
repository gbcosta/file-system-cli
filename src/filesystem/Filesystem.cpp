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

void Filesystem::deleteFile(std::string path) {
  if (fs::is_regular_file(path)) {
    fs::remove(path);
    return;
  }

  if (fs::is_directory(path)) {
    fs::remove_all(path);
  }
}

void Filesystem::search(std::string path, std::string strToSearch) {
  if (!fs::is_directory(path) || strToSearch.size() == 0)
    return;

  for (const auto &input : fs::recursive_directory_iterator(path)) {
    std::string inputString = input.path().string();
    const size_t lastSlashPos = inputString.find_last_of("/");
    std::string lastPart = (lastSlashPos != std::string::npos)
                               ? inputString.substr(lastSlashPos + 1)
                               : "";

    if (lastPart.find(strToSearch) != std::string::npos &&
        fs::is_regular_file(input)) {
      std::cout << input.path() << "\n";
    }
  }
}
