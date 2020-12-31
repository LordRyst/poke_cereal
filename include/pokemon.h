#ifndef POKEMON_H
#define POKEMON_H
#include <string>
#include <vector>



std::vector<std::string>* splitString(std::string in);

std::vector<int>* wordsToNum(std::vector<std::string>* in);

void read_species(std::string inname);

#endif