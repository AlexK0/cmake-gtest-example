#pragma once

#include <numeric>


class Rational {
public:
  explicit Rational(int numerator = 0, int denominator = 1)
          : numerator_(numerator), denominator_(denominator) {
    Normalize();
  }

  int Numerator() const {
    return numerator_;
  }

  int Denominator() const {
    return denominator_;
  }

  friend std::ostream& operator<<(std::ostream& output, Rational self) {
    return output << self.numerator_ << '/' << self.denominator_;
  }

  friend Rational operator*(Rational &lhs, Rational rhs) {
    lhs.numerator_ *= rhs.numerator_;
    lhs.denominator_ *= rhs.denominator_;
    return lhs;
  }

  bool operator!() const noexcept {
    return numerator_ == 0;
  }

  friend bool operator||(Rational lhs, Rational rhs) noexcept {
    return lhs.numerator_ || rhs.numerator_;
  }

private:
  void Normalize() {
    if (denominator_ < 0) {
      numerator_ = -numerator_;
      denominator_ = -denominator_;
    }
    int n = std::gcd(numerator_, denominator_);
    numerator_ /= n;
    denominator_ /= n;
  }

  int numerator_ = 0;
  int denominator_ = 1;
};
