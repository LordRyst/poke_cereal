#include "moves.h"
#include "json.hpp"
#include <fstream>
#include <set>
#include <vector>
#include "tools.h"

#define MOVES "Moves"

using namespace nlohmann;

extern json data;

void read_moves(std::string moves_in)
{
    json moves;
    std::vector<std::string> lines;
    std::ifstream infile(moves_in.c_str());
    std::string line;
    while (std::getline(infile, line))
    {
        if (line[line.size() - 1] == '\r')
        {
            line.pop_back();
        }
        if (line.size() > 10)
            lines.push_back(line);
    }


    if (!data.contains(MOVES))
        data[MOVES] = json::array();

    unsigned int lineNum = 0;
    while (lineNum < lines.size())
    {
        std::string line = lines[lineNum];
        std::vector<std::string>* split = splitString(line);
        moves[(*split)[1]]["ID"] = stoi((*split)[0]);
        moves[(*split)[1]]["DisplayName"] = (*split)[2];
        moves[(*split)[1]]["FunctionCode"] = stoi((*split)[3], 0, 16);
        moves[(*split)[1]]["BasePower"] = stoi((*split)[4]);
        moves[(*split)[1]]["Type"] = (*split)[5];
        moves[(*split)[1]]["Category"] = (*split)[6];
        moves[(*split)[1]]["Accuracy"] = stoi((*split)[7]);
        moves[(*split)[1]]["TotalPP"] = stoi((*split)[8]);
        moves[(*split)[1]]["EffectChance"] = stoi((*split)[9]);
        int target = stoi((*split)[10]);
        std::string text;
        switch(target)
        {
            case 0: text = "SingleOther";break;
            case 1: text = "NoTarget";break;
            case 2: text = "SingleOppRand";break;
            case 4: text = "AllOpp";break;
            case 8: text = "AllOther";break;
            case 10: text = "User";break;
            case 20: text = "BothSides";break;
            case 40: text = "UserSide";break;
            case 80: text = "OpposingSide";break;
            case 100: text = "UserPartner";break;
            case 200: text = "SingleAlly";break;
            case 400: text = "SingleOpp";break;
            case 800: text = "SingleDirectOpp";break;
        }
        moves[(*split)[1]]["Target"] = target;
        moves[(*split)[1]]["Priority"] = stoi((*split)[11]);
        std::string fstring = (*split)[12];
        json flags;
        if (fstring.find('a') != std::string::npos) flags.push_back("PhysicalContact");
        moves[(*split)[1]]["Flags"] = flags;
        moves[(*split)[1]]["Description"] = stoi((*split)[13]);
        lineNum++;
    }
    data[MOVES] = moves;
    printf ("%s", moves.dump(4).c_str());
}