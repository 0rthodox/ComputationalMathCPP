#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

using val = long double;

template <typename Val>
Val toBeIntegrated(Val x) {
    return std::sin(100 * x) * std::exp(-x * x) * std::cos(2 * x);
}

template <typename Val>
Val integrate(std::function<Val(Val)> func, std::pair<Val, Val> bounds, Val step) noexcept {
    auto retval = Val();
    for(auto x = bounds.first; x <= bounds.second; x += step) retval += func(x) * step;
    return retval;
}

int main()
{
    val step = 1e-6L;
    std::pair bounds = {val(), val(3)};
    auto result = integrate<val>(toBeIntegrated<val>, bounds, step);
    auto sResult = integrate<val>(toBeIntegrated<val>, bounds, step * 2);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(std::numeric_limits<val>::digits10 - 1);
    std::cout << "The answer is " << result << std::endl;
    std::cout << "Error is " << std::abs(result - sResult) / 3 << std::endl;
    system("pause");
    return 0;
}
