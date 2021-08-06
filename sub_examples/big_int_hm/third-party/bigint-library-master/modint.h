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