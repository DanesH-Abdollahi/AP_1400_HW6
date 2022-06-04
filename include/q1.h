#ifndef Q1_H
#define Q1_H

#include <cmath>
#include <iostream>

namespace q1 {
template <typename T, typename Func>
static const T gradient_descent(const T& initial_value, const T& step_size, Func function = Func {})
{
    T X { initial_value };
    T delta { step_size * 0.000001 }; // Small delta to avoid division by zero ( For calculating the derivative )
    T dY_dx {};
    T X_New {};

    while (true) {
        T dY_dX = (function(X + delta) - function(X)) / delta; // Calculating derivative
        T X_New = X - step_size * dY_dX; // Update X

        if (std::abs(X_New - X) >= delta) // If the difference between the X-New and X is smaller than delta, then we can stop
            X = X_New;
        else
            break;
    }
    return X;
}
}
#endif // Q1_H