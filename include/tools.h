#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <string>

std::vector<std::string>* splitString(std::string in);

std::vector<int>* wordsToNum(std::vector<std::string>* in);

std::vector<std::string>* read_file(std::string in);

#endif