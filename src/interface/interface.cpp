//
// Created by 丁麓然 on 9/22/23.
//

#include "../../inc/interface/interface.h"
#include "../../inc/datastructure/customlist.h"
#include "../../inc/datastructure/customstring.h"

namespace interface {
void Welcome() {
  std::cout << "Welcome to use String Operation!" << std::endl;
  std::cout << "Please input \"help\" to get help." << std::endl;
}
void Help() {
  std::cout << "help: get help" << std::endl;
  std::cout << "open: open a file" << std::endl;
  std::cout << "create: create a file" << std::endl;
  std::cout << "save: save the file" << std::endl;
  std::cout << "exit: exit the program" << std::endl;
}
void ShowPage(const custom::list<custom::string> &page) {
  std::cout << "The file is:" << std::endl;
}
} // namespace interface

// extern custom::list<custom::string> page;
