#pragma once 

#include <stdexcept>
#include <sstream>
#include <iostream>

namespace DELIB
{
    class Logger {
    public:
        template <typename... Args>
        static void Error(Args&&... args)
        {
            std::cerr << "\033[31m" << "ERROR: ";
            std::cerr << "\033[1m\033[30m";
            (std::cerr << ... << args);
            std::cerr << "\033[0m";
            std::cerr << std::endl;
        }

        template <typename... Args>
        static void Info(Args&&... args)
        {
            std::cout << "\033[32m" << "INFO: ";
            std::cout << "\033[1m\033[32m";
            (std::cout << ... << args);
            std::cout << "\033[0m";
            std::cout << std::endl;
        }

        template <typename... Args>
        static void Warn(Args&&... args)             
        {
            std::cout << "\033[33m" << "WARNING: ";
            std::cout << "\033[1m\033[33m";
            (std::cout << ... << args);
            std::cout << "\033[0m";
            std::cout << std::endl;
        }
    };
}
