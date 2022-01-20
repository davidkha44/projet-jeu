#include "Pattern.h"
#include "../../client/client/Macro.hpp"
#include "../state.h"

GET_SET(engine::Pattern,std::vector<state::Actor*>,Map)


engine::Pattern::Pattern(std::vector<std::string> args)
{
    _Name = args[0];
    _ResPath = args[1];
    _Size = sf::Vector2i(std::stoi(args[2]),std::stoi(args[3]));
    int _col = 0,_lines = 0;
    Patterns[_Name] = this;
    PARSE_CSV_LINES(_ResPath,'#',

        for(std::string str : items)
        {
            switch((char)str[0])
            {
                case '1':
                {
                    std::vector<std::string> args = std::vector<std::string>();
                    args.push_back("PIECE_"+std::to_string(_col)+"_"+std::to_string(_lines));
                    args.push_back("BG_TILE_SAND");
                    args.push_back("0");args.push_back("0");args.push_back("0");args.push_back("0");args.push_back("0");
                    args.push_back("STD_ATTACK;STD_MOVE");
                    state::Actor* _m = new state::Actor(args);
                    _m->ID(0xDE000000 + (Patterns.size() << 16) + (_col << 8) + _lines);
                    _m->AssignPosition(_col,_lines);
                    _Map.push_back(_m);
                }
                break;

                case 'A':
                    _Origin = sf::Vector2i(_col,_lines);
                break;
            }
            _col++;
        }
        _col = 0;
        _lines++;
    )
    for(state::Manageable* m : _Map)
        m->AssignPosition(m->Position().x - _Origin.x,m->Position().y - _Origin.y);

}

engine::Pattern::Pattern(std::string args) 
{

}