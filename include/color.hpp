#pragma once

#include <string>

class Color
{
public:
	Color(char value = 0) : value_(value & 0x1f) {}
	Color(const std::string &text);

	Color &operator +=(const Color &color) { value_ |= color.value_; return *this; }
	Color &operator -=(const Color &color) { value_ &= ~color.value_; return *this; }

	bool operator ==(const Color &color) const { return value_ == color.value_; }
	bool operator <=(const Color &color) const { return (value_ & color.value_) == value_; }

	operator char() const { return value_; }
	operator std::string() const;

private:
	char value_;

	mutable std::string desc_;
};

Color operator +(const Color &a, const Color &b);
Color operator -(const Color &a, const Color &b);

inline bool operator !=(const Color &a, const Color &b) { return !(a == b); }
inline bool operator >=(const Color &a, const Color &b) { return b <= a; }
inline bool operator <(const Color &a, const Color &b) { return !(b <= a); }
inline bool operator >(const Color &a, const Color &b) { return !(a <= b); }
