#pragma once

/* Fixed point decimal class, 16 + 16 bits */

class Fixed {
private:
  bool valid;
  long myVal;
public: // constructors
  Fixed();
  Fixed(int);
  Fixed(short);
  Fixed(long);
  Fixed(long long);
  Fixed(float);
  Fixed(double);
  Fixed(const Fixed&);
  Fixed(Fixed&&) noexcept;
  Fixed& operator = (const Fixed&);
public: // cast
  operator int() const;
  operator short() const;
  operator long() const;
  operator long long() const;
  operator float() const;
  operator double() const;
  operator bool() const;
public: // attribute
  bool isValid() const;
public: // arithmetic operators
  const Fixed operator + (const Fixed&) const;
  const Fixed operator - (const Fixed&) const;
  const Fixed operator * (const Fixed&) const;
  const Fixed operator / (const Fixed&) const;
  Fixed& operator += (const Fixed&);
  Fixed& operator -= (const Fixed&);
  Fixed& operator *= (const Fixed&);
  Fixed& operator /= (const Fixed&);
  const Fixed operator + () const;
  const Fixed operator - () const;
  inline const Fixed operator + (const int val) const {return *this + Fixed(val);}
  inline const Fixed operator - (const int val) const {return *this - Fixed(val);}
  inline const Fixed operator * (const int val) const {return *this * Fixed(val);}
  inline const Fixed operator / (const int val) const {return *this / Fixed(val);}
  inline Fixed& operator += (const int val) {return *this += Fixed(val);}
  inline Fixed& operator -= (const int val) {return *this -= Fixed(val);}
  inline Fixed& operator *= (const int val) {return *this *= Fixed(val);}
  inline Fixed& operator /= (const int val) {return *this /= Fixed(val);}
public: // comparison
  bool operator == (const Fixed&) const;
  bool operator != (const Fixed&) const;
  bool operator < (const Fixed&) const;
  bool operator > (const Fixed&) const;
  bool operator <= (const Fixed&) const;
  bool operator >= (const Fixed&) const;
  inline bool operator == (const int val) const {return *this == Fixed(val);}
  inline bool operator != (const int val) const {return *this != Fixed(val);}
  inline bool operator < (const int val) const {return *this < Fixed(val);}
  inline bool operator > (const int val) const {return *this > Fixed(val);}
  inline bool operator <= (const int val) const {return *this <= Fixed(val);}
  inline bool operator >= (const int val) const {return *this >= Fixed(val);}
};
