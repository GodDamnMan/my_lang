#include "LevelLoader.h"
#include <fstream>
#include <iostream>
#include <string>

bool LevelLoader::loadLevel(const std::string& filename, 
                           std::vector<int8_t>& inputSeq, 
                           std::vector<int8_t>& outputSeq) {
    std::ifstream levelFile(filename);
    if (!levelFile) {
        std::cerr << "Error: Unable to open level file " << filename << std::endl;
        return false;
    }

    inputSeq.clear();
    outputSeq.clear();
    
    std::string line;
    bool readingInput = true;
    while (std::getline(levelFile, line)) {
        if (line.compare("---") == 1) {
            readingInput = false;
            continue;
        }

        size_t pos = line.find('#');
        if (pos != std::string::npos) {
            line.erase(pos);
        }

        try {
            if (readingInput) {
                inputSeq.push_back(std::stoi(line));
            } else {
                outputSeq.push_back(std::stoi(line));
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid number format in level file: " << line << std::endl;
            return false;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Number out of range in level file: " << line << std::endl;
            return false;
        }
    }
    
    levelFile.close();
    return true;
}