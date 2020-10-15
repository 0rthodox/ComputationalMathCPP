#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <numeric>

using val = long double;

template<typename Val>
bool is_equal(Val a, Val b)
{
	return std::fabsl(a - b) < std::numeric_limits<Val>::epsilon();
}

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

enum class Result {
	HAS_SOLUTION,
	INFINITE_SOLUTIONS,
	NO_SOLUTIONS
};


template<typename Val>
[[maybe_unused]] [[nodiscard]] std::pair<Result, std::vector<Val>> solve(std::vector<std::vector<Val>>& a) noexcept {
	
	for (auto i = size_t(); i < a.size() - 1U; ++i)
	{
		for (auto j = i + 1U; j < a.size(); ++j) 
		{
			if (is_equal<Val>(a[i][i], 0.)) // if coefficient on main diagonal is zero
			{
				auto row = i + 1U;

				for (; row < a.size() && is_equal<Val>(a[row][i], 0.); ++row); // seeking the one without zero

				if (row == a.size()) break;

				for (auto k = i; k <= a.size(); ++k) std::swap(a[i][k], a[row][k]); // swapping
			}

			double r = a[j][i] / a[i][i];

			for (auto p = i; p <= a.size(); ++p)
			{
				a[j][p] -= r * a[i][p]; // forward stroke
			}
		}
	}


	for (auto i = 0U; i < a.size(); ++i)
	{
		double r = a[i][i];

		if (!is_equal(r, 0.0))
		{
			for (auto j = i; j <= a.size(); ++j)
			{
				a[i][j] /= r;
			}
		}
	}
	
	for (auto i = a.size() - 1U; i > 0; --i) 
	{
		for (int j = static_cast<int>(i) - 1; j >= 0; --j)
		{
			double r = a[j][i];

			for (auto k = i; k <= a.size(); ++k)
			{
				a[j][k] -= r * a[i][k]; // backward stroke
			}
		}
	}

	// looking for null rows

	Result flag = Result::HAS_SOLUTION;

	for (auto i = 0U; i < a.size(); ++i)
	{
		bool is_null = true;

		for (auto j = 0U; j < a.size(); ++j)
		{
			if (!is_equal<Val>(a[i][j], 0.L)) is_null = false;
		}

		if (is_null)
		{
			if (a[i][a.size()] != 0.0)
			{
				flag = Result::NO_SOLUTIONS;
			}
			else if (a[i][a.size()] == 0.0 && flag != Result::NO_SOLUTIONS)
			{
				flag = Result::INFINITE_SOLUTIONS;
			}
		}
	}
	
	std::vector<Val> retval;

	for (const auto& vect : a) {
		retval.push_back(vect[a.size()]);
	}

	return { flag, retval };
	
}


int main()
{
	auto h = 10;
	std::vector<val> values = { 92228496, 106021537, 123202624, 132164569, 151325798,
		179323175, 203211926, 226545805, 248709873, 281421906 };

	auto index = 5;
	auto size = values.size();
	std::vector<val> b(size, 0);
	b[1] = 1.L / h;
	std::vector<std::vector<val>> a(size);
	std::for_each(a.begin(), a.end(), [size](auto& vect) {vect.resize(size + 1); });
	Factorial<val> factorial;
	for (auto i = 0; i < size; ++i) {
		for (auto j = 0; j < size; ++j) {
			a[i][j] = std::pow(j + 1 - index, i) / factorial(i);
		}
		a[i][size] = b[i];
	}
	auto result = solve(a).second;	

	auto deriv = std::inner_product(result.begin(), result.end(), values.begin(), 0.L);
	
	auto estimateLeft = (values[index - 1] - values[index - 2]) / h;
	auto estimateRight = (values[index] - values[index - 1]) / h;

	std::cout.setf(std::ios::fixed);
	std::cout.precision(0);
	std::cout << "Result is " << deriv << ", left est.: " << estimateLeft << ", right est.: " << estimateRight << std::endl;
		

	return 0;
}