#include "FileHandler.hpp"


#include <fstream>
#include <iostream>
#include <string.h>
#include <thread>
#include <pthread.h>


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

void FileHandler::LoadCSVFile(std::string path,int (*Callback)(std::vector<std::string>))
{
    std::ifstream file(path);
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            Callback(strs);
        }
    }
}
int FileHandler::OnLoadManagerFromCSV(std::vector<std::string> strs)
{
    Manager* mgr = new Manager(strs[0],std::stoi(strs[1]));
    mgr->Flush(false);
    if(std::stoi(strs[2]))
        mgr->Flush(true);  
    return 0;
}
int FileHandler::OnLoadVisualsFromCSV(std::vector<std::string> strs)
{
    Manager* mgr = Manager::GetMgrByName(strs[1]);
    Manageable* item = new Manageable(strs[0],std::stoi(strs[2]),strs[3]);
    mgr->Add(item);
    std::cout << "Added " << strs[0] << "to " << strs[1] << "::" << mgr->Elements()->size() << std::endl;
    sf::Vector2f _scale(std::stof(strs[4]),std::stof(strs[5]));
    item->Sprite()->setScale(_scale.x,_scale.y);
    item->Scale(_scale);
    return 0;
}

void FileHandler::InitManagers(std::string path)
{
    std::ifstream file(path);
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            Manager* mgr = new Manager(strs[0],std::stoi(strs[1]));
            mgr->Flush(false);
            if(std::stoi(strs[2]))
                mgr->Flush(true);  
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
            Manageable* item = new Manageable(strs[0],std::stoi(strs[2]),strs[3]);
            mgr->Add(item);
            std::cout << "Added " << strs[0] << "to " << strs[1] << "::" << mgr->Elements()->size() << std::endl;
            sf::Vector2f _scale(std::stof(strs[4]),std::stof(strs[5]));
            item->Sprite()->setScale(_scale.x,_scale.y);
            item->Scale(_scale);
        }
    }
}
void FileHandler::InitActors(std::string path)
{
    std::ifstream file(path);
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            Manager::GetMgrByName("ACTOR_MGR")->Add(new Actor(strs));
            Manager::GetMgrByName("ACTOR_MGR")->Add(new Actor(strs));
            Manager::GetMgrByName("ACTOR_MGR")->Add(new Actor(strs));
            Manager::GetMgrByName("ACTOR_MGR")->Add(new Actor(strs));
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
            {
                InitVisuals("src/client/tables/ManageablesVisuals.csv");
                mf = InitWorlds("src/client/tables/Worlds.csv",strs[1]);
            }
            if(strs[0] == "FLUSH_PATH")
            {
                WorldHandler::FlushPath = strs[1];
                WorldHandler::Instance = 100; 
            }
            
            
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
                WorldHandler::CurrentWorld = new World(strs[0],strs[1],std::stoi(strs[2]),std::stoi(strs[3]),std::stoi(strs[4]),std::stoi(strs[5]));
                InitWorld(strs[1],std::stoi(strs[2]),std::stoi(strs[3]),std::stoi(strs[4]),std::stoi(strs[5]));
                InitActors("src/client/tables/Actors.csv");
                mf = new MainFrame("PLT",std::stoi(strs[2]) * std::stoi(strs[4]),std::stoi(strs[3]) * std::stoi(strs[5]));    
            }
                
        }
    }
    return mf;
}

void FileHandler::InitWorld(std::string path,int csx,int csy,int ncx,int ncy)
{
    std::ifstream file(path);
    Manager* mgr = Manager::GetMgrByID(0);
    int lines = 0,col = 0;
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = SplitString(line,",");
            for(int i = 0; i < ncx;i++)
            {
                Manageable* ref = mgr->GetByID(std::stoi(strs[i]));
                Manageable* item = new Manageable("TILE_"+std::to_string(col)+"_"+std::to_string(lines),ref->Name());
                item->Sprite()->setScale(ref->Scale());
                item->Sprite()->setPosition(col*csx,lines*csy);
                item->Render(true);
                item->ID(0xFF000000 + ((col & 0xFF) << 8) + (lines & 0xFF));
                item->Position(*(new sf::Vector2i(col,lines)));
                Manager::GetMgrByID(1)->Add(item);
                col++;
            } 
        }
        col = 0;
        lines++;
        if(lines == ncy)
            return;
    }

}

