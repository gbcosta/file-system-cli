#include "Filesystem.h"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;
using namespace std;

Filesystem::Filesystem() {}

void Filesystem::list(fs::path path) {
  for (const auto &input : fs::directory_iterator(path)) {
    cout << input.path() << std::endl;
  }
}

void Filesystem::deleteFile(fs::path path) {
  if (fs::is_regular_file(path)) {
    fs::remove(path);
    return;
  }

  if (fs::is_directory(path)) {
    fs::remove_all(path);
  }
}

void Filesystem::search(fs::path path, fs::path searchStr) {
  if (!fs::is_directory(path) || searchStr.string().size() == 0) {
    return;
  }

  fs::path inputFileName;
  for (const auto &input : fs::recursive_directory_iterator(path)) {
    fs::path inputFileName = input.path().string();

    if (inputFileName.filename().string().find(searchStr) !=
        std::string::npos) {
      cout << input.path() << "\n";
    }
  }
}

void Filesystem::copy(fs::path path, fs::path pastePath) {
  cout << path << "\n";
  cout << pastePath << "\n";

  if (!fs::is_directory(pastePath) || !fs::is_directory(path) ||
      !fs::is_regular_file(path))
    return;

  if (fs::is_directory(path)) {
    fs::copy(path, pastePath, fs::copy_options::recursive);
    cout << "copy directory" << "\n";
    return;
  }

  if (fs::is_regular_file(path)) {
    fs::copy(path, pastePath);
    return;
  }
}
