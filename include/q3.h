#ifndef Q3_H
#define Q3_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <sstream>
#include <string>

namespace q3 {
struct Flight {

    Flight(const std::string& _flight_num, const size_t& _duration,
        const size_t& _connections, const size_t& _connection_times, const size_t& _price)
        : flight_number { _flight_num }
        , duration { _duration }
        , connections { _connections }
        , connection_times { _connection_times }
        , price { _price }

    {
    }

    std::string flight_number;
    size_t duration;
    size_t connections;
    size_t connection_times;
    size_t price;
};

static auto func { [](auto a, auto b) { return (a.duration + a.connection_times + 3 * a.price)
                                            >= (b.duration + b.connection_times + 3 * b.price); } };

static std::priority_queue<Flight, std::vector<Flight>, decltype(func)> gather_flights(std::string filename)
{

    std::ifstream file(filename);
    std::stringstream buffer {};
    buffer << file.rdbuf();
    std::string txt { buffer.str() };

    std::regex pattern(R"(flight_number *: *(\w+) * - * duration *: *(\d+)?h?(\d+)?m? *- *connections *: *(\d+) *- *connection_times *: *(\S+) *- *price *: *(\d+))");
    std::smatch match;

    std::priority_queue<Flight, std::vector<Flight>, decltype(func)> flights { func };

    while (std::regex_search(txt, match, pattern)) {

        size_t Totall_Conecction_Time {}; // In Minutes4
        size_t Duration {}; // In Minutes

        std::string txt1 { match[5] };

        std::regex pattern1(R"((\d+)h(\d+)?m?)");
        std::smatch match1;

        while (std::regex_search(txt1, match1, pattern1)) {

            if (!match1[1].str().empty())
                Totall_Conecction_Time += std::stoi(match1[1]) * 60;

            if (!match1[2].str().empty())
                Totall_Conecction_Time += std::stoi(match1[2]);

            txt1 = match1.suffix().str();
        }
        Totall_Conecction_Time = static_cast<size_t>(Totall_Conecction_Time);

        if (!match[2].str().empty())
            Duration += std::stoi(match[2]) * 60;
        if (!match[3].str().empty())
            Duration += std::stoi(match[3]);

        Flight tmp {
            match[1].str(),
            Duration,
            static_cast<size_t>(std::stoi(match[4])),
            Totall_Conecction_Time,
            static_cast<size_t>(std::stoi(match[6]))
        };

        flights.push(tmp);

        txt = match.suffix().str();
    }

    return flights;
}

}

#endif // Q3_H