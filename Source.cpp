#include <cmath>
#include <iostream>
#include <vector>

template<typename Val>
class Factorial {
public:
	[[nodiscard]] Val operator()(size_t num) noexcept {
		if (num < cache.size()) return cache.at(num);
		cache.reserve(num);
		for (; num + 1 > cache.size();) cache.push_back(cache.back() * cache.size());
		return cache.back();
	}
private:
	std::vector<Val> cache = { 1, 1, 2, 6, 24, 120 };
};

template<typename Val>
class Power {
public:
	Power(Val value) noexcept : cache({1, value, value * value}) {}
	[[nodiscard]] Val operator()(size_t degree) noexcept {
		if (degree < cache.size()) return cache.at(degree);
		cache.reserve(degree);
		for (; degree + 1 > cache.size();) cache.push_back(cache.back() * cache.at(1));
		return cache.back();
	}
private:
	std::vector<Val> cache;
};

[[maybe_unused]] [[nodiscard]] size_t computeN(long double t, long double epsilon) noexcept {
	Power<long double> power(t);
	Factorial<long double> factorial;
	for (size_t n = 0;;) {
		long double nderiv;
		std::cout << "Input the value of " << n << " derivative:";
		std::cin >> nderiv; 
		if (std::abs(nderiv) * power(n) / factorial(n) <= epsilon) return n;
	}
}

[[nodiscard]] long double tangent(long double t, size_t n = 20) noexcept {
	long double retval;
	for (retval = t * t / (2 * n-- - 1); n > 0;) retval = t * t / (2 * n-- - 1 - retval);
	return retval / t;
}

[[nodiscard]] long double sine(long double t) noexcept {
	long double Pi = acosl(-1.L);
	t = std::remainder(t, 2 * Pi);
	if (Pi < t && t < 2 * Pi) t -= 2 * Pi;
	auto sign = (t < 0) ? -1LL : 1LL;
	t = std::abs(t);
	if (t > Pi / 2) t = Pi - t; // now t is in [0, Pi/2]
	long double tan4 = tangent(t / 4);
	return sign * 4 * tan4 * (1 - tan4 * tan4) / std::pow((1 + tan4 * tan4), 2);
}
[[nodiscard]] long double exponent(long double t, long double epsilon = 10e-15) noexcept {
	size_t n = std::ceil(t / epsilon);
	return std::pow((1 + t / n), n);
}

// Returns -1 if there is not enough derivatives
[[maybe_unused]] [[nodiscard]] int computeN(long double t, long double epsilon, const std::vector<long double>& derivatives) noexcept {
	Power<long double> power(t);
	Factorial<long double> factorial;
	for (size_t n = 0; n < derivatives.size(); ++n) {
		if (std::abs(derivatives.at(n)) * power(n) / factorial(n) <= epsilon) return n;
	}
	return -1;
}

int main() {
	Factorial<long double> factorial;
	auto deltaT = 1e-3L; // epsilon, long double
	auto n = 0;
	Power<long double> power1(1 + deltaT);
	Power<long double> power2(11 + deltaT);
	std::cout << "For sine function: " << std::endl;
	for (; power1(2 * n + 1)/ factorial(2 * n + 1) > deltaT; ++n);
	std::cout << "t in [0, 1]: n = " << n << std::endl;
	for (n = 0; power2(2 * n + 1) / factorial(2 * n + 1) > deltaT; ++n);
	std::cout << "t in [10, 11]: n = " << n << std::endl;
	std::cout << "Input value for sine and exponent calculation: ";
	long double t;
	std::cin >> t;
	std::cout << "Sin(" << t << ") = " << sine(t) << ' ' << std::sin(t) << std::endl;
	std::cout << "Exp(" << t << ") = " << exponent(t) << ' ' << std::exp(t) << std::endl;
	
	return EXIT_SUCCESS;
}