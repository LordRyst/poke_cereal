#include "json.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

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
    for (std::string word : in)
    {
        nums->push_back(stoi(word));
    }
    return nums;
}

void read_species(std::string inname)
{
    json species;
    std::vector<std::string> lines;
    std::ifstream infile(inname.c_str());
    copy (std::istream_iterator<std::string>(infile),
        std::istream_iterator<std::string>(),
        std::back_inserter(lines));

    if (!data.contains(SPECIES))
        data[SPECIES] = json::array();

    int lineNum = 0;
    int ID;
    std::string name;
    std::string internal;
    while (lineNum < lines.size())
    {
        std::string line = lines[lineNum];
        int eq = line.find_first_of('=');
        if (eq != std::string::npos)
        {
            std::string begin = line.substr(0, eq);
            std::string end = line.substr(eq + 1);
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
                species[name]["BaseEXP"] = end;
            }  else if (!begin.compare("BaseEXP")) {
                internal = end;
                species[name]["Forms"][internal]["Name"] = end;
            } else if (!begin.compare("Abilities")) {
                species[name]["Forms"][internal]["Abilties"] = *split;
            } else if (!begin.compare("HiddenAbility")) {
                species[name]["HiddenAbility"] = end;
            } else if (!begin.compare("Type1")) {
                species[name]["Type1"] = end;
            } else if (!begin.compare("Type2")) {
                species[name]["Type2"] = end;
            } else if (!begin.compare("Stats")) {
                std::vector<int>* nums = wordsToNum(split);
                species[name]["Stats"] = *nums;
                delete nums;
            } else if (!begin.compare("EffortPoints")) {
                std::vector<int>* nums = wordsToNum(split);
                species[name]["EV"] = *nums;
                delete nums;
            } else if (!begin.compare("Shape")) {
                species[name]["Shape"] = end;
            } else if (!begin.compare("Color")) {
                species[name]["Color"] = end;
            } else if (!begin.compare("Height")) {
                species[name]["Height"] = stof(end);
            } else if (!begin.compare("Weight")) {
                species[name]["Weight"] = stof(end);
            } else if (!begin.compare("EggMoves")) {
                species[name]["EggMoveset"] = *split;
            }
            delete split;
        } else
        {
            if (line[0] == '['){
                ID = stoi(line.substr(1, line.find_last_of(']') - 1));
            }
        }
        






 else if (!line.substr(0, keyStrings[1].size()).compare(keyStrings[1])){//Name
            name = lines[line].substr(keyStrings[1].size() + 1);
            //TODO check against species file.
            data[SPECIES][name][keyStrings[0]] = ID;
            data[SPECIES][name][keyStrings[1]] = name;
        } else if (!lines[line].substr(0, keyStrings[2].size()).compare(keyStrings[2])){//BaseEXP
            data[SPECIES][name][keyStrings[2]] = stoi(lines[line].substr(keyStrings[2].size() + 1));
        } else if (!lines[line].substr(0, keyStrings[3].size()).compare(keyStrings[3])){//GrowthRate
            data[SPECIES][name][keyStrings[3]] = lines[line].substr(keyStrings[3].size() + 1);
        } else if (!lines[line].substr(0, keyStrings[4].size()).compare(keyStrings[4])){//GenderRate
            data[SPECIES][name][keyStrings[4]] = lines[line].substr(keyStrings[4].size() + 1);
        } else if (!lines[line].substr(0, keyStrings[5].size()).compare(keyStrings[5])){//Rareness
            data[SPECIES][name]["CatchRate"] = stoi(lines[line].substr(keyStrings[5].size() + 1));
        } else if (!lines[line].substr(0, keyStrings[6].size()).compare(keyStrings[6])){//Happiness
            data[SPECIES][name][keyStrings[6]] = stoi(lines[line].substr(keyStrings[6].size() + 1));
        } else if (!lines[line].substr(0, keyStrings[7].size()).compare(keyStrings[7])){//StepsToHatch
            data[SPECIES][name][keyStrings[7]] = stoi(lines[line].substr(keyStrings[7].size() + 1));
        } else if (!lines[line].substr(0, keyStrings[8].size()).compare(keyStrings[8])){//Kind
            data[SPECIES][name][keyStrings[8]] = lines[line].substr(keyStrings[8].size() + 1);
        } else if (!lines[line].substr(0, keyStrings[9].size()).compare(keyStrings[9])){//Compatibility
            std::string comp = lines[line].substr(keyStrings[9].size() + 1);
            std::vector<std::string>* comps = splitString(comp);
            data[SPECIES][name][keyStrings[9]] = *comps;
            delete comps;
        } else if (!lines[line].substr(0, keyStrings[10].size()).compare(keyStrings[10])){//Pokedex
            data[SPECIES][name][keyStrings[10]] = lines[line].substr(keyStrings[10].size() + 1);
        } else if (!lines[line].substr(0, keyStrings[11].size()).compare(keyStrings[11])){//InternalName
            internal = lines[line].substr(keyStrings[11].size() + 1);
            data[SPECIES][name]["Forms"][internal]["Name"] = internal;
            data[SPECIES][name]["Forms"][internal]["ID"] = ID;
        }  else if (!lines[line].substr(0, keyStrings[12].size()).compare(keyStrings[12])){//Abilities
            std::string abil = lines[line].substr(keyStrings[12].size() + 1);
            std::vector<std::string>* abilities = splitString(abil);
        }
        line++;
    }
}
