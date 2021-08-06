#ifndef ___CLASS_NTT
#define ___CLASS_NTT

#include <vector>
#include "modint.h"

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