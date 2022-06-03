#include <gtest/gtest.h>
#include <iostream>

#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"

int main(int argc, char** argv)
{
    if (false) {

        std::ifstream file("flights.txt");
        std::stringstream buffer {};
        buffer << file.rdbuf();
        std::string txt { buffer.str() };

        std::regex pattern(R"(duration:(\d+)h(\d+)?m?)");
        std::smatch match;

        while (std::regex_search(txt, match, pattern)) {
            if (!match[2].str().empty())
                std::cout << match[1] << " " << std::stoi(match[2]) << std::endl;

            txt = match.suffix().str();
        }

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}