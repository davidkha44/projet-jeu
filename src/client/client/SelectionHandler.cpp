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