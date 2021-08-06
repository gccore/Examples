#ifndef __CLASS_BASICINTEGER
#define __CLASS_BASICINTEGER

#include <vector>
#include "ntt.h"

using modulo1 = modint<469762049, 3>; ntt<modulo1> ntt_base1;
using modulo2 = modint<167772161, 3>; ntt<modulo2> ntt_base2;

const modulo1 magic_inv = modulo1(modulo2::get_mod()).binpow(modulo1::get_mod() - 2);

template<int base>
class basic_integer {
protected:
	std::vector<int> a;
public:
	basic_integer() : a(std::vector<int>({ 0 })) {};
	basic_integer(const std::vector<int>& a_) : a(a_) {};
	int size() const { return a.size(); }
	int nth_digit(int n) const { return a[n]; }
	basic_integer& resize() {
		int lim = 1;
		for (int i = 0; i < a.size(); ++i) {
			if (a[i] != 0) lim = i + 1;
		}
		a.resize(lim);
		return *this;
	}
	basic_integer& shift() {
		for (int i = 0; i < int(a.size()) - 1; ++i) {
			if (a[i] >= 0) {
				a[i + 1] += a[i] / base;
				a[i] %= base;
			}
			else {
				int x = (-a[i] + base - 1) / base;
				a[i] += x * base;
				a[i + 1] -= x;
			}
		}
		while (a.back() >= base) {
			a.push_back(a.back() / base);
			a[a.size() - 2] %= base;
		}
		return *this;
	}
	bool operator==(const basic_integer& b) const { return a == b.a; }
	bool operator!=(const basic_integer& b) const { return a != b.a; }
	bool operator<(const basic_integer& b) const {
		if (a.size() != b.a.size()) return a.size() < b.a.size();
		for (int i = a.size() - 1; i >= 0; --i) {
			if (a[i] != b.a[i]) return a[i] < b.a[i];
		}
		return false;
	}
	bool operator>(const basic_integer& b) const { return b < (*this); }
	bool operator<=(const basic_integer& b) const { return !((*this) > b); }
	bool operator>=(const basic_integer& b) const { return !((*this) < b); }
	basic_integer& operator<<=(const uint32_t x) {
		if (a.back() >= 1 || a.size() >= 2) {
			std::vector<int> v(x, 0);
			a.insert(a.begin(), v.begin(), v.end());
		}
		return (*this);
	}
	basic_integer& operator>>=(const uint32_t x) {
		if (x == 0) return *this;
		if (x > a.size()) a = { 0 };
		else a = std::vector<int>(a.begin() + x, a.end());
		return (*this);
	}
	basic_integer& operator+=(const basic_integer& b) {
		if (a.size() < b.a.size()) a.resize(b.a.size(), 0);
		for (int i = 0; i < b.a.size(); ++i) a[i] += b.a[i];
		return (*this).shift();
	}
	basic_integer& operator-=(const basic_integer& b) {
		for (int i = 0; i < b.a.size(); ++i) a[i] -= b.a[i];
		return (*this).shift().resize();
	}
	basic_integer& operator*=(const basic_integer& b) {
		std::vector<modulo1> mul_base1 = ntt_base1.convolve(get_modvector<modulo1>(a), get_modvector<modulo1>(b.a));
		std::vector<modulo2> mul_base2 = ntt_base2.convolve(get_modvector<modulo2>(a), get_modvector<modulo2>(b.a));
		const int margin = 20;
		a = std::vector<int>(mul_base1.size() + margin);
		for (int i = 0; i < a.size() - margin; ++i) {
			// s * p1 + a1 = val = t * p2 + a2's solution is t = (a1 - a2) / p2 (mod p1)
			long long val = (long long)(((mul_base1[i] - modulo1(mul_base2[i].get())) * magic_inv).get()) * modulo2::get_mod() + mul_base2[i].get();
			for (int j = i; val > 0 && j < a.size(); ++j) {
				a[j] += val % base;
				if (a[j] >= base) {
					a[j] -= base;
					a[j + 1] += 1;
				}
				val /= base;
			}
		}
		return (*this).resize();
	}
	basic_integer& operator/=(const basic_integer& b) {
		int preci = a.size() - b.a.size();
		basic_integer t({ 1 });
		basic_integer two = basic_integer({ 2 }) << b.a.size();
		basic_integer pre;
		int lim = std::min(preci, 3);
		int blim = std::min(int(b.a.size()), 6);
		t <<= lim;
		while (pre != t) {
			basic_integer rb = b >> (b.a.size() - blim);
			if (blim != b.a.size()) rb += basic_integer({ 1 });
			pre = t;
			t *= (basic_integer({ 2 }) << (blim + lim)) - rb * t;
			t.a = std::vector<int>(t.a.begin() + lim + blim, t.a.end());
		}
		if (lim != preci) {
			pre = basic_integer();
			while (pre != t) {
				basic_integer rb = b >> (b.a.size() - blim);
				if (blim != b.a.size()) rb += basic_integer({ 1 });
				pre = t;
				t *= (basic_integer({ 2 }) << (blim + lim)) - rb * t;
				t.a = std::vector<int>(t.a.begin() + lim + blim, t.a.end());
				int next_lim = std::min(lim * 2 + 1, preci);
				if (next_lim != lim) t <<= next_lim - lim;
				int next_blim = std::min(blim * 2 + 1, int(b.a.size()));
				lim = next_lim;
				blim = next_blim;
			}
		}
		basic_integer ans = (*this) * t;
		ans.a = std::vector<int>(ans.a.begin() + a.size(), ans.a.end());
		while ((ans + basic_integer({ 1 })) * b <= (*this)) {
			ans += basic_integer({ 1 });
		}
		(*this) = ans.resize();
		return *this;
	}
	basic_integer& divide_by_2() {
		for (int i = a.size() - 1; i >= 0; --i) {
			int carry = a[i] % 2;
			a[i] /= 2;
			if (i != 0) a[i - 1] += carry * base;
		}
		if (a.size() >= 2 && a.back() == 0) a.pop_back();
		return *this;
	}
	basic_integer operator<<(int x) const { return basic_integer(*this) <<= x; }
	basic_integer operator>>(int x) const { return basic_integer(*this) >>= x; }
	basic_integer operator+(const basic_integer& b) const { return basic_integer(*this) += b; }
	basic_integer operator-(const basic_integer& b) const { return basic_integer(*this) -= b; }
	basic_integer operator*(const basic_integer& b) const { return basic_integer(*this) *= b; }
	basic_integer operator/(const basic_integer& b) const { return basic_integer(*this) /= b; }
};

#endif