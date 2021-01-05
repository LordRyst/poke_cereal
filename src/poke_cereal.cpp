#include <string>
#include <set>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "json.hpp"
#include "pokemon.h"
#include "moves.h"

using namespace nlohmann;

json data;

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

    // std::set<std::string> all_moves;
    // for (auto& move : data["Moves"].items())
    // {
    //     all_moves.insert(move.key());
    // }
    // std::set<std::string> moves_used;
    // for(auto& specie :  data.at("Species").items())
    // {
    //     for (auto& form : specie.value().at("Forms").items())
    //     {
    //         for(json::iterator move = form.value()["Moves"].begin(); move != form.value()["Moves"].end(); move++)
    //         {
    //             //printf("%s\n", move->dump().c_str());
    //             std::string str = move.value();
    //             if (str.size() > 2 && str != "100")
    //                 moves_used.insert(str);
    //         }
    //     }
    // }
    // for(auto& specie :  data.at("Species").items())
    // {
    //     for (auto& form : specie.value().at("Forms").items())
    //     {
    //         for(json::iterator move = form.value()["EggMoves"].begin(); move != form.value()["EggMoves"].end(); move++)
    //         {
    //             //printf("%s\n", move->dump().c_str());
    //             std::string str = move.value();
    //             if (str.size() > 2 && str != "100")
    //                 moves_used.insert(str);
    //         }
    //     }
    // }

    // if (all_moves != moves_used)
    // {
    //     printf("Moves not used: ");
    //     for (auto move : all_moves)
    //     {
    //         if (!moves_used.count(move))
    //         {
    //             printf("%s, ", move.c_str());
    //         }
    //     }
    //     printf("\nMove unknown: ");
    //     for (auto move : moves_used)
    //     {
    //         if (!all_moves.count(move))
    //         {
    //             printf("%s, ", move.c_str());
    //         }
    //     }
    // }
    


    printf ("%s", data.dump(4).c_str());
}
