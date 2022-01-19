#include "Tree.h"
#include "../../client/client/Macro.hpp"
#include "../state.h"




ai::Tree::Tree()
{

}

ai::Tree::Tree(ai::Node* root)
{
    Root = root;  
}

std::vector<ai::Node*> ai::Tree::Children(int depth)
{
    ai::Node* currentNode = Root;
}

std::vector<ai::Node*> ai::Tree::Level(int lvl)
{
    std::vector<ai::Node*> output;
    
    if(!lvl) output.push_back(Root);
    else
    {
        int _lvl = (lvl < 0 ) ? -1 * lvl : lvl;
        std::vector<ai::Node*> nodes2iterate;
        nodes2iterate.push_back(Root);
        do
        {
            output.clear();
            for(ai::Node* node : nodes2iterate)
                VECTOR_CONCAT(output,node->Children);
            nodes2iterate = std::vector<ai::Node*>(output);
        }while (--_lvl);
    }
    return output;
}

int ai::Tree::Level()
{
    int level = -1;
    while(Level(level++).size());
    return --level;
}





