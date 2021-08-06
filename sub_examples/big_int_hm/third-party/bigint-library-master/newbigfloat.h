#ifndef ___CLASS_NEWBIGFLOAT
#define ___CLASS_NEWBIGFLOAT

#include "newbigint.h"

class bigfloat {
private:
	bigint b;
	int scale; // b * D^scale (b is represented as D-ary number)
public:
	bigfloat() : b(0), scale(0) {};
	bigfloat(const bigint& b_) : b(b_), scale(0) {};
	bigfloat(const bigint& b_, int scale_) : b(b_), scale(scale_) {};
	int get_scale() const { return scale; }
	bigint get_number() const { return b; }
	bigfloat& set_scale(int scale_) {
		if (scale < scale_) b >>= (scale_ - scale);
		else b <<= (scale - scale_);
		scale = scale_;
		return *this;
	}
	bigfloat& operator<<=(int x) { scale += x; return *this; }
	bigfloat& operator>>=(int x) { scale -= x; return *this; }
	bigfloat& operator+=(const bigfloat& f) {
		if (scale > f.scale) (*this).set_scale(f.scale), (*this).b += f.b;
		else {
			bigint delta = f.b << (f.scale - scale);
			(*this).b += delta;
		}
		return *this;
	}
	bigfloat& operator-=(const bigfloat& f) {
		if (scale > f.scale) (*this).set_scale(f.scale), (*this).b -= f.b;
		else (*this).b -= (f.b << (f.scale - scale));
		return *this;
	}
	bigfloat& operator*=(const bigfloat& f) {
		b *= f.b;
		scale += f.scale;
		return *this;
	}
	bigfloat& operator/=(const bigfloat& f) {
		b /= f.b;
		scale -= f.scale;
		return *this;
	}
	bigfloat& divide_by_2() {
		b.divide_by_2();
		return *this;
	}
	bool operator==(const bigfloat& f) { return b == f.b && scale == f.scale; }
	bool operator!=(const bigfloat& f) { return b != f.b || scale != f.scale; }
	bigfloat operator<<(int x) const { return bigfloat(*this) <<= x; }
	bigfloat operator>>(int x) const { return bigfloat(*this) >>= x; }
	bigfloat operator+(const bigfloat& f) const { return bigfloat(*this) += f; }
	bigfloat operator-(const bigfloat& f) const { return bigfloat(*this) -= f; }
	bigfloat operator*(const bigfloat& f) const { return bigfloat(*this) *= f; }
	bigfloat operator/(const bigfloat& f) const { return bigfloat(*this) /= f; }
	std::string to_string() const {
		std::string s = b.to_string();
		if (scale * digit > 0) s += std::string(scale, '0');
		else if(1 <= -scale * digit && -scale * digit < s.size()) {
			s = s.substr(0, s.size() + scale * digit) + "." + s.substr(s.size() + scale * digit);
		}
		else if (-scale * digit >= s.size()) {
			s = "0." + std::string(-scale * digit - s.size(), '0') + s;
		}
		return s;
	}
	bigint to_bigint() const {
		if (scale < 0) return b >> (-scale);
		return b << scale;
	}
	friend std::ostream& operator<<(std::ostream& os, const bigfloat& f) { os << f.to_string(); return os; }
};

#endif