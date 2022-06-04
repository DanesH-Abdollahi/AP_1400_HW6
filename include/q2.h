#ifndef _Q2_H_
#define _Q2_H_

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace q2 {

struct Patient {
    // Constructor
    Patient(const std::string& _name, const std::string& _surname, const size_t& _age, const size_t& _smokes, const size_t& _area_q, const size_t& _alkhol)
        : name { _name + " " + _surname }
        , age { _age }
        , smokes { _smokes }
        , area_q { _area_q }
        , alkhol { _alkhol }

    {
    }
    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
};

static std::vector<Patient> read_file(std::string filename)
{
    std::vector<Patient> patients;
    std::ifstream file(filename);
    std::stringstream buffer {};
    buffer << file.rdbuf();
    std::string txt { buffer.str() };

    std::regex pattern(R"((\w+) *, *(\w+) *, *(\d+) *, *(\d+) *, *(\d+) *, *(\d+) *)"); // Pattern For Find Patient's Information
    std::smatch match;

    while (std::regex_search(txt, match, pattern)) {
        Patient tmp { match[1], match[2], static_cast<size_t>(std::stoi(match[3])), static_cast<size_t>(std::stoi(match[4])),
            static_cast<size_t>(std::stoi(match[5])), static_cast<size_t>(std::stoi(match[6])) }; // Construct an Object Of Patient Class

        patients.push_back(tmp); // Add The Object To patients Vector

        txt = match.suffix().str();
    }

    return patients;
}

static void sort(std::vector<Patient>& patient)
{
    auto Greater_Possibility {
        [](const auto a, const auto b) { return (3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol)
                                             > (3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol); }
    }; // Define a lambda Function For Comparing 2 Patients Object's

    std::sort(patient.begin(), patient.end(), Greater_Possibility); // Sort The patients Vector
}
}

#endif // Q2_H