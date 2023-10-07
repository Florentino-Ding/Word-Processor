#include "../inc/backend/backend.h"
#include "../inc/basic.h"
#include "../inc/datastructure/customlist.h"
#include "../inc/datastructure/customstring.h"
#include "../inc/frontend/frontend.h"
#include <cstdlib>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

Page page;
MODE mode = PLAIN_MODE;

int main(int argc, char *argv[]) {
  using custom::list, custom::string;
  using custom::OpenFile, custom::SaveFile;
  using interface::Welcome, interface::Help, interface::ShowPage, interface::SwitchInterface, interface::GetUserInput;
  using std::wcout, std::endl;

  int o;
  char optstring[] = "ho:";

  struct winsize size;
  size.ws_col = 80; // 设置终端列数
  size.ws_row = 24; // 设置终端行数

  if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &size) == -1) {
    std::cerr << "Failed to set terminal size." << std::endl;
    return 1;
  }

  if (argc == 1) {
    Welcome();
  } else {
    while ((o = getopt(argc, argv, optstring)) != -1) {
      switch (o) {
      case 'h':
        Help();
        break;
      case 'o':
        OpenFile(optarg);
        ShowPage();
        break;
      case '?':
        wcout << L"Unknown option: " << (char)optopt << endl;
        exit(-1);
      }
      SwitchInterface(GetUserInput());
    }
  }

  return 0;
}
