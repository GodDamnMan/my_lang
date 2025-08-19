#include "SolutionLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &s) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (tokenStream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

bool SolutionLoader::loadSolution(const std::string& filename, 
                                std::vector<std::vector<std::string>>& instructions) {
    std::ifstream solutionFile(filename);
    if (!solutionFile) {
        std::cerr << "Error: Unable to open solution file " << filename << std::endl;
        return false;
    }

    instructions.clear();
    
    std::string line;
    while (std::getline(solutionFile, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;
        
        std::vector<std::string> tokens = split(line);
        if (!tokens.empty()) {
            instructions.push_back(tokens);
        }
    }
    
    solutionFile.close();
    return true;
}