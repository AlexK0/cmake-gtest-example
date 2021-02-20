// main.cpp

#include "observed-string.h"

#include <iostream>

void case1() {
  {
    ObservedString s1{"hello"};
    ObservedString s2{"world"};
    ObservedString s3{"hello"};
    std::cout << "In scope:" << std::endl << ObservedString::get_observer() << std::endl;
  }
  std::cout << "Out of scope:" << std::endl << ObservedString::get_observer();
}

int main(int argc, char *argv[]) {
  int case_id = 0;
  if (argc > 1) {
    case_id = std::atoi(argv[1]);
  }

  switch (case_id) {
    case 1:
      case1();
      break;
    default:
      std::cout << "Please choose the correct case!" << std::endl;
  }
  return 0;
}

