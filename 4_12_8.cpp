#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>

using val = long double;

template <typename Val>
[[nodiscard]] Val lPhi(Val x) noexcept {
    return std::exp(x * x) / 2 / (std::sqrt(2) * std::exp(0.5));
}
template <typename Val>
[[nodiscard]] Val rPhi(Val x) noexcept {
    return std::sqrt(log(2 * x * std::sqrt(2) * std::exp(0.5)));
}


template <typename Val>
Val MSI(Val current, std::function<Val(Val)> func, Val epsilon) {
    for(; std::abs(current - func(current)) > epsilon; current = func(current));
    return current;
}

int main() {
    val epsilon = 1e-4L;
    std::pair line = {MSI<val>(val(0.2L), lPhi<val>, epsilon), MSI<val>(val(1.4L), rPhi<val>, epsilon)};
    std::cout << std::setprecision(4) << line.second - line.first << std::endl;
}




