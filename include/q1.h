#ifndef Q1_H
#define Q1_H
#include <algorithm>
#include <iostream>
#include <map>

namespace q1 {
template <typename T, typename Func>
const T gradient_descent(const T& initial_value, const T& step_size, Func function = Func {})
{
    T x { initial_value };
    T y { function(x) };

    while (true) {
        std::map<T, T> Temp {};
        Temp[x - step_size] = function(x - step_size);
        Temp[x] = function(x);
        Temp[x + step_size] = function(x + step_size);

        const auto Local_min { *min_element(Temp.begin(), Temp.end(),
            [](const auto a, const auto b) { return a.second < b.second; }) };
        if (Local_min.first != x) {
            x = Local_min.first;
            y = Local_min.second;
        } else
            break;
    }
    return x;
}
}
#endif // Q1_H