#include "MainFrame.hpp"
#include "SelectionHandler.hpp"
#include "InputHandler.hpp"
#include <iostream>

MainFrame::MainFrame(std::string name, int h, int w)
{
    Height(h);
    Width(w);
    sf::VideoMode frame_vm(Height(), Width());
    sf::RenderWindow win(frame_vm, name, sf::Style::Default);
    MainFrame::Window = &win;

}

void MainFrame::OnStart()
{
    InputHandler::Initialize();
        while (MainFrame::Window->isOpen())
    {
        sf::Event event;
        MainFrame::Window->clear(sf::Color::Black);
        Draw();
        if (MainFrame::Window->hasFocus())
            Tick();

        while (Window->pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                Window->close();
        }
        MainFrame::Window->display();
    }
}
void MainFrame::Draw()
{
    for (int i = 0; i < Manager::Managers.size(); i++)
        Manager::GetMgrByID(i)->Draw(MainFrame::Window);
}

void MainFrame::Tick()
{

    ON_MOUSE_LEFT(
        //SelectionHandler::Add(BG_TILE(SelectionHandler::GetBGWpos(MousePos).x,SelectionHandler::GetBGWpos(MousePos).y));
        InputHandler::RoutineMouseLeft(MousePos);)
    ON_MOUSE_RIGHT(
        InputHandler::RoutineMouseRight(MousePos);)

    ON_KEY_DBG(X,
               printf("Close Game !");
               MainFrame::Window->close();)
    unsigned char *buffer = InputHandler::RegisterKeyboardInputs();
    if (buffer[sf::Keyboard::M])
    {
        Handler::RoutineTurnBegin();
        Handler::RoutineTurnBeginAsync();
    }
    if (buffer[sf::Keyboard::Z])
    {
        for (Manageable *m : SelectionHandler::Selection)
        {
            if (Manager::GetMgrByName("ACTOR_MGR")->PartOf(m))
            {
                int px = m->Position().x;
                int py = m->Position().y;
                py--;
                RANGE(py, 0, WorldHandler::CurrentWorld->CellN().y)
                m->AssignPosition(px, py);
            }
        }
    }
    if (buffer[sf::Keyboard::S])
    {
        for (Manageable *m : SelectionHandler::Selection)
        {
            if (Manager::GetMgrByName("ACTOR_MGR")->PartOf(m))
            {
                int px = m->Position().x;
                int py = m->Position().y;
                py++;
                RANGE(py, 0, WorldHandler::CurrentWorld->CellN().y)
                m->AssignPosition(px, py);
            }
        }
    }
    if (buffer[sf::Keyboard::Q])
    {
        for (Manageable *m : SelectionHandler::Selection)
        {
            if (Manager::GetMgrByName("ACTOR_MGR")->PartOf(m))
            {
                int px = m->Position().x;
                int py = m->Position().y;
                px--;
                RANGE(px, 0, WorldHandler::CurrentWorld->CellN().x)
                m->AssignPosition(px, py);
            }
        }
    }
    if (buffer[sf::Keyboard::D])
    {
        for (Manageable *m : SelectionHandler::Selection)
        {
            if (Manager::GetMgrByName("ACTOR_MGR")->PartOf(m))
            {
                int px = m->Position().x;
                int py = m->Position().y;
                px++;
                RANGE(px, 0, WorldHandler::CurrentWorld->CellN().x)
                m->AssignPosition(px, py);
            }
        }
    }
    free(buffer);
}