#include "WorldHandler.hpp"

void WorldHandler::OnTurnBegin()
{
    ++Turn %= Players->size();
}