#ifndef ___CLASS_NEWBIGINT
#define ___CLASS_NEWBIGINT

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
		a.clear();
		for (int i = 0; x > 0; ++i) {
			a.push_back(x % digit_base);
			x /= digit_base;
		}
		if (a.size() == 0) a = { 0 };
	}
	bigint(const std::string& s) {
		a.clear();
		for (int i = 0; digit * i < s.size(); ++i) {
			a.push_back(std::stoi(s.substr(std::max(int(s.size()) - i * digit - digit, 0), digit - std::max(digit + i * digit - int(s.size()), 0))));
		}
		if (a.size() == 0) a = { 0 };
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
	int convert_int() const { return std::stoi((*this).to_string()); }
	long long convert_ll() const { return std::stoll((*this).to_string()); }
	bigint& operator<<=(int x) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) <<= x); }
	bigint& operator>>=(int x) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) >>= x); }
	bigint& operator+=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) += basic_integer(b)); }
	bigint& operator-=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) -= basic_integer(b)); }
	bigint& operator*=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) *= basic_integer(b)); }
	bigint& operator/=(const bigint& b) { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a) /= basic_integer(b)); }
	bigint& divide_by_2() { return reinterpret_cast<bigint&>(reinterpret_cast<basic_integer&>(a).divide_by_2()); }
	bigint operator<<(int x) const { return bigint(*this) <<= x; }
	bigint operator>>(int x) const { return bigint(*this) >>= x; }
	bigint operator+(const bigint& b) const { return bigint(*this) += b; }
	bigint operator-(const bigint& b) const { return bigint(*this) -= b; }
	bigint operator*(const bigint& b) const { return bigint(*this) *= b; }
	bigint operator/(const bigint& b) const { return bigint(*this) /= b; }
	friend std::istream& operator>>(std::istream& is, bigint& x) { std::string s; is >> s; x = bigint(s); return is; }
	friend std::ostream& operator<<(std::ostream& os, const bigint& x) { os << x.to_string(); return os; }
};

#endif