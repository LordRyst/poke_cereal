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
        moves[(*split)[1]]["FunctionCode"] = json::array();
        moves[(*split)[1]]["FunctionCode"].push_back(stoi((*split)[3], 0, 16));
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
        // a - The move makes physical contact with the target.
        // b - The target can use Protect or Detect to protect itself from the move.
        // c - The target can use Magic Coat to redirect the effect of the move. Use this flag if the move deals no damage but causes a negative effect on the target. (Flags c and d are mutually exclusive.)
        // d - The target can use Snatch to steal the effect of the move. Use this flag for most moves that target the user. (Flags c and d are mutually exclusive.)
        // e - The move can be copied by Mirror Move.
        // f - The move has a 10% chance of making the opponent flinch if the user is holding a King's Rock/Razor Fang. Use this flag for all damaging moves that don't already have a flinching effect.
        // g - If the user is frozen, the move will thaw it out before it is used.
        // h - The move has a high critical hit rate.
        // i - The move is a biting move (powered up by the ability Strong Jaw).
        // j - The move is a punching move (powered up by the ability Iron Fist).
        // k - The move is a sound-based move.
        // l - The move is a powder-based move (Grass-type Pokémon are immune to them).
        // m - The move is a pulse-based move (powered up by the ability Mega Launcher).
        // n - The move is a bomb-based move (resisted by the ability Bulletproof).
        if (fstring.find('a') != std::string::npos) flags.push_back("PhysicalContact");
        if (fstring.find('b') != std::string::npos) flags.push_back("TargetProtectable");
        if (fstring.find('c') != std::string::npos) flags.push_back("MagicCoatable");
        if (fstring.find('d') != std::string::npos) flags.push_back("Snatchable");
        if (fstring.find('e') != std::string::npos) flags.push_back("MirrorMoveable");
        if (fstring.find('f') != std::string::npos) flags.push_back("DamageFlinch");
        if (fstring.find('g') != std::string::npos) flags.push_back("ThawUser");
        if (fstring.find('h') != std::string::npos) flags.push_back("HighCrit");
        if (fstring.find('i') != std::string::npos) flags.push_back("BiteMove");
        if (fstring.find('j') != std::string::npos) flags.push_back("PunchMove");
        if (fstring.find('k') != std::string::npos) flags.push_back("SoundMove");
        if (fstring.find('l') != std::string::npos) flags.push_back("PowderMove");
        if (fstring.find('m') != std::string::npos) flags.push_back("PulseMove");
        if (fstring.find('n') != std::string::npos) flags.push_back("Bombmove");
        moves[(*split)[1]]["Flags"] = flags;
        moves[(*split)[1]]["Description"] = (*split)[13];
        lineNum++;
    }
    data[MOVES] = moves;
}