#ifndef Q4_H
#define Q4_H

#include <iostream>
#include <vector>

namespace q4 {

struct Vector2D {
    Vector2D() = default; // Default Constructor
    Vector2D(const double& _x, const double& _y) // Constructor
        : x { _x }
        , y { _y }
    {
    }

    double x {};
    double y {};
};

struct Sensor {

    Sensor(const Vector2D& _pos, const double& _accuracy) // Constructor
        : pos { _pos }
        , accuracy { _accuracy }
    {
    }

    Vector2D pos;
    double accuracy;
};

static const Vector2D kalman_filter(std::vector<Sensor> sensors)
{

    Vector2D Answ {}; // Construct an Object Of Vector2D Class
    double Sum_Of_Accs {}; // Sum of All Accuracies
    std::for_each(sensors.begin(), sensors.end(), [&Sum_Of_Accs](const auto a) { Sum_Of_Accs += a.accuracy; }); // Calculating Sum_Of_Accs

    // Computing The Weighted_Mean Pos
    std::for_each(sensors.begin(), sensors.end(), [Sum_Of_Accs, &Answ](const auto a) {
        Answ.x += (a.accuracy / Sum_Of_Accs) * a.pos.x, Answ.y += (a.accuracy / Sum_Of_Accs) * a.pos.y;
    });

    return Answ;
}

}

#endif // Q4_H