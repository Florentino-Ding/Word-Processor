//
// Created by 丁麓然 on 9/22/23.
//

#include "../../inc/interface/interface.h"
#include "../../inc/datastructure/customlist.h"
#include "../../inc/datastructure/customstring.h"
#include <iomanip>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

extern custom::list<custom::string> page;

namespace interface {

void Welcome() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int terminalWidth = size.ws_col;
  int terminalHeight = size.ws_row;

  std::cout << "\033[2J\033[H"; // Clear terminal content

  for (int i = 0; i < (terminalHeight - 2) / 2; i++) {
    std::cout << std::endl;
  }

  std::cout << std::setw((terminalWidth - 36) / 2) << ""
            << "Welcome to use Florentino's word editor!" << std::endl;
  std::cout << std::setw((terminalWidth - 30) / 2) << ""
            << "Press \"h\" to get help." << std::endl;
  std::cout << std::setw((terminalWidth - 30) / 2) << ""
            << "Press \"c\" to create a new file." << std::endl;
  std::cout << std::setw((terminalWidth - 30) / 2) << ""
            << "Press \"q\" to quit." << std::endl;

  for (int i = 0; i < (terminalHeight - 2) / 2; i++) {
    std::cout << std::endl;
  }
}

void Help() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int terminalWidth = size.ws_col;
  int terminalHeight = size.ws_row;

  std::cout << "\033[2J\033[H"; // Clear terminal content

  for (int i = 0; i < (terminalHeight - 5) / 2; i++) {
    std::cout << std::endl;
  }

  std::cout << std::setw((terminalWidth - 4) / 2) << ""
            << "help: get help" << std::endl;
  std::cout << std::setw((terminalWidth - 10) / 2) << ""
            << "open: open a file" << std::endl;
  std::cout << std::setw((terminalWidth - 12) / 2) << ""
            << "create: create a file" << std::endl;
  std::cout << std::setw((terminalWidth - 10) / 2) << ""
            << "save: save the file" << std::endl;
  std::cout << std::setw((terminalWidth - 12) / 2) << ""
            << "exit: exit the program" << std::endl;

  for (int i = 0; i < (terminalHeight - 5) / 2; i++) {
    std::cout << std::endl;
  }
}

char GetUserInput() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int terminalWidth = size.ws_col;
  int terminalHeight = size.ws_row;

  char userInput;

  while (userInput != 'h' and userInput != 'c' and userInput != 'q') {
    std::cout << "\033[2J\033[H"; // Clear terminal content

    for (int i = 0; i < (terminalHeight - 3) / 2; i++) {
      std::cout << std::endl;
    }

    std::cin >> userInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      break;
    }
  }

  switch (userInput) {
  case 'h':
    Help();
    break;
  case 'c':
    // CreateFile(page);
    break;
  case 'q':
    exit(0);
  }

  return userInput;
}

void ShowPage(const custom::list<custom::string> &page) {
  std::wcout << page << std::endl;
}
} // namespace interface
