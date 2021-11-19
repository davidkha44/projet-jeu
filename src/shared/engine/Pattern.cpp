#include "Pattern.h"
#include "../../client/client/Macro.hpp"
#include "../state/Manageable.h"

GET_SET(engine::Pattern,std::vector<state::Manageable*>,Map)


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
                    state::Manageable* _m = new state::Manageable("PIECE_"+std::to_string(_col)+"_"+std::to_string(_lines),"BG_TILE_SAND");
                    _m->AssignPosition(_col,_lines);
                    _Map.push_back(_m);
                    _m->ID(0xDE000000 + (Patterns.size() << 16) + (_col << 8) + _lines);
                    break;
                }

                case 'A':
                    _Origin = sf::Vector2i(_col,_lines);
                    std::cout << "ORIGIN@" << _col << "::" << _lines << std::endl;
                break;
            }
            _col++;
        }
        _col = 0;
        _lines++;
    )
    for(state::Manageable* m : _Map)
    {
        m->AssignPosition(m->Position().x - _Origin.x,m->Position().y - _Origin.y);
        std::cout << "PIECE @" << m->Position().x << "::" << m->Position().y << std::endl;
    }

}
