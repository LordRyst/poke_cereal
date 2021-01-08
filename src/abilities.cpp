#include "abilities.h"
#include "json.hpp"
#include <fstream>
#include <set>
#include <vector>
#include "tools.h"

#define ABIL "Abilities"

using namespace nlohmann;

extern json data;

void read_abilities(std::string file_in)
{
    json abil;
    std::vector<std::string>* lines = read_file(file_in);

    if (!data.contains(ABIL))
        data[ABIL] = json::array();

    unsigned int lineNum = 0;
    while (lineNum < lines->size())
    {
        std::string line = (*lines)[lineNum];
        std::vector<std::string>* split = splitString(line);
        abil[(*split)[1]]["ID"] = stoi((*split)[0]);
        lineNum++;
    }
    data[ABIL] = abil;
}