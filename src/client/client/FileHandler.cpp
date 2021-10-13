#include "FileHandler.hpp"
#include "Manager.hpp"

#include <fstream>
#include <iostream>


std::vector<std::string> FileHandler::SplitString(std::string str,std::string separator)
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

void FileHandler::InitManagers(std::string path)
{
    std::ifstream file(path);
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            Manager* mgr = new Manager(strs[0]);
        }
    }

}
void FileHandler::InitVisuals(std::string path)
{
    std::ifstream file(path);
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            Manager* mgr = Manager::GetMgrByName(strs[1]);
            std::cout << "Added" << strs[0] << "to " << strs[1] << std::endl;
            Manageable* item = new Manageable(strs[0],strs[2]);
            sf::Vector2f _scale(std::stof(strs[3]),std::stof(strs[4]));
            item->Sprite()->setScale(_scale.x,_scale.y);
            item->Scale(_scale);
            mgr->Add(item);
        }
    }

}
void FileHandler::InitArgs(MainFrame* mf,std::string path)
{
    std::ifstream file(path);
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            if(strs[0] == "SCENE")
                mf = InitWorlds("/home/ensea/PLT/projet-jeu/src/client/tables/Worlds.csv",strs[1]);

            
        }
    }

}

MainFrame* FileHandler::InitWorlds(std::string path,std::string wname)
{
    MainFrame* mf;
    std::ifstream file(path);
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            if(strs[0] == wname)
            {
                InitWorld(strs[1],std::stoi(strs[2]),std::stoi(strs[3]),std::stoi(strs[4]),std::stoi(strs[5]));
                mf = new MainFrame("PLT",std::stoi(strs[2]) * std::stoi(strs[4]),std::stoi(strs[3]) * std::stoi(strs[5]));    
            }
                
        }
    }
    return mf;
}

void FileHandler::InitWorld(std::string path,int csx,int csy,int ncx,int ncy)
{
    std::ifstream file(path);
    Manager* mgr = Manager::GetMgrByName("BG_MGR");
    int lines = 0,col = 0;
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            for(int i = 0; i < ncx;i++)
            {
                std::string respath,bg_tile_str;
                switch(std::stoi(strs[i]))
                {
                    case 1 :
                        bg_tile_str = "WATER";
                    break;
                    case 2 :
                        bg_tile_str = "BRIDGE";
                    break;
                    default :
                        bg_tile_str = "GRASS";
                    break;
                }
                respath = Manager::GetMgrByName("BG_MGR")->GetByName("BG_TILE_"+bg_tile_str)->front()->ResPath();
                Manageable* item = new Manageable("TILE_"+std::to_string(col)+"_"+std::to_string(lines),respath);
                item->Sprite()->setScale(FETCH_FROM_MGR("BG_MGR","BG_TILE_"+bg_tile_str)->front()->Scale());
                item->Sprite()->setPosition(col*csx,lines*csy);
                item->Render(true);
                mgr->Add(item);
                col++;
            } 
        }
        col = 0;
        lines++;
        if(lines == ncy)
            return;
    }

}

