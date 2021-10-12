#include "FileHandler.hpp"
#include "Manager.hpp"
#include "Manageable.hpp"
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
            item->Sprite()->setScale(std::stof(strs[3]),std::stof(strs[4]));
            mgr->Add(item);
        }
    }

}
void FileHandler::InitWorld(std::string path)
{
    std::ifstream file(path);
    Manager* mgr = Manager::GetMgrByName("BG_MGR");
    int lines = 0,col = 0;
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            for(std::string s : strs)
            {
                Manageable* item = new Manageable("TILE_"+std::to_string(lines)+"_"+std::to_string(col),"/home/ensea/PLT/projet-jeu/res/bridge.png");
                item->Sprite()->setScale(0.5,0.5);
                item->Sprite()->setPosition(col*40,lines*40);
                item->Render(true);
                mgr->Add(item);
                col++;
            } 
        }
        col = 0;
        lines++;
    }

}

