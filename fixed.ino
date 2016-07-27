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
