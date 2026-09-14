#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

inline std::string GetDataFromFile(const std::string& filepath)
{
    std::ifstream file (filepath);
    if(!file)
    {
        std::cerr<<"Couldn't open file: " + filepath + "\n";
    }
    std::stringstream stream;
    stream<<file.rdbuf();
    return stream.str();
}

inline std::vector<std::string> ReadLinesFromFile(const std::string& filepath)
{
    std::ifstream file (filepath);
    if(!file)
    {
        std::cerr<<"Couldn't open file: " + filepath + "\n";
    }
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}