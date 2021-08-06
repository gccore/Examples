#include "basic_integer.h"
#include <string>
#include <iostream>
#include <algorithm>

const int digit = 4;
const int digit_base = 10000;

class bigint : public basic_integer<digit_base> {
public:
	bigint() { a = std::vector<int>({ 0 }); };
	bigint(long long x) {
		a.resize(1, 0);
		for (int i = 0; x > 0; ++i) {
			if (a.size() == i) {
				a.resize(a.size() * 2, 0);
			}
			a[i] = x % digit_base;
			x /= digit_base;
		}
	}
	bigint(const std::string& s) {
		a.resize(1, 0);
		for (int i = 0; digit * 4 < s.size(); ++i) {
			if (a.size() == i) {
				a.resize(a.size() * 2, 0);
			}
			a[i] = std::stoi(s.substr(std::max(int(s.size()) - i * 4 - 4, 0), 4));
		}
	}
	std::string to_string() const {
		std::string ret;
		bool flag = false;
		for (int i = a.size() - 1; i >= 0; --i) {
			if (a[i] > 0 && !flag) {
				ret += std::to_string(a[i]);
				flag = true;
			}
			else if (flag) {
				std::string sub = std::to_string(a[i]);
				ret += std::string(digit - sub.size(), '0') + sub;
			}
		}
		return ret.empty() ? "0" : ret;
	}
	bigint& operator<<=(int x) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) <<= x); }
	bigint& operator>>=(int x) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) >>= x); }
	bigint& operator+=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) += basic_integer(b)); }
	bigint& operator-=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) -= basic_integer(b)); }
	bigint& operator*=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) *= basic_integer(b)); }
	bigint& operator/=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) /= basic_integer(b)); }
	bigint operator<<(int x) const { return bigint(*this) <<= x; }
	bigint operator>>(int x) const { return bigint(*this) >>= x; }
	bigint operator+(const bigint& b) const { return bigint(*this) += b; }
	bigint operator-(const bigint& b) const { return bigint(*this) -= b; }
	bigint operator*(const bigint& b) const { return bigint(*this) *= b; }
	bigint operator/(const bigint& b) const { return bigint(*this) /= b; }
	friend std::istream& operator>>(std::istream& is, bigint& x) { std::string s; is >> s; x = bigint(s); return is; }
	friend std::ostream& operator<<(std::ostream& os, const bigint& x) { os << x.to_string(); return os; }
};