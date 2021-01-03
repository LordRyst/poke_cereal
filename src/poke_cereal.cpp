#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "json.hpp"
#include "pokemon.h"
#include "moves.h"

nlohmann::json data;

int main(int argc, char* argv[])
{
    std::string pokemon_in;
    std::string abilities_in;
    std::string moves_in;
    std::string items_in;
    std::string output;

    int opt;
    while ((opt = getopt (argc, argv, "p:am:io:")) != EOF)
    {
        switch (opt)
        {
            case 'p':
                pokemon_in = std::string(optarg);
                break;
            case 'a':
                abilities_in = std::string(optarg);
                break;
            case 'm':
                moves_in = std::string(optarg);
                break;
            case 'i':
                items_in = std::string(optarg);
                break;
            case 'o':
                output = std::string(optarg);
                break;
        }
    }

    if (!abilities_in.empty())
    {
        //read_abilities(abilities_in);
    }

    read_moves(moves_in);

    read_species(pokemon_in);

    //print_json(output);
}
