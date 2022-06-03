#ifndef Q1_H
#define Q1_H
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>

namespace q1 {
template <typename T, typename Func>
const T gradient_descent(const T& initial_value, const T& step_size, Func function = Func {})
{
    T X { initial_value };
    T delta { step_size * 0.000001 };
    T dY_dx {};
    T X_New {};

    while (true) {
        T dY_dX = (function(X + delta) - function(X)) / delta;
        T X_New = X - step_size * dY_dX;

        if (std::abs(X_New - X) >= delta)
            X = X_New;
        else
            break;
        // std::map<T, T> Temp {};
        // Temp[X - step_size] = function(X - step_size);
        // Temp[X] = function(X);
        // Temp[X + step_size] = function(X + step_size);

        // const auto Local_min { *min_element(Temp.begin(), Temp.end(),
        //     [](const auto a, const auto b) { return a.second < b.second; }) };
        // if (Local_min.first != X) {
        //     X = Local_min.first;
        //     Y = Local_min.second;
        // } else
        //     break;
    }
    return X;
}
}
#endif // Q1_H