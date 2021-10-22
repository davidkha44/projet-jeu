#include "Macro.hpp"
#include <SFML/Graphics.hpp>
#include <functional>


class InputHandler
{
    STATIC(unsigned char* PreviousSnapshot)
    STATIC(unsigned char* CurrentSnapshot)
    STATIC(int SampleSize)
    STATIC(std::vector<std::function<void(sf::Vector2i)>> MouseLeftEvents)
    STATIC(std::vector<std::function<void(sf::Vector2i)>> MouseRightEvents)
    STATIC(std::vector<std::function<void(sf::Keyboard::Key)>> KeyboardEvents)

    public :
        template <class T> 
        static void RegisterMouseLeftEvent();
        template <class T> 
        static void RegisterMouseRightEvent();
        template <class T> 
        static void RegisterKeyboardEvent();

        static void RoutineMouseLeft(sf::Vector2i MousePos);
        static void RoutineMouseRight(sf::Vector2i MousePos);
        static void RoutineKeybboard(sf::Keyboard::Key k);


        static unsigned char* CompareSnapshots();
        static unsigned char* RegisterKeyboardInputs();
        static void Initialize();
};
template <class T>
void InputHandler::RegisterMouseLeftEvent()
{
    MouseLeftEvents.push_back(T::OnMouseLeft);
}
template <class T>
void InputHandler::RegisterMouseRightEvent()
{
    MouseRightEvents.push_back(T::OnMouseRight);
}
