#include <iostream>
#include <vector>
#include <string>
#include "LevelLoader.h"
#include "SolutionLoader.h"
#include "Simulator.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " level solution" << std::endl;
        return 1;
    }

    // Load level file
    std::vector<int8_t> inputSeq, expectedOutput;
    if (!LevelLoader::loadLevel(argv[1], inputSeq, expectedOutput)) {
        return 1;
    }

    // Load solution file
    std::vector<std::vector<std::string>> instructions;
    if (!SolutionLoader::loadSolution(argv[2], instructions)) {
        return 1;
    }

    // Simulate the program
    Simulator simulator;
    if (!simulator.simulate(inputSeq, instructions)) {
        std::cerr << simulator.getErrorMessage() << std::endl;
        std::cerr << "Simulation failed." << std::endl;
        return 1;
    }

    std::vector<int8_t> actualOutput = simulator.getOutputSeq();

    // Compare outputs
    if (actualOutput.size() != expectedOutput.size()) {
        std::cerr << "Output size mismatch: expected " 
                  << expectedOutput.size() << ", got " 
                  << actualOutput.size() << std::endl;
        return 1;
    }

    for (size_t i = 0; i < expectedOutput.size(); i++) {
        if (actualOutput[i] != expectedOutput[i]) {
            std::cerr << "Output mismatch at position " << i 
                      << ": expected " << expectedOutput[i] 
                      << ", got " << actualOutput[i] << std::endl;
            return 1;
        }
    }

    std::cout << "Success! Output matches." << std::endl;
    return 0;
}