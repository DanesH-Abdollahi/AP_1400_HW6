#ifndef Q2_H
#define Q2_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

// Name, Surname, Age, Smokes, AreaQ, Alkhol

namespace q2 {

struct Patient {
    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
};

std::vector<Patient> read_file(std::string filename)
{

    auto ss = std::ostringstream {};
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
                  << filename << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    // return ss.str();
}
}

#endif // Q2_H