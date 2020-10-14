#include <iostream>
#include <cmath>
#include <functional>

using val = long double;

template<typename Val>
std::ostream& operator<< (std::ostream& ostr, std::pair<Val, Val> pair) {
	ostr << '(' << pair.first << ", " << pair.second << ')';
	return ostr;
}

template<typename Val>
std::pair<Val, Val> operator-(const std::pair<Val, Val>& pair) noexcept {
	return { -pair.first, -pair.second };
}

template<typename Val>
[[maybe_unused]] bool is_equal(Val a, Val b) noexcept
{
	return std::abs(a - b) < std::numeric_limits<Val>::epsilon();
}

template <typename Val>
Val binarySearch(std::pair<Val, Val> bounds, std::function<Val(Val)> func, Val error) noexcept {
    for (; bounds.second - bounds.first >= error;
    (bounds.second = (func(bounds.first) * func((bounds.first + bounds.second) / 2) < 0) ?
        (bounds.first + bounds.second) / 2 : bounds.second) &&
    (bounds.first = (func(bounds.second) * func((bounds.first + bounds.second) / 2) < 0) ?
        (bounds.first + bounds.second) / 2 : bounds.first));
    return bounds.first;
}

template <typename Val>
Val fx(Val x) noexcept {
	return x * x + std::pow(std::tan(x), 2) - Val(1);
}

template <typename Val>
Val fy(Val y) noexcept {
	return y * y + std::pow(std::atan(y), 2) - Val(1);
}
int main()
{
    std::pair xBounds = { val(0.6L), val(0.7L) };
    std::pair yBounds = { val(0.7L), val(0.8L) };
    auto error = val(1e-6L);
    std::pair result = {binarySearch<val>(xBounds, fx<val>, error), binarySearch<val>(yBounds, fy<val>, error)};

	  std::cout.setf(std::ios::fixed);
	  std::cout.precision(6);
	  std::cout << "Answers are " << result << " and " << -result << std::endl;
	return EXIT_SUCCESS;
}
