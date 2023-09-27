#include "../../inc/datastructure/customlist.h"
#include "../../inc/datastructure/customstring.h"
#include "../../inc/file/fileoperation.h"
#include "../../inc/interface/interface.h"
#include <fstream>

namespace custom {
void OpenFile(list<list<string>> &page, const string &path) {
  std::ifstream file(path);
  if (!file) {
    std::cout << "File not found." << std::endl;
    return;
  }
  string line;
  // while (std::getline(file, line)) {
  //   list<string> line_list;
  //   for (int i = 0; i < line.length(); i++) {
  //     line_list.push_back(line[i]);
  //   }
  //   page.push_back(line_list);
  // }
  file.close();
}
void CreateFile(const string &path) {
  std::ofstream file(path);
  file.close();
}
void OverwriteFile(const list<list<string>> &page, const string &path) {}
} // namespace custom