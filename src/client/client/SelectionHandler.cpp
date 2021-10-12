#include "SelectionHandler.hpp"

SelectionHandler::SelectionHandler() : Handler("Selection Handler")
{
    Selection(*(new std::vector<Manageable>));
}

void SelectionHandler::Add(Manageable m)
{
    Selection().push_back(m);
}

void SelectionHandler::OnTurnBegin()
{
    *this = *(new SelectionHandler());
}

// sf::Vector2i GetBGWpos(sf::Vector2i uv)
// {
//     sf::Vector2i output(uv.x/20,uv.y/20);

//     return output;
// }