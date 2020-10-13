#include <iostream>
#include <cmath>
#include <iomanip>

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
	return std::fabsl(a - b) < std::numeric_limits<Val>::epsilon();
}

template <typename Val>
Val fx(Val x) noexcept
{
	return x * x + std::pow(std::tanl(x), 2) - Val(1);
}

template <typename Val>
Val fy(Val y) noexcept
{
	return y * y + std::pow(std::atanl(y), 2) - Val(1);
}
int main()
{
	std::pair bounds = { val(0.6L), val(0.7L) };
	auto error = val(1e-6L);
	auto distance = bounds.second - bounds.first;
	for (; distance >= error;) {
			if (fx(bounds.first) * fx((bounds.first + bounds.second) / 2) < 0) {
					bounds.second = (bounds.first + bounds.second)/2;
					distance /= 2;
			}
			if(fx(bounds.second) * fx((bounds.first + bounds.second) / 2) < 0)
				{
					bounds.first = (bounds.first + bounds.second) / 2;
					distance /= 2;
				}
	}
	std::pair result = { bounds.first, val() };
	bounds = {0.7L, 0.8L};
	distance = (bounds.second - bounds.first) / 2;
	for (; distance >= error;) {
		if (fy(bounds.first) * fy((bounds.first + bounds.second) / 2) < 0) {
			bounds.second = (bounds.first + bounds.second) / 2;
			distance /= 2;
		}
		if (fy(bounds.second) * fy((bounds.first + bounds.second) / 2) < 0)
		{
			bounds.first = (bounds.first + bounds.second) / 2;
			distance /= 2;
		}
	}
	result.second = bounds.first;
	std::cout.setf(std::ios::fixed);
	std::cout.precision(6);
	std::cout << "Answers are " << result << " and " << -result << std::endl;
	return EXIT_SUCCESS;
}
