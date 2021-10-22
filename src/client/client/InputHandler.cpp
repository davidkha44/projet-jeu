#include "InputHandler.hpp"
#include <string.h>

void InputHandler::RoutineMouseLeft(sf::Vector2i MousePos)
{
    for(std::function<void(sf::Vector2i)> f : MouseLeftEvents)
        f(MousePos);
}
void InputHandler::RoutineMouseRight(sf::Vector2i MousePos)
{
    for(std::function<void(sf::Vector2i)> f : MouseRightEvents)
        f(MousePos);
}


unsigned char* InputHandler::CompareSnapshots()
{
    unsigned char* output = (unsigned char*)malloc(SampleSize);
    for(int i = 0; i < SampleSize;i++)
        output[i] = (~CurrentSnapshot[i] & 1) & (PreviousSnapshot[i] ^ CurrentSnapshot[i]);
    return output;
}

unsigned char* InputHandler::RegisterKeyboardInputs()
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

void InputHandler::Initialize()
{
    SampleSize = 101;
    PreviousSnapshot = (unsigned char*)malloc(SampleSize);
    CurrentSnapshot = (unsigned char*)malloc(SampleSize);
}