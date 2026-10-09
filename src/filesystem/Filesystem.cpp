#include "Filesystem.h"
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;
using namespace std;

Filesystem::Filesystem() {}

void Filesystem::list(fs::path path) {
  std::error_code ec;
  if (!fs::is_directory(path, ec)) {
    cout << "Not a directory: " << path << "\n";
    return;
  }

  fs::directory_iterator it(path, ec);
  fs::directory_iterator end;
  while (!ec && it != end) {
    cout << it->path() << "\n";
    it.increment(ec);
  }

  if (ec) {
    cerr << "Error: " << ec.message() << "\n";
  }
}

void Filesystem::deleteFile(fs::path path) {
  std::error_code ec;

  if (fs::is_regular_file(path, ec)) {
    fs::remove(path, ec);
  } else if (fs::is_directory(path, ec)) {
    fs::remove_all(path, ec);
  } else {
    cout << "Path not found: " << path << "\n";
    return;
  }

  if (ec) {
    cerr << "Error: " << ec.message() << "\n";
  }
}

void Filesystem::search(fs::path path, fs::path searchStr) {
  std::error_code ec;
  if (!fs::is_directory(path, ec) || searchStr.string().size() == 0) {
    return;
  }

  fs::path inputFileName;
  for (const auto &input : fs::recursive_directory_iterator(path, ec)) {
    inputFileName = input.path().string();

    if (inputFileName.filename().string().find(searchStr) !=
        std::string::npos) {
      cout << input.path() << "\n";
    }
  }

  if (ec) {
    cerr << "Error: " << ec.message() << "\n";
  }
}

void Filesystem::copy(fs::path path, fs::path pastePath) {
  std::error_code ec;
  if (!fs::is_directory(path, ec) && !fs::is_regular_file(path, ec))
    return;

  if (fs::is_directory(path, ec)) {
    fs::path finalPath = pastePath / path.filename();

    fs::copy(path, finalPath,
             fs::copy_options::recursive | fs::copy_options::skip_existing, ec);
    return;
  }

  if (fs::is_regular_file(path, ec)) {
    fs::copy(path, pastePath, fs::copy_options::skip_existing, ec);
    return;
  }

  if (ec) {
    cerr << "Error: " << ec.message() << "\n";
  }
}
