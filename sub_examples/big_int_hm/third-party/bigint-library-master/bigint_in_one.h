#ifndef ___CLASS_MODINT
#define ___CLASS_MODINT

#include <vector>
#include <cstdint>

using singlebit = uint32_t;
using doublebit = uint64_t;

static constexpr singlebit find_inv(singlebit n, int d = 5, singlebit x = 1) {
	return d == 0 ? x : find_inv(n, d - 1, x * (2 - x * n));
}
template <singlebit mod, singlebit primroot> class modint {
	// Fast Modulo Integer, Assertion: mod < 2^31
private:
	singlebit n;
	static constexpr int level = 32; // LIMIT OF singlebit
	static constexpr singlebit max_value = -1;
	static constexpr singlebit r2 = (((1ull << level) % mod) << level) % mod;
	static constexpr singlebit inv = singlebit(-1) * find_inv(mod);
	static singlebit reduce(doublebit x) {
		singlebit res = (x + doublebit(singlebit(x) * inv) * mod) >> level;
		return res < mod ? res : res - mod;
	}
public:
	modint() : n(0) {};
	modint(singlebit n_) { n = reduce(doublebit(n_) * r2); };
	modint& operator=(const singlebit x) { n = reduce(doublebit(x) * r2); return *this; }
	bool operator==(const modint& x) const { return n == x.n; }
	bool operator!=(const modint& x) const { return n != x.n; }
	modint& operator+=(const modint& x) { n += x.n; n -= (n < mod ? 0 : mod); return *this; }
	modint& operator-=(const modint& x) { n += mod - x.n; n -= (n < mod ? 0 : mod); return *this; }
	modint& operator*=(const modint& x) { n = reduce(1ull * n * x.n); return *this; }
	modint operator+(const modint& x) const { return modint(*this) += x; }
	modint operator-(const modint& x) const { return modint(*this) -= x; }
	modint operator*(const modint& x) const { return modint(*this) *= x; }
	static singlebit get_mod() { return mod; }
	static singlebit get_primroot() { return primroot; }
	singlebit get() { return reduce(doublebit(n)); }
	modint binpow(singlebit b) {
		modint ans(1), cur(*this);
		while (b > 0) {
			if (b & 1) ans *= cur;
			cur *= cur;
			b >>= 1;
		}
		return ans;
	}
};

template<typename modulo>
std::vector<modulo> get_modvector(std::vector<int> v) {
	std::vector<modulo> ans(v.size());
	for (int i = 0; i < v.size(); ++i) {
		ans[i] = v[i];
	}
	return ans;
}

#endif

#ifndef ___CLASS_NTT
#define ___CLASS_NTT

#include <vector>

template<typename modulo>
class ntt {
	// Number Theoretic Transform
private:
	int depth;
	std::vector<modulo> roots;
	std::vector<modulo> powinv;
public:
	ntt() {
		depth = 0;
		uint32_t div_number = modulo::get_mod() - 1;
		while (div_number % 2 == 0) div_number >>= 1, ++depth;
		modulo b = modulo::get_primroot();
		for (int i = 0; i < depth; ++i) b *= b;
		modulo baseroot = modulo::get_primroot(), bb = b;
		while (bb != 1) bb *= b, baseroot *= modulo::get_primroot();
		roots = std::vector<modulo>(depth + 1, 0);
		powinv = std::vector<modulo>(depth + 1, 0);
		powinv[1] = (modulo::get_mod() + 1) / 2;
		for (int i = 2; i <= depth; ++i) powinv[i] = powinv[i - 1] * powinv[1];
		roots[depth] = 1;
		for (int i = 0; i < modulo::get_mod() - 1; i += 1 << depth) roots[depth] *= baseroot;
		for (int i = depth - 1; i >= 1; --i) roots[i] = roots[i + 1] * roots[i + 1];
	}
	void fourier_transform(std::vector<modulo> &v, bool inverse) {
		int s = v.size();
		for (int i = 0, j = 1; j < s - 1; ++j) {
			for (int k = s >> 1; k >(i ^= k); k >>= 1);
			if (i < j) std::swap(v[i], v[j]);
		}
		int sc = 0, sz = 1;
		while (sz < s) sz *= 2, ++sc;
		std::vector<modulo> pw(s + 1); pw[0] = 1;
		for (int i = 1; i <= s; i++) pw[i] = pw[i - 1] * roots[sc];
		int qs = s;
		for (int b = 1; b < s; b <<= 1) {
			qs >>= 1;
			for (int i = 0; i < s; i += b * 2) {
				for (int j = i; j < i + b; ++j) {
					modulo delta = pw[(inverse ? b * 2 - j + i : j - i) * qs] * v[j + b];
					v[j + b] = v[j] - delta;
					v[j] += delta;
				}
			}
		}
		if (inverse) {
			for (int i = 0; i < s; ++i) v[i] *= powinv[sc];
		}
	}
	std::vector<modulo> convolve(std::vector<modulo> v1, std::vector<modulo> v2) {
		const int threshold = 16;
		if (v1.size() < v2.size()) swap(v1, v2);
		int s1 = 1; while (s1 < v1.size()) s1 <<= 1; v1.resize(s1);
		int s2 = 1; while (s2 < v2.size()) s2 <<= 1; v2.resize(s2 * 2);
		std::vector<modulo> ans(s1 + s2);
		if (s2 <= threshold) {
			for (int i = 0; i < s1; ++i) {
				for (int j = 0; j < s2; ++j) {
					ans[i + j] += v1[i] * v2[j];
				}
			}
		}
		else {
			fourier_transform(v2, false);
			for (int i = 0; i < s1; i += s2) {
				std::vector<modulo> v(v1.begin() + i, v1.begin() + i + s2);
				v.resize(s2 * 2);
				fourier_transform(v, false);
				for (int j = 0; j < v.size(); ++j) v[j] *= v2[j];
				fourier_transform(v, true);
				for (int j = 0; j < s2 * 2; ++j) {
					ans[i + j] += v[j];
				}
			}
		}
		return ans;
	}
};

#endif

#ifndef __CLASS_BASICINTEGER
#define __CLASS_BASICINTEGER

#include <vector>

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
	basic_integer operator >> (int x) const { return basic_integer(*this) >>= x; }
	basic_integer operator+(const basic_integer& b) const { return basic_integer(*this) += b; }
	basic_integer operator-(const basic_integer& b) const { return basic_integer(*this) -= b; }
	basic_integer operator*(const basic_integer& b) const { return basic_integer(*this) *= b; }
	basic_integer operator/(const basic_integer& b) const { return basic_integer(*this) /= b; }
};

#endif

#ifndef ___CLASS_NEWBIGINT
#define ___CLASS_NEWBIGINT

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
	bigint operator >> (int x) const { return bigint(*this) >>= x; }
	bigint operator+(const bigint& b) const { return bigint(*this) += b; }
	bigint operator-(const bigint& b) const { return bigint(*this) -= b; }
	bigint operator*(const bigint& b) const { return bigint(*this) *= b; }
	bigint operator/(const bigint& b) const { return bigint(*this) /= b; }
	friend std::istream& operator >> (std::istream& is, bigint& x) { std::string s; is >> s; x = bigint(s); return is; }
	friend std::ostream& operator<<(std::ostream& os, const bigint& x) { os << x.to_string(); return os; }
};

#endif

#ifndef ___CLASS_NEWBIGFLOAT
#define ___CLASS_NEWBIGFLOAT

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
	bigfloat operator >> (int x) const { return bigfloat(*this) >>= x; }
	bigfloat operator+(const bigfloat& f) const { return bigfloat(*this) += f; }
	bigfloat operator-(const bigfloat& f) const { return bigfloat(*this) -= f; }
	bigfloat operator*(const bigfloat& f) const { return bigfloat(*this) *= f; }
	bigfloat operator/(const bigfloat& f) const { return bigfloat(*this) /= f; }
	std::string to_string() const {
		std::string s = b.to_string();
		if (scale * digit > 0) s += std::string(scale, '0');
		else if (1 <= -scale * digit && -scale * digit < s.size()) {
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