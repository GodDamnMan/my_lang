#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <string>
#include <map>

class Simulator {
public:
    bool simulate(const std::vector<int8_t>& inputSeq, 
                 const std::vector<std::vector<std::string>>& instructions);
    
    const std::string& getErrorMessage() const { return errorMessage; }
    const std::vector<int8_t>& getOutputSeq() const { return outputSeq; }

private:
    std::string errorMessage;
    std::map<std::string, int8_t> registers;
    std::vector<int8_t> input;
    std::vector<int8_t> outputSeq;
    int32_t programCounter;

    bool executeInstruction(const std::vector<std::string>& tokens);
};

#endif // SIMULATOR_H