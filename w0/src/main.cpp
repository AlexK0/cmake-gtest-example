// main.cpp

#include "observed-string.h"
#include "rational.h"

#include <iostream>
#include <vector>

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

void case6() {
  {
    ObservedString s1{"hello"};
    ObservedString s2{"world"};

    std::vector<ObservedString> v;
    v.push_back(s1 + s2);
    std::cout << "In scope:" << std::endl << ObservedString::get_observer() << std::endl;
  }
  std::cout << "Out of scope:" << std::endl << ObservedString::get_observer();
}

void case7() {
  {
    ObservedString s1{"hello"};
    ObservedString s2{"world"};
    ObservedString s3{"xyz"};

    s3 = s1 + s2;
    std::cout << "In scope:" << std::endl << ObservedString::get_observer() << std::endl;
  }
  std::cout << "Out of scope:" << std::endl << ObservedString::get_observer();
}

void case8() {
  {
    ObservedString s1{"hello"};
    ObservedString s2{"world"};
    ObservedString s3 = s1 + s2;
    ObservedString s4 = s3;
  }

  std::cout << std::endl << ObservedString::get_observer();
}

ObservedString some_fun2() {
  ObservedString s{"hello"};
  return s;
};

const ObservedString &some_fun1(const ObservedString &s) {
  std::cout << "in some_fun1!" << std::endl;
  return s;
}

const ObservedString &some_fun3(const ObservedString &s) {
  std::cout << "in some_fun3!" << std::endl;
  return s;
}

void case9() {
  const ObservedString &s1 = some_fun3(some_fun1(some_fun2()));
  ObservedString s2{"world"};
  std::cout << std::endl << ObservedString::get_observer();
}


ObservedString some_fun10() {
  ObservedString s{"hello"};
  return s;
};

void case10(bool x) {
  static ObservedString default_world{"default world"};
  const ObservedString &s1 = x ? static_cast<const ObservedString &>(some_fun10()) : default_world;

  std::cout << std::endl << ObservedString::get_observer();
}

ObservedString some_fun11_1() {
  ObservedString s{"some_fun11_1"};
  return s;
};

ObservedString some_fun11_2() {
  ObservedString s{"some_fun11_2"};
  return s;
};

void case11() {
  ObservedString s = some_fun11_1() + some_fun11_2();
}

void case12() {
  Rational x{1, 5};
  Rational y{2};
  Rational z = x * y;

  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;
  std::cout << "z: " << z << std::endl;
}

Rational make_rational(int numerator) {
  std::cout << "make_rational(" << numerator << ")" << std::endl;
  return Rational{numerator};
}

void case13() {
  if (make_rational(1) || make_rational(2)) {
    std::cout << "in if" << std::endl;
  } else {
    std::cout << "in else" << std::endl;
  }
}

void case14() {
  std::vector<int> x{5, 10}; // 5 10
  std::vector<int> y(5, 10); // 10 10 10 10 10

  std::cout << x.size() << std::endl << y.size() << std::endl;
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
    case 7:
      case7();
      break;
    case 8:
      case8();
      break;
    case 9:
      case9();
      break;
    case 10:
      case10(true);
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
    default:
      std::cout << "Please choose the correct case!" << std::endl;
  }
  return 0;
}

