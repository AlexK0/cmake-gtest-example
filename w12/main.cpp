#include <iostream>
#include <iomanip>
#include <string_view>

template<class T>
std::ostream &dump_to(const T &obj, std::ostream &out) {
  size_t obj_size = sizeof(T);
  size_t obj_align = alignof(T);

  out << "---------------------------" << std::endl
      << "Object size: " << obj_size << ", align: " << obj_align << std::endl;
  auto *p = reinterpret_cast<const uint8_t *>(&obj);
  for (size_t i = 0; i != obj_size;) {
    out << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(p[i]);
    if (++i % obj_align == 0) {
      out << std::endl;
    } else {
      out << " ";
    }
  }
  return out << "---------------------------" << std::dec;
}

namespace case1 {

struct Demo1 {
  uint8_t x1{0xa1};
  uint8_t x2{0xa2};
  uint8_t x3{0xa3};
};

struct Demo2 {
  uint8_t x1{0xa1};
  uint32_t y1{0xb1b2b3b4};
  uint8_t x2{0xa2};
  uint8_t x3{0xa3};
  uint32_t y2{0xc1c2c3c4};
  uint16_t z1{0xd1d2};
  uint64_t w1{0xf1f2f3f4f5f6f7f8};
};

}

namespace case2 {
struct Demo1 {
  uint8_t x0{0x01};
};

struct Demo2 {
  uint32_t x1{0x11121314};
  uint8_t x2{0x21};
};

struct Demo3 {
  uint16_t x3{0x3132};
  uint16_t x4{0x4142};
};

struct Demo {
  Demo1 d1;
  Demo2 d2;
  Demo3 d3;
};

struct Demo_ {
  uint8_t x0{0x01};
  uint32_t x1{0x11121314};
  uint8_t x2{0x21};
  uint16_t x3{0x3132};
  uint64_t x4{0x4142434445464748};
};
}

namespace case3 {

struct Demo2 {
  uint8_t x0{0x01};
  uint32_t x1{0x11121314};
};

struct Demo {
  Demo2 d[3];
};

struct Demo_ {
  Demo2 d1;
  Demo2 d2;
  Demo2 d3;
};

}

namespace case4 {

struct String_ {
  const char *string_ptr;
  size_t string_size;
  union {
    size_t string_capacity;
    char string_sso[16];
  };
};

size_t get_string_size(const std::string &s) {
  return reinterpret_cast<const String_ *>(&s)->string_size;
}

}

namespace case5 {
struct Demo {
};

struct Demo1 {
  Demo d1[7];
};
}

namespace case6 {
struct Demo1 {
  uint8_t x0{0x01};
};

struct Demo2 : Demo1 {
  uint32_t x1{0x11121314};
  uint8_t x2{0x21};
};

struct Demo3 : Demo2 {
  uint16_t x3{0x3132};
  uint16_t x4{0x4142};
};

struct Demo4 : Demo3 {
  uint64_t x5{0x5152535455565758};
};

struct Demo4_ {
  uint8_t x0{0x01};
  uint32_t x1{0x11121314};
  uint8_t x2{0x21};
  uint16_t x3{0x3132};
  uint16_t x4{0x4142};
  uint64_t x5{0x5152535455565758};
};

struct Demo4__ {
  Demo1 d1;
  Demo2 d2;
  Demo3 d3;
  uint64_t x5{0x5152535455565758};
};

struct Demo3_ {
  Demo2 d2;
  uint16_t x3{0x3132};
  uint16_t x4{0x4142};
};

}

namespace case7 {
struct Demo1 {
  uint8_t x0{0xa1};
};

struct Demo2 {
  uint32_t x1{0x11121314};
  uint8_t x2{0x21};
};

struct Demo3 {
  uint16_t x3{0x3132};
  uint32_t x4{0x4142};
};

struct Demo4 : Demo1, Demo2, Demo3 {
  uint64_t x5{0x5152535455565758};
};

}

namespace case8 {

struct Demo1 {
  uint8_t x0{0x01};
};

struct Demo2 : Demo1 {
  uint32_t x1{0x11121314};
  uint8_t x2{0x21};
};

struct Demo3 : Demo2 {
  uint16_t x3{0x3132};
  uint32_t x4{0x4142};
};

struct Demo4 : Demo3 {
  uint64_t x5{0x5152535455565758};
};

}

namespace case9 {

struct Demo1 {
  uint16_t x0{0x0102};
};

struct Demo2 : virtual Demo1 {
  uint32_t x1{0x11121314};
  uint8_t x2{0x21};
};

struct Demo3 : virtual Demo1 {
  uint32_t x3{0x31323334};
  uint8_t x4{0x41};
};

struct Demo4 : Demo2, Demo3 {
  uint64_t x5{0x5152535455565758};
};
}

namespace case10 {

struct Demo {
};

struct Demo1 : Demo {
  int32_t x{0x12345678};
};

}

namespace case11 {

struct Demo {
  void dump_me_to(std::ostream &out) const {
    out << this->x << std::endl;
  }

  uint32_t x{0x1234};
};

void Demo_dump_me_to(const Demo *this_, std::ostream &out) {
  out << this_->x << std::endl;
}

}

int main() {
  dump_to(case11::Demo{}, std::cout) << std::endl;
  case11::Demo d{};
  d.dump_me_to(std::cout);
  // ||
  Demo_dump_me_to(&d, std::cout);
  return 0;
}
