#include "Simulator.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool Simulator::simulate(const std::vector<int8_t>& inputSeq, 
                        const std::vector<std::vector<std::string>>& instructions) {
    // Reset state
    registers.clear();
    outputSeq.clear();
    errorMessage.clear();
    registers.clear();
    programCounter = 1;
    input = inputSeq;
    

    for (;programCounter < instructions.size() + 1; programCounter++) {
        const auto& tokens = instructions[programCounter - 1];
        if (!executeInstruction(tokens)) {
            return false;
        }
    }
    
    return true;
}

bool Simulator::executeInstruction(const std::vector<std::string>& tokens) {
    if (tokens.empty()) return true;
    
    std::string op = tokens[0];

    if (op == "input") {
        if (tokens.size() != 2) {
            errorMessage = "Error: Invalid input instruction";
            return false;
        }
        if (input.empty()) {
            errorMessage = "Error: No more input available";
            return false;
        }
        registers[tokens[1]] = input[0];
        input.erase(input.begin());
    } 
    else if (op == "output") {
        if (tokens.size() != 2) {
            errorMessage = "Error: Invalid output instruction";
            return false;
        }
        outputSeq.push_back(registers[tokens[1]]);
    } 
    else if (op == "bumpp") {
        if (tokens.size() != 2) {
            errorMessage = "Error: Invalid bumpp instruction";
            return false;
        }
        registers[tokens[1]]++;
    } 
    else if (op == "bumpm") {
        if (tokens.size() != 2) {
            errorMessage = "Error: Invalid bumpm instruction";
            return false;
        }
        if (registers[tokens[1]] == 0) {
            errorMessage = "Error: Cannot decrement zero";
            return false;
        }
        registers[tokens[1]]--;
    } 
    else if (op == "copy") {
        if (tokens.size() != 3) {
            errorMessage = "Error: Invalid copy instruction";
            return false;
        }
        registers[tokens[2]] = registers[tokens[1]];
    } 
    else if (op == "add") {
        if (tokens.size() != 3) {
            errorMessage = "Error: Invalid add instruction";
            return false;
        }
        registers[tokens[2]] += registers[tokens[1]];
    } 
    else if (op == "sub") {
        if (tokens.size() != 3) {
            errorMessage = "Error: Invalid sub instruction";
            return false;
        }
        if (registers[tokens[1]] > registers[tokens[2]]) {
            errorMessage = "Error: Subtraction would result in negative";
            return false;
        }
        registers[tokens[2]] -= registers[tokens[1]];
    } 
    else if (op == "jump") {
        if (tokens.size() != 2) {
            errorMessage = "Error: Invalid jump instruction";
            return false;
        }
        programCounter = atoi(tokens[1].c_str()) - 1;
    } 
    else if (op == "jumpz") {
        if (tokens.size() != 3) {
            errorMessage = "Error: Invalid jumpz instruction";
            return false;
        }
        if (registers[tokens[1]] == 0)
            programCounter = atoi(tokens[2].c_str()) - 1;
    } 
    else if (op == "jumpnz") {
        if (tokens.size() != 3) {
            errorMessage = "Error: Invalid jumpnz instruction";
            return false;
        }
        if (registers[tokens[1]] != 0)
            programCounter = atoi(tokens[2].c_str()) - 1;
    } 
    else {
        errorMessage = "Error: Unknown instruction " + op;
        return false;
    }
    


    if (true){
        std::cout << "Command number is " << programCounter << std::endl;
        std::cout << "Command: ";

        for (auto &i : tokens) 
            std::cout << i << " ";
        std::cout << std::endl;
        
    
        for (auto variable = registers.begin(); variable != registers.end(); variable++)
            std::cout << variable->first << ':' << static_cast<int>(variable->second) << std::endl;
        std::cout << "-------------" << std::endl;       
        std::cin.ignore();
    }

    return true;
}