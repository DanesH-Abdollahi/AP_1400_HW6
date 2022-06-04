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
    // Constructor
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

// Define a lambda Function For Comparing 2 Flight's Object's
static auto func { [](auto a, auto b) { return (a.duration + a.connection_times + 3 * a.price)
                                            >= (b.duration + b.connection_times + 3 * b.price); } };

static std::priority_queue<Flight, std::vector<Flight>, decltype(func)> gather_flights(std::string filename)
{

    std::ifstream file(filename);
    std::stringstream buffer {};
    buffer << file.rdbuf();
    std::string txt { buffer.str() };

    // Pattern For Find Flight's Information
    std::regex pattern(R"(flight_number *: *(\w+) * - * duration *: *(\d+)?h?(\d+)?m? *- *connections *: *(\d+) *- *connection_times *: *(\S+) *- *price *: *(\d+))");
    std::smatch match;

    std::priority_queue<Flight, std::vector<Flight>, decltype(func)> flights { func }; // Define the Priority_queue Flights

    while (std::regex_search(txt, match, pattern)) {

        size_t Totall_Conecction_Time {}; // In Minutes
        size_t Duration {}; // In Minutes

        std::string txt1 { match[5] };

        std::regex pattern1(R"((\d+)h(\d+)?m?)"); // Pattern For Find Connection_Time For each Flight
        std::smatch match1;

        while (std::regex_search(txt1, match1, pattern1)) { // Finding Connection_Time For each Flight

            if (!match1[1].str().empty())
                Totall_Conecction_Time += std::stoi(match1[1]) * 60;

            if (!match1[2].str().empty())
                Totall_Conecction_Time += std::stoi(match1[2]);

            txt1 = match1.suffix().str();
        }
        Totall_Conecction_Time = static_cast<size_t>(Totall_Conecction_Time);

        // Computing Totall Duratin Time for each Flight
        if (!match[2].str().empty())
            Duration += std::stoi(match[2]) * 60;
        if (!match[3].str().empty())
            Duration += std::stoi(match[3]);

        // Construct an Object Of Flight Class
        Flight tmp {
            match[1].str(),
            Duration,
            static_cast<size_t>(std::stoi(match[4])),
            Totall_Conecction_Time,
            static_cast<size_t>(std::stoi(match[6]))
        };

        flights.push(tmp); // Add The Object To flights Priority queue

        txt = match.suffix().str();
    }

    return flights;
}

}

#endif // Q3_H