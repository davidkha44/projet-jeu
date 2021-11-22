#include "InputHandler.h"
#include "SelectionHandler.h"
#include "../state.h"
#include "../../client/client/Macro.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>

EVENT(engine::InputHandler,MouseLeft,engine::SelectionHandler)
EVENT(engine::InputHandler,MouseRight,engine::SelectionHandler)
EVENT(engine::InputHandler,Keyboard,state::Actor)


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
template <class T>
void engine::InputHandler::RegisterKeyboardEvents()
{
    KeyboardEvents.push_back(T::OnKey);
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
void engine::InputHandler::RoutineKey(unsigned char* snapshot)
{
    for(std::function<void(unsigned char*)> f : KeyboardEvents)
        f(snapshot);
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
    RegisterKeyboardEvents<state::Actor>();
}

