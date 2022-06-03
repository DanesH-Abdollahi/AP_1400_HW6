#ifndef Q4_H
#define Q4_H

namespace q4 {

struct Vector2D {
    Vector2D() = default;
    Vector2D(const double& _x, const double& _y)
        : x { _x }
        , y { _y }
    {
    }

    double x {};
    double y {};
};

struct Sensor {

    Sensor(const Vector2D& _pos, const double& _accuracy)
        : pos { _pos }
        , accuracy { _accuracy }
    {
    }

    Vector2D pos;
    double accuracy;
};

static const Vector2D kalman_filter(std::vector<Sensor> sensors)
{

    Vector2D Answ {};
    double Sum_Of_Accs {};
    std::for_each(sensors.begin(), sensors.end(), [&Sum_Of_Accs](const auto a) { Sum_Of_Accs += a.accuracy; });

    std::for_each(sensors.begin(), sensors.end(), [Sum_Of_Accs, &Answ](const auto a) {
        Answ.x += (a.accuracy / Sum_Of_Accs) * a.pos.x, Answ.y += (a.accuracy / Sum_Of_Accs) * a.pos.y;
    });

    return Answ;
}

}

#endif // Q4_H