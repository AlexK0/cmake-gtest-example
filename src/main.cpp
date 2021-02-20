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

void case2() {
  {
    ObservedString s1{"hello"};
    ObservedString s2 = s1;
    std::cout << "In scope:" << std::endl << ObservedString::get_observer() << std::endl;
  }
  std::cout << "Out of scope:" << std::endl << ObservedString::get_observer();
}

void case3() {
  {
    ObservedString s1{"hello"};
    ObservedString s2{"world"};
    s2 = s1;
    std::cout << "In scope:" << std::endl << ObservedString::get_observer() << std::endl;
  }
  std::cout << "Out of scope:" << std::endl << ObservedString::get_observer();
}

void case4() {
  {
    ObservedString s1{"hello"};
    ObservedString s2{"world"};
    s2 += s1;
    std::cout << "In scope:" << std::endl << ObservedString::get_observer() << std::endl;
  }
  std::cout << "Out of scope:" << std::endl << ObservedString::get_observer();
}

void case5() {
  {
    ObservedString s1{"hello"};
    ObservedString s2{"world"};
    ObservedString s3 = s1 + s2;
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
    case 2:
      case2();
      break;
    case 3:
      case3();
      break;
    case 4:
      case4();
      break;
    case 5:
      case5();
      break;
    default:
      std::cout << "Please choose the correct case!" << std::endl;
  }
  return 0;
}

