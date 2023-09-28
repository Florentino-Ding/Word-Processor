#include "../../inc/backend/backend.h"
#include "../../inc/basic.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

extern Page page;

namespace custom {
void OpenFile(const char *const path) {
  std::ifstream file;
  try {
    file.open(path);
  } catch (std::ifstream::failure e) {
    std::cerr << "Exception opening/reading file" << std::endl;
    exit(-1);
  }
  if (file) {
    std::string line;
    while (std::getline(file, line)) {
      line += '\n';
      string s(line);
      page += s.split();
    }
    file.close();
  }
}
void OpenFile(const wchar_t *const path) {
  std::ifstream file;
  try {
    file.open(path);
  } catch (std::ifstream::failure e) {
    std::cerr << "Exception opening/reading file" << std::endl;
    exit(-1);
  }
  if (file) {
    std::string line;
    while (std::getline(file, line)) {
      line += '\n';
      string s(line);
      page += s.split();
    }
    file.close();
  }
}

void SaveFile(const wchar_t *const path) {
  std::wofstream file;
  try {
    file.open(path);
  } catch (std::wifstream::failure e) {
    std::cerr << "Exception opening/reading file" << std::endl;
    exit(-1);
  }
  if (file) {
    file << page;
    file.close();
  }
  std::cout << "File saved to: " << path << std::endl;
}
} // namespace custom