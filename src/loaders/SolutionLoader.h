#ifndef SOLUTION_LOADER_H
#define SOLUTION_LOADER_H

#include <vector>
#include <string>

class SolutionLoader {
public:
    static bool loadSolution(const std::string& filename, 
                            std::vector<std::vector<std::string>>& instructions);
};

#endif // SOLUTION_LOADER_H