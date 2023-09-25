#include "../inc/datastructure/customlist.h"
#include "../inc/datastructure/customstring.h"
#include "../inc/file/fileoperation.h"
#include "../inc/interface/interface.h"
#include <iostream>
#include <unistd.h>

custom::list<custom::string> page;

int main(int argc, char *argv[]) {
  using custom::OpenFile, custom::CreateFile, custom::OverwriteFile;
  using interface::Welcome, interface::Help;

  int o;
  char *optstring = "o:h";

  if (argc == 1) {
    Welcome();
  } else {
    while ((o = getopt(argc, argv, optstring)) != -1) {
      switch (o) {
      case 'h':
        Help();
        break;
      case 'o':
        // OpenFile(page, optarg);
      default:
        std::cout << "Invalid option:" << o << std::endl;
      }
    }
  }

  return 0;
}
