#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <vector>
#include <string>

class LevelLoader {
public:
    static bool loadLevel(const std::string& filename, 
                         std::vector<int8_t>& inputSeq, 
                         std::vector<int8_t>& outputSeq);
};

#endif // LEVEL_LOADER_H