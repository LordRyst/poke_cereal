#include "json.hpp"
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include "pokemon.h"

#define SPECIES "Species"

using namespace nlohmann;

extern json data;

std::vector<std::string>* splitString(std::string in)
{
    std::stringstream ss(in);
    std::vector<std::string>* words = new std::vector<std::string>();
    while (ss.good())
    {
        std::string sub;
        getline(ss, sub, ',');
        words->push_back(sub);
    }
    return words;
}

std::vector<int>* wordsToNum(std::vector<std::string>* in)
{
    std::vector<int>* nums = new std::vector<int>();
    for (std::vector<std::string>::iterator word = in->begin(); word != in->end(); word++)
    {
        nums->push_back(stoi(*word));
    }
    return nums;
}

void read_species(std::string inname)
{
    json species;
    std::vector<std::string> lines;
    std::ifstream infile(inname.c_str());
    std::string line;
    while (std::getline(infile, line))
    {
    lines.push_back(line);
    }

    // copy (std::istream_iterator<std::string>(infile),
    //     std::istream_iterator<std::string>(),
    //     std::back_inserter(lines));

    if (!data.contains(SPECIES))
        data[SPECIES] = json::array();

    unsigned int lineNum = 0;
    unsigned int ID = 0;
    std::string name;
    std::string internal;
    std::set<std::string> missingKeys;
    std::set<std::string> missingEvo;
    while (lineNum < lines.size())
    {
        std::string line = lines[lineNum];
        long unsigned int eq = line.find_first_of('=');
        if (eq != std::string::npos)
        {
            std::string begin = line.substr(0, eq);
            std::string end = line.substr(eq + 1);
            //fprintf(stderr, "%d, %s\n", lineNum, line.c_str());
            std::vector<std::string>* split = splitString(end);
            if (!begin.compare("Name")) {
                name = end;
                species[name]["Name"] = end;
                species[name]["ID"] = ID;
            } else if (!begin.compare("BaseEXP")) {
                species[name]["BaseEXP"] = stoi(end);
            } else if (!begin.compare("GrowthRate")) {
                species[name]["GrowthRate"] = end;
            } else if (!begin.compare("GenderRate")) {
                species[name]["GenderRate"] = end;
            } else if (!begin.compare("Rareness")) {
                species[name]["CatchRate"] = stoi(end);
            } else if (!begin.compare("Happiness")) {
                species[name]["Happiness"] = stoi(end);
            } else if (!begin.compare("StepsToHatch")) {
                species[name]["StepsToHatch"] = stoi(end);
            } else if (!begin.compare("Kind")) {
                species[name]["Kind"] = end;
            } else if (!begin.compare("Compatibility")) {
                species[name]["Compatibility"] = *split;
            } else if (!begin.compare("Pokedex")) {
                species[name]["Pokedex"] = end;
            } else if (!begin.compare("InternalName")) {
                internal = end;
                species[name]["Forms"][internal]["Name"] = end;
            } else if (!begin.compare("Abilities")) {
                species[name]["Forms"][internal]["Abilties"] = *split;
            } else if (!begin.compare("HiddenAbility")) {
                species[name]["Forms"][internal]["HiddenAbility"] = end;
            } else if (!begin.compare("Moves")) {
                species[name]["Forms"][internal]["Moves"] = *split;
            } else if (!begin.compare("Type1")) {
                species[name]["Forms"][internal]["Type1"] = end;
            } else if (!begin.compare("Type2")) {
                species[name]["Forms"][internal]["Type2"] = end;
            } else if (!begin.compare("BaseStats")) {
                std::vector<int>* nums = wordsToNum(split);
                species[name]["Forms"][internal]["Stats"] = *nums;
                delete nums;
            } else if (!begin.compare("EffortPoints")) {
                std::vector<int>* nums = wordsToNum(split);
                species[name]["EV"] = *nums;
                delete nums;
            } else if (!begin.compare("Shape")) {
                species[name]["Forms"][internal]["Shape"] = end;
            } else if (!begin.compare("Color")) {
                species[name]["Forms"][internal]["Color"] = end;
            } else if (!begin.compare("Height")) {
                species[name]["Forms"][internal]["Height"] = stof(end);
            } else if (!begin.compare("Weight")) {
                species[name]["Forms"][internal]["Weight"] = stof(end);
            } else if (!begin.compare("EggMoves")) {
                species[name]["Forms"][internal]["EggMoveset"] = *split;
            } else if (!begin.compare("WildItemCommon")) {
                species[name]["Forms"][internal]["WildItem"][0] = end;
            } else if (!begin.compare("WildItemUncommon")) {
                species[name]["Forms"][internal]["WildItem"][1] = end;
            } else if (!begin.compare("WildItemRare")) {
                species[name]["Forms"][internal]["WildItem"][2] = end;
            } else if (!begin.compare("Evolutions")) {
                std::string evo;
                for (unsigned int i = 1; i < split->size(); i++)
                {
                    evo = (*split)[0];
                    if (!(*split)[i].compare("Level"))
                    {
                        species[name]["Forms"][internal]["Evolutions"][evo]["Level"] = stoi((*split)[++i]);
                        i++;
                    } else if (!(*split)[i].compare("Item")) {
                        species[name]["Forms"][internal]["Evolutions"][evo]["Item"] = (*split)[++i];
                        i++;
                    } else {
                        missingEvo.insert((*split)[i]);
                    }
                }
                species[name]["Forms"][internal]["Evolutions"] = end;
            } else {
                missingKeys.insert(begin);
            }
            delete split;
        } else
        {
            if (line[0] == '['){
                ID = stoi(line.substr(1, line.find_last_of(']') - 1));
            }
        }
        lineNum++;
    }
    // for (std::set<std::string>::iterator it = missingKeys.begin(); it != missingKeys.end(); it++)
    // {
    //     printf("Unknown Key: %s\n", it->c_str());
    // }
    // for (std::set<std::string>::iterator it = missingEvo.begin(); it != missingEvo.end(); it++)
    // {
    //     printf("Unknown Evo: %s\n", it->c_str());
    // }

    printf ("%s", species.dump(4).c_str());
}