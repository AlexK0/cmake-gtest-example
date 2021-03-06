// main.cpp

#include <iostream>
#include <vector>
#include <iterator>

#include "sequence-produce-iterator.h"
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

void case4() {
  std::vector<int> v{SequenceProduceIterator<int>{1, 10, 10}, SequenceProduceIterator<int>{}};

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

void case5() {
  std::copy(SequenceProduceIterator<double>{0.2, 0.3, 10},
            SequenceProduceIterator<double>{},
            std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;
}

void case6() {
  std::vector<std::string> target(5, "");

  std::copy(SequenceProduceIterator<std::string>{"a", "+x", 10},
            SequenceProduceIterator<std::string>{},
            ShuffleAccessIterator{target});

  std::copy(target.begin(), target.end(), std::ostream_iterator<std::string>(std::cout, " "));
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
    case 4:
      case4();
      break;
    case 5:
      case5();
      break;
    case 6:
      case6();
      break;
    default:
      std::cout << "Please choose the correct case!" << std::endl;
  }
  return 0;
}


