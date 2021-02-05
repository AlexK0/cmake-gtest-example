// main.cpp

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "sequence-produce-iterator.h"
#include "shuffle-access-iterator.h"

//void case1() {
//  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//  std::vector<int> target(20, 0);
//
//  for (auto i: target) {
//    std::cout << i << ", ";
//  }
//  std::cout << std::endl;
//
//  ShuffleAccessIterator it{target};
//  std::copy(v.begin(), v.end(), it);
//
//
//  for (auto i: target) {
//    std::cout << i << ", ";
//  }
//  std::cout << std::endl;
//}
//
//void case2() {
//  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//  std::vector<int> target(20, 0);
//
//  for (auto i: target) {
//    std::cout << i << ", ";
//  }
//  std::cout << std::endl;
//
//  ShuffleAccessIterator it{target};
//  for (int i = 0; i < 20; ++i) {
//    *it = i;
//  }
//
//  for (auto i: target) {
//    std::cout << i << ", ";
//  }
//  std::cout << std::endl;
//}
//
//void case3() {
//  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//
//  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//  std::cout << std::endl;
//}
//
//void case4() {
//  std::vector<int> v{SequenceProduceIterator<int>{1, 10, 10}, SequenceProduceIterator<int>{}};
//
//  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//  std::cout << std::endl;
//}
//
//void case5() {
//  std::copy(SequenceProduceIterator<double>{0.2, 0.3, 10},
//            SequenceProduceIterator<double>{},
//            std::ostream_iterator<double>(std::cout, " "));
//  std::cout << std::endl;
//}
//
//void case6() {
//  std::vector<std::string> target(5, "");
//
//  std::copy(SequenceProduceIterator<std::string>{"a", "+x", 10},
//            SequenceProduceIterator<std::string>{},
//            ShuffleAccessIterator{target});
//
//  std::copy(target.begin(), target.end(), std::ostream_iterator<std::string>(std::cout, " "));
//  std::cout << std::endl;
//}
//
//void case7() {
//  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//
//  std::copy(ShuffleAccessIterator<int>(v), ShuffleAccessIterator<int>(v, 0),
//            std::ostream_iterator<int>(std::cout, " "));
//  std::cout << std::endl;
//
//  std::copy(ShuffleAccessIterator<int>(v, 20), ShuffleAccessIterator<int>(v, 0),
//            std::ostream_iterator<int>(std::cout, " "));
//  std::cout << std::endl;
//}

void case8() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i : ShuffleAccessRange(v)) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
}

void case9() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  ShuffleAccessRange shuffle_range{v};

  for (int i : shuffle_range) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;

  for (int i : shuffle_range) {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
}

void case10() {
  std::vector<std::pair<std::string, int>> v{{"Alex",   1},
                                             {"Bob",    2},
                                             {"Jessie", 3},
                                             {"Don",    4}};
  for (auto &i : ShuffleAccessRange{v, 2}) {
    i.second *= 10;
  }

  for (const auto &i : v) {
    std::cout << "[" << i.first << ": " << i.second << "], ";
  }
  std::cout << std::endl;
}

void case11() {
  std::vector<std::pair<std::string, int>> v{{"Alex",   1},
                                             {"Bob",    2},
                                             {"Jessie", 3},
                                             {"Don",    4}};
  ShuffleAccessRange shuffle_range{v, 2};
  for (auto it = shuffle_range.begin(); it != shuffle_range.end(); ++it) {
    it->second *= 10;
  }

  for (const auto &i : v) {
    std::cout << "[" << i.first << ": " << i.second << "], ";
  }
  std::cout << std::endl;
}

void case12() {
  std::vector<std::string> v{"Liam", "Olivia",
                             "Noah", "Emma",
                             "Oliver", "Ava",
                             "William", "Sophia",
                             "Elijah", "Isabella",
                             "James", "Charlotte",
                             "Benjamin", "Amelia",
                             "Lucas", "Mia",
                             "Mason", "Harper"};

  ShuffleAccessRange shuffle_range{v, 3};
  std::fill(shuffle_range.begin(), shuffle_range.end(), "DELETED");

  std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, ", "));
  std::cout << std::endl;
}

void case13() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  ShuffleAccessRange shuffle_range{v, 4};
  std::cout << std::accumulate(shuffle_range.begin(), shuffle_range.end(), int{0}) << std::endl;
}

void case14() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  ShuffleAccessRange shuffle_range{v, 7};

  for (auto it = shuffle_range.begin(); it != shuffle_range.end(); ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  for (auto it = shuffle_range.end(); it != shuffle_range.begin();) {
    std::cout << *--it << ", ";
  }
  std::cout << std::endl;
}

void case15() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  ShuffleAccessRange shuffle_range{v};

  for (auto it = shuffle_range.begin(); it != shuffle_range.end(); ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  for (auto it = shuffle_range.rbegin(); it != shuffle_range.rend(); ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
}

void case16() {
  std::vector<int> v{SequenceProduceIterator<int>(1, 1, 1000), SequenceProduceIterator<int>()};
  ShuffleAccessRange shuffle_range{v, 3};

  do {
    std::copy(shuffle_range.begin(), shuffle_range.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
  } while(std::next_permutation(shuffle_range.begin(), shuffle_range.end()));
}


void case17() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ShuffleAccessRange shuffle_range{v};

  auto first = std::next(shuffle_range.begin(), 2);
  auto last = std::prev(shuffle_range.end(), 3);
  std::copy(first, last, std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
}


int main(int argc, char *argv[]) {
  int case_id = 0;
  if (argc > 1) {
    case_id = std::atoi(argv[1]);
  }

  switch (case_id) {
//    case 1:
//      case1();
//      break;
//    case 2:
//      case2();
//      break;
//    case 3:
//      case3();
//      break;
//    case 4:
//      case4();
//      break;
//    case 5:
//      case5();
//      break;
//    case 6:
//      case6();
//      break;
//    case 7:
//      case7();
//      break;
    case 8:
      case8();
      break;
    case 9:
      case9();
      break;
    case 10:
      case10();
      break;
    case 11:
      case11();
      break;
    case 12:
      case12();
      break;
    case 13:
      case13();
      break;
    case 14:
      case14();
      break;
    case 15:
      case15();
      break;
    case 16:
      case16();
      break;
    case 17:
      case17();
      break;
    default:
      std::cout << "Please choose the correct case!" << std::endl;
  }
  return 0;
}


