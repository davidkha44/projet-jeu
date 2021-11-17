#include "InputHandler.h"
#include "SelectionHandler.h"
#include "../../client/client/Macro.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>

EVENT(engine::InputHandler,MouseLeft,engine::SelectionHandler)
EVENT(engine::InputHandler,MouseRight,engine::SelectionHandler)


template <class T>
void engine::InputHandler::RegisterMouseLeftEvents()
{
    MouseLeftEvents.push_back(T::OnMouseLeft);
}
template <class T>
void engine::InputHandler::RegisterMouseRightEvents()
{
    MouseRightEvents.push_back(T::OnMouseRight);
}

void engine::InputHandler::RoutineMouseLeft (int x,int y)
{
    for(std::function<void(int,int)> f : MouseLeftEvents)
        f(x,y);
}
void engine::InputHandler::RoutineMouseRight(int x,int y)
{
    for(std::function<void(int,int)> f : MouseRightEvents)
        f(x,y);
}


unsigned char* engine::InputHandler::CompareSnapshots()
{
    unsigned char* output = (unsigned char*)malloc(SampleSize);
    for(int i = 0; i < SampleSize;i++)
        output[i] = (~CurrentSnapshot[i] & 1) & (PreviousSnapshot[i] ^ CurrentSnapshot[i]);
    return output;
}

unsigned char* engine::InputHandler::RegisterInputs()
{
    memcpy(PreviousSnapshot,CurrentSnapshot,SampleSize);
    for(int i = 0; i < SampleSize;i++)
    {
        CurrentSnapshot[i] = 0;
        ON_KEY_ENUM(i,
        CurrentSnapshot[i] = 1;
        )
    }
    return CompareSnapshots();
}

void engine::InputHandler::Initialize()
{
    SampleSize = 101;
    PreviousSnapshot = (unsigned char*)malloc(SampleSize);
    CurrentSnapshot = (unsigned char*)malloc(SampleSize);
    RegisterMouseLeftEvents<engine::SelectionHandler>();
    RegisterMouseRightEvents<engine::SelectionHandler>();
}

