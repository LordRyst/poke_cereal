#include "tools.h"
#include <sstream>

std::vector<std::string>* splitString(std::string in)
{
    std::stringstream ss(in);
    std::vector<std::string> words;
    std::string sub;
    while (ss.good())
    {
        getline(ss, sub, ',');
        words.push_back(sub);
    }
    std::vector<std::string>* rebuild = new std::vector<std::string>();
    bool quote = false;
    for (unsigned int i = 0; i < words.size(); i++)
    {
        if (!quote)
        {
            rebuild->push_back(words[i]);
        } else {
            (*rebuild)[rebuild->size() - 1] += "," + words[i];
        }
        if (words[i].find_first_of('\"') != std::string::npos)
        {
            quote = !quote;
        }
    }
    return rebuild;
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