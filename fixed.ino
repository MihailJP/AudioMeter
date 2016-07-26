#include "fixed.h"
#include <utility>

#define PREC 12

/* Construstors */

Fixed::Fixed() {myVal = 0;}
Fixed::Fixed(int val) {myVal = (long)val << PREC;}
Fixed::Fixed(short val) {myVal = (long)val << PREC;}
Fixed::Fixed(long val) {myVal = val << PREC;}
Fixed::Fixed(long long val) {myVal = val << PREC;}
Fixed::Fixed(float val) {myVal = val * (1 << PREC);}
Fixed::Fixed(double val) {myVal = val * (1 << PREC);}
Fixed::Fixed(const Fixed& val) {myVal = val.myVal;}
Fixed::Fixed(Fixed&& val) noexcept {myVal = val.myVal;}
Fixed& Fixed::operator = (const Fixed& val) {myVal = val.myVal;}

/* Cast */
Fixed::operator int() const {return (int)(myVal >> PREC);}
Fixed::operator short() const {return (short)(myVal >> PREC);}
Fixed::operator long() const {return (long)(myVal >> PREC);}
Fixed::operator long long() const {return (long long)(myVal >> PREC);}
Fixed::operator float() const {return (float)myVal / (1 << PREC);}
Fixed::operator double() const {return (double)myVal / (1 << PREC);}
Fixed::operator bool() const {return (bool)myVal;}

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
  tmpVal.myVal = (((long long)myVal << (PREC * 2)) / (long long)val.myVal) >> PREC;
  return std::move(tmpVal);
}

Fixed& Fixed::operator += (const Fixed& val) {
  myVal += val.myVal;
  return *this;
}
Fixed& Fixed::operator -= (const Fixed& val) {
  myVal -= val.myVal;
  return *this;
}
Fixed& Fixed::operator *= (const Fixed& val) {
  myVal = ((long long)myVal * (long long)val.myVal) >> PREC;
  return *this;
}
Fixed& Fixed::operator /= (const Fixed& val) {
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
