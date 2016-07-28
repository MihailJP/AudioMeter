#include "fixed.h"
#include <utility>
#include <cmath>

#define PREC 12

/* Construstors */

Fixed::Fixed() {myVal = 0; valid = true;}
Fixed::Fixed(int val) {myVal = (long)val << PREC; valid = true;}
Fixed::Fixed(short val) {myVal = (long)val << PREC; valid = true;}
Fixed::Fixed(long val) {myVal = val << PREC; valid = true;}
Fixed::Fixed(long long val) {myVal = val << PREC; valid = true;}
Fixed::Fixed(float val) {myVal = val * (1 << PREC); valid = true;}
Fixed::Fixed(double val) {myVal = val * (1 << PREC); valid = true;}
Fixed::Fixed(const Fixed& val) {myVal = val.myVal; valid = true;}
Fixed::Fixed(Fixed&& val) noexcept {myVal = val.myVal; valid = val.valid;}
Fixed& Fixed::operator = (const Fixed& val) {myVal = val.myVal; valid = val.valid;}

/* Cast */
Fixed::operator int() const {return valid ? (int)(myVal >> PREC) : 0/0;}
Fixed::operator short() const {return valid ? (short)(myVal >> PREC) : 0/0;}
Fixed::operator long() const {return valid ? (long)(myVal >> PREC) : 0/0;}
Fixed::operator long long() const {return valid ? (long long)(myVal >> PREC) : 0/0;}
Fixed::operator float() const {return valid ? (float)myVal / (1 << PREC) : NAN;}
Fixed::operator double() const {return valid ? (double)myVal / (1 << PREC) : NAN;}
Fixed::operator bool() const {return valid && (bool)myVal;}

/* Attribute */
bool Fixed::isValid() const {
  return valid;
}

/* Arithmetic */

const Fixed Fixed::operator + (const Fixed& val) const {
  Fixed tmpVal;
  tmpVal.myVal = myVal + val.myVal;
  return std::move(tmpVal);
}
const Fixed Fixed::operator - (const Fixed& val) const {
  Fixed tmpVal;
  tmpVal.myVal = myVal - val.myVal;
  return std::move(tmpVal);
}
const Fixed Fixed::operator * (const Fixed& val) const {
  Fixed tmpVal;
  tmpVal.myVal = ((long long)myVal * (long long)val.myVal) >> PREC;
  return std::move(tmpVal);
}
const Fixed Fixed::operator / (const Fixed& val) const {
  Fixed tmpVal;
  tmpVal.valid = valid && val.valid;
  tmpVal.myVal = (((long long)myVal << (PREC * 2)) / (long long)val.myVal) >> PREC;
  return std::move(tmpVal);
}

Fixed& Fixed::operator += (const Fixed& val) {
  valid = valid && val.valid;
  myVal += val.myVal;
  return *this;
}
Fixed& Fixed::operator -= (const Fixed& val) {
  valid = valid && val.valid;
  myVal -= val.myVal;
  return *this;
}
Fixed& Fixed::operator *= (const Fixed& val) {
  myVal = ((long long)myVal * (long long)val.myVal) >> PREC;
  return *this;
}
Fixed& Fixed::operator /= (const Fixed& val) {
  valid = valid && val.valid;
  myVal = (((long long)myVal << (PREC * 2)) / (long long)val.myVal) >> PREC;
  return *this;
}

const Fixed Fixed::operator + () const {
  return *this;
}
const Fixed Fixed::operator - () const {
  return std::move(Fixed(-myVal));
}

/* Comparison */

bool Fixed::operator == (const Fixed& val) const {
  return myVal == val.myVal;
}
bool Fixed::operator != (const Fixed& val) const {
  return myVal != val.myVal;
}
bool Fixed::operator < (const Fixed& val) const {
  return myVal < val.myVal;
}
bool Fixed::operator > (const Fixed& val) const {
  return myVal > val.myVal;
}
bool Fixed::operator <= (const Fixed& val) const {
  return myVal <= val.myVal;
}
bool Fixed::operator >= (const Fixed& val) const {
  return myVal >= val.myVal;
}

/* Function */

unsigned long calc_sqrt(unsigned long val) {
  /* square root, algorithm like Odhner machine (uses hexadecimal rather than decimal) */
  
  unsigned long x = val;
  unsigned long y = 0;
  unsigned long ans = 0;
  
  int basePos = 24;
  int addPos = 24;
  int ansPos = 28;
  
  do {
    for (int i = 1; i < 32; i += 2) {
      if (x >= (y | (i << addPos))) {
        x -= (y | (i << addPos));
        ans += 1 << ansPos;
      } else {
        y += (i - 1) << addPos;
        if (addPos > 0) {
          y >>= 4;
          basePos -= 4;
          addPos -= 8;
        } else {
          x <<= 8;
          y <<= 4;
        }
        ansPos -= 4;
        break;
      }
    }
  } while (ansPos >= 4);

  return ans;
}

const Fixed Fixed::sqrt(const Fixed& val) {
  Fixed ans;
  if (val.myVal < 0) {
    ans.myVal = 0x80000000L; // invalid
  } else {
    unsigned long answer = calc_sqrt((unsigned long)val.myVal);
    answer >>= 16 - (PREC / 2);
    ans.myVal = (long)answer;
  }
  return std::move(ans);
}

const Fixed Fixed::sqrt(long val) {
  Fixed ans;
  if (val < 0) {
    ans.valid = false; // invalid
  } else {
    unsigned long answer = calc_sqrt((unsigned long)val);
    answer >>= 16 - PREC;
    ans.myVal = (long)answer;
  }
  return std::move(ans);
}

const Fixed Fixed::log2(const Fixed& val) {
  Fixed ans;
  if (val.myVal <= 0) {
    ans.myVal = 0x80000000L; // invalid
  } else {
    long long antilog = val.myVal;
    if ((antilog & (-1 << PREC)) == 0) { // less than one
      while ((antilog & (-1 << PREC)) != (1 << PREC)) {
        antilog <<= 1;
        ans.myVal -= 1;
      }
    } else if ((antilog & (-1 << (PREC + 1))) != 0) { // not less than two
      while ((antilog & (-1 << PREC)) != (1 << PREC)) {
        antilog >>= 1;
        ans.myVal += 1;
      }
    }

    for (int i = 0; i < PREC; ++i) {
      antilog *= antilog;
      ans.myVal <<= 1;
      if ((antilog & (-1 << PREC * 2 + 1)) != 0) {
        ans.myVal |= 1;
        antilog >>= 1;
      }
      antilog >>= PREC;
    }
  }
  return std::move(ans);
}

const Fixed Fixed::log10(const Fixed& val) {
  Fixed ans;
  if (val.myVal <= 0) {
    ans.myVal = 0x80000000L; // invalid
  } else {
    static Fixed log2_10 = log2(10);
    ans = log2(val) / log2_10;
  }
  return std::move(ans);
}
