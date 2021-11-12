#include "FileHandler.h"
#include "MainFrame.h"
#include "../../shared/state.h"
#include "../../client/client/Macro.hpp"


#include <fstream>
#include <iostream>
#include <string.h>
#include <thread>
#include <pthread.h>

std::vector<std::string> render::FileHandler::SplitString(std::string str,std::string separator)
{
    size_t pos_start = 0, pos_end, delim_len = separator.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = str.find (separator, pos_start)) != std::string::npos) {
        token = str.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (str.substr (pos_start));
    return res;
}

render::MainFrame* render::FileHandler::LoadLaunchArgs (std::string path)
{
    render::MainFrame* mf;
    PARSE_CSV_LINES(path,'#',

    if(!strcmp(items[0].c_str(),"SCENE"))
    {
        std::vector<state::World*> _wrld = DeserializeTable<state::World>("src/client/tables/Worlds.csv","CSV");
        std::cout << "OUT :" << _wrld.size() << std::endl;
        for(state::World* w : _wrld)
        {
            if(w->Name() == items[1])
            {
                std::cout << "WORLD : " << w->Name() << std::endl;
                state::WorldHandler::CurrentWorld = w;
                mf = new render::MainFrame("PLT",w->CellN().y*w->CellSize().y,w->CellN().x*w->CellSize().x);
            }
        }
    }
    
    )
    return mf;
}

template <class T>
std::vector<T*> render::FileHandler::DeserializeTable(std::string path, std::string format)
{   
    std::vector<T*> Output;
    if(format == "CSV")
    {
        std::ifstream file(path);
        for( std::string line; getline( file, line ); )
        {
            if(line.find('#') == std::string::npos)
            {
                std::vector<std::string> strs = SplitString(line,",");
                Output.push_back(new T(strs));
            }
        }  
    }
    return Output;
}
template std::vector<state::Manager*> render::FileHandler::DeserializeTable<state::Manager>(std::string path, std::string format);
template std::vector<state::Manageable*> render::FileHandler::DeserializeTable<state::Manageable>(std::string path, std::string format);
template std::vector<state::World*> render::FileHandler::DeserializeTable<state::World>(std::string path, std::string format);
template std::vector<state::Actor*> render::FileHandler::DeserializeTable<state::Actor>(std::string path, std::string format);
