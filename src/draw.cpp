#include "cellPlane.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace
{
    static const size_t GRID_SIZE = 20;
    static uint8_t SQUARE_SIZE = 20;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode((1 + GRID_SIZE) * SQUARE_SIZE, (1 + GRID_SIZE) * SQUARE_SIZE), "SFML works!");
    window.setVerticalSyncEnabled(true);

    CellPlane cells(GRID_SIZE, SQUARE_SIZE, sf::Color::Cyan, sf::Color(0, 255, 0, 32), sf::Color::Black, sf::Color(255, 255, 255, 32));

    bool gameOn = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    gameOn = !gameOn;
                    cells.showGrid(!gameOn);
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;
                else
                    std::cout << "wheel type: unknown" << std::endl;
                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
                SQUARE_SIZE += event.mouseWheelScroll.delta;
                cells.setCellSize(SQUARE_SIZE);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    std::cout << "the middle button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was released" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    size_t x = event.mouseButton.x / SQUARE_SIZE;
                    size_t y = event.mouseButton.y / SQUARE_SIZE;
                    if (x < GRID_SIZE && y < GRID_SIZE)
                    {
                        cells.setDead(x, y);
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    std::cout << "the middle button was released" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was released" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    size_t x = event.mouseButton.x / SQUARE_SIZE;
                    size_t y = event.mouseButton.y / SQUARE_SIZE;
                    if (x < GRID_SIZE && y < GRID_SIZE)
                    {
                        cells.raise(x, y);
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
            }

            if (event.type == sf::Event::MouseEntered)
                std::cout << "the mouse cursor has entered the window" << std::endl;
            
            if (event.type == sf::Event::MouseLeft)
                std::cout << "the mouse cursor has left the window" << std::endl;
        }

        window.clear();
        window.draw(cells);
        window.display();
    }

    return 0;
}
