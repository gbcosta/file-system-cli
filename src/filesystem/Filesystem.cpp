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

void Filesystem::move(fs::path path, fs::path movePath) {
  std::error_code ec;
  if (!fs::is_directory(path, ec) && !fs::is_regular_file(path, ec))
    return;

  fs::rename(path, movePath, ec);

  if (ec) {
    cerr << "Error: " << ec.message() << "\n";
  }
}

void Filesystem::help() {
  cout << "=== Available Filesystem Commands ===\n\n";

  cout << "list <path>\n"
       << "    Lists all files and folders inside the given directory.\n"
       << "    Example: list /home/user/documents\n\n";

  cout << "deleteFile <path>\n"
       << "    Removes a file or a directory (including all of its contents).\n"
       << "    Warning: directory deletion is recursive and irreversible.\n"
       << "    Example: deleteFile /home/user/temp\n\n";

  cout << "search <path> <text>\n"
       << "    Recursively searches, starting from the given directory, for\n"
       << "    files and folders whose name contains the search text.\n"
       << "    Example: search /home/user report\n\n";

  cout << "copy <source> <destination>\n"
       << "    Copies a file or directory to the given destination.\n"
       << "    Directories are copied recursively; files that already exist\n"
       << "    at the destination are skipped.\n"
       << "    Example: copy /home/user/photo.png /home/user/backup\n\n";

  cout << "move <source> <destination>\n"
       << "    Moves a file or directory to the given destination\n"
       << "    (copies to the destination and removes the original).\n"
       << "    Example: move /home/user/photo.png /home/user/photos\n\n";

  cout << "help\n"
       << "    Displays this list of commands.\n";
}
