#include "FileHandler.h"
#include "MainFrame.h"
#include "../../shared/state.h"
#include "../../shared/engine.h"
#include "../../client/client/Macro.hpp"


#include <fstream>
#include <iostream>
#include <string.h>
#include <thread>
#include <pthread.h>

std::vector<std::string> render::FileHandler::SplitString(std::string str,std::string separator)
{
    //Utile pour casser une chaine de caractères
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
    //Charge et parcours le fichiers de configuration LaunchArgs.csv
    render::MainFrame* mf;
    PARSE_CSV_LINES(path,'#',

    if(!strcmp(items[0].c_str(),"SCENE"))
    {
        for(state::World* w : DeserializeTable<state::World>("src/client/tables/Worlds.csv","CSV"))
        {
            if(w->Name() == items[1])
            {
                std::cout << "WORLD : " << w->Name() << std::endl;
                state::WorldHandler::CurrentWorld = w;
                mf = new render::MainFrame("PLT",w->CellN().x*w->CellSize().x,w->CellN().y*w->CellSize().y);
            }
        }
    }
    
    )
    return mf;
}

template <class T>
std::vector<T*> render::FileHandler::DeserializeTable(std::string path, std::string format)
{   
    //Déserialise une classe en objet de classe T
    // Utile pour transformer une table en objets
    // Retourne la liste des objets créés si on souhaite les utiliser
    // La classe T doit posséder un constructeur T(std::vector<std::string>) pour être déserialisable
    std::vector<T*> Output;
    if(format == "CSV")
    {
        PARSE_CSV_LINES(path,'#',
            Output.push_back(new T(SplitString(line,",")));
        )
    }
    return Output;
}
DESERIALIZE(state::Manager)
DESERIALIZE(state::Manageable)
DESERIALIZE(state::World)
DESERIALIZE(state::Actor)
DESERIALIZE(engine::Pattern)
DESERIALIZE(engine::Action)
