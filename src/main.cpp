// main.cpp

#include <iostream>
#include <vector>
#include <iterator>

#include "shuffle-access-iterator.h"

void case1() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
  std::vector<int> target(20, 0);

  for (auto i: target) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  ShuffleAccessIterator it{target};
  std::copy(v.begin(), v.end(), it);


  for (auto i: target) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
}

void case2() {
  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
  std::vector<int> target(20, 0);

  for (auto i: target) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  ShuffleAccessIterator it{target};
  for (int i = 0; i < 20; ++i) {
    *it = i;
  }

  for (auto i: target) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
}

void case3() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
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
    default:
      std::cout << "Please choose the correct case!" << std::endl;
  }
  return 0;
}


