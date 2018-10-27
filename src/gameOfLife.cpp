#include "flatland.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace
{
    static const size_t GRID_SIZE = 1024;
    static size_t SQUARE_SIZE = 10;
    static size_t WORLD_SIZE = GRID_SIZE * SQUARE_SIZE;
    static const size_t GRID_WIDTH = 1;
    static const size_t GRID_OPACITY = 32;

    static sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));

    static sf::RectangleShape hLine(sf::Vector2f(WORLD_SIZE, GRID_WIDTH));
    static sf::RectangleShape vLine(sf::Vector2f(GRID_WIDTH, WORLD_SIZE));

    static sf::RectangleShape brush(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    static int32_t brushSize = 1;

    static void scaleWorld(const bool up)
    {
        if (up)
        {
            ++SQUARE_SIZE;
        }
        else
        {
            --SQUARE_SIZE;
        }
        WORLD_SIZE = GRID_SIZE * SQUARE_SIZE;

        square.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
        hLine.setSize(sf::Vector2f(WORLD_SIZE, GRID_WIDTH));
        vLine.setSize(sf::Vector2f(GRID_WIDTH, WORLD_SIZE));
        brush.setSize(sf::Vector2f(brushSize*SQUARE_SIZE, brushSize*SQUARE_SIZE));
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Game Of Life");
    window.setVerticalSyncEnabled(true);
    sf::View view = window.getDefaultView();
    view.setCenter(WORLD_SIZE/2, WORLD_SIZE/2);
    window.setView(view);

    hLine.setFillColor(sf::Color(255, 255, 255, GRID_OPACITY));
    vLine.setFillColor(sf::Color(255, 255, 255, GRID_OPACITY));
    brush.setFillColor(sf::Color(255, 0, 0, 128));

    Flatland<GRID_SIZE> flatland;
    bool gameOn = false;

    sf::Clock timer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::Resized)
            {
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }

            else if (event.type == sf::Event::LostFocus)
            {
                std::cout << "Focus lost." << std::endl;
            }
            
            else if (event.type == sf::Event::GainedFocus)
            {
                std::cout << "Focus gained." << std::endl;
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    gameOn = !gameOn;
                    window.setMouseCursorVisible(!gameOn);
                }
                else if (event.key.code == sf::Keyboard::PageUp)
                {
                    scaleWorld(true);
                    sf::Vector2f oldCenter = view.getCenter();
                    sf::Vector2f newCenter = (float)SQUARE_SIZE * oldCenter / (float)(SQUARE_SIZE - 1);
                    view.setCenter(newCenter);
                    window.setView(view);
                }
                else if (event.key.code == sf::Keyboard::PageDown && SQUARE_SIZE > 1)
                {
                    scaleWorld(false);
                    sf::Vector2f oldCenter = view.getCenter();
                    sf::Vector2f newCenter = (float)SQUARE_SIZE * oldCenter / (float)(SQUARE_SIZE + 1);
                    view.setCenter(newCenter);
                    window.setView(view);
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    view.setCenter(WORLD_SIZE/2, WORLD_SIZE/2);
                        window.setView(view);
                }
            }

            else if (!gameOn)
            {
                if (event.type == sf::Event::MouseMoved)
                {
                    size_t x = event.mouseMove.x + view.getCenter().x - view.getSize().x/2;
                    size_t y = event.mouseMove.y + view.getCenter().y - view.getSize().y/2;
                    std::cout << "new mouse x: " << x << std::endl;
                    std::cout << "new mouse y: " << y << std::endl;
                    size_t cellX = x/SQUARE_SIZE;
                    size_t cellY = y/SQUARE_SIZE;
                    brush.setPosition(sf::Vector2f(cellX*SQUARE_SIZE, cellY*SQUARE_SIZE));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        for (size_t n = cellY; n < cellY + brushSize && n < GRID_SIZE; ++n)
                        {
                            for (size_t m = cellX; m < cellX + brushSize && m < GRID_SIZE; ++m)
                            {
                                flatland.raise(m, n);
                            }
                        }
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        for (size_t n = cellY; n < cellY + brushSize && n < GRID_SIZE; ++n)
                        {
                            for (size_t m = cellX; m < cellX + brushSize && m < GRID_SIZE; ++m)
                            {
                                flatland.kill(m, n);
                            }
                        }
                    }
                }
                else if (event.type == sf::Event::MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    {
                        std::cout << "wheel type: vertical" << std::endl;
                        brushSize += event.mouseWheelScroll.delta;
                        if (brushSize < 1) brushSize = 1;
                        brush.setSize(sf::Vector2f(brushSize * SQUARE_SIZE, brushSize * SQUARE_SIZE));
                    }
                }

                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        size_t x = event.mouseButton.x + view.getCenter().x - view.getSize().x/2;
                        size_t y = event.mouseButton.y + view.getCenter().y - view.getSize().y/2;
                        std::cout << "the left button was released" << std::endl;
                        std::cout << "mouse x: " << x << std::endl;
                        std::cout << "mouse y: " << y << std::endl;

                        size_t cellX = x/SQUARE_SIZE;
                        size_t cellY = y/SQUARE_SIZE;
                        for (size_t n = cellY; n < cellY + brushSize && n < GRID_SIZE; ++n)
                        {
                            for (size_t m = cellX; m < cellX + brushSize && m < GRID_SIZE; ++m)
                            {
                                flatland.raise(m, n);
                            }
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        size_t x = event.mouseButton.x + view.getCenter().x - view.getSize().x/2;
                        size_t y = event.mouseButton.y + view.getCenter().y - view.getSize().y/2;
                        std::cout << "the right button was released" << std::endl;
                        std::cout << "mouse x: " << x << std::endl;
                        std::cout << "mouse y: " << y << std::endl;

                        size_t cellX = x/SQUARE_SIZE;
                        size_t cellY = y/SQUARE_SIZE;
                        for (int n = cellY; n < cellY + brushSize && n < GRID_SIZE; ++n)
                        {
                            for (int m = cellX; m < cellX + brushSize && m < GRID_SIZE; ++m)
                            {
                                flatland.kill(m, n);
                            }
                        }
                    }
               }

           }
        }
        if (gameOn)
        {
            if (timer.getElapsedTime().asMilliseconds() > 50)
            {
                std::cout << "New step after " << timer.getElapsedTime().asMilliseconds() << std::endl;
                flatland.evolve();
                timer.restart();
            }
        }

        window.clear();

        hLine.setPosition(sf::Vector2f(0, -1));
        vLine.setPosition(sf::Vector2f(-1, 0));
        window.draw(hLine);
        window.draw(vLine);
        hLine.setPosition(sf::Vector2f(0, WORLD_SIZE));
        vLine.setPosition(sf::Vector2f(WORLD_SIZE, 0));
        window.draw(hLine);
        window.draw(vLine);

        for (size_t y = 0; y < GRID_SIZE; ++y)
        {
            for (size_t x = 0; x < GRID_SIZE; ++x)
            {
                if (flatland.isAlive(x, y))
                {
                    square.setPosition(sf::Vector2f(x * SQUARE_SIZE, y * SQUARE_SIZE));
                    window.draw(square);
                }
            }
        }

        if (!gameOn)
        {
            for (size_t i = 1; i < GRID_SIZE; ++i)
            {
                hLine.setPosition(sf::Vector2f(0, i * SQUARE_SIZE));
                vLine.setPosition(sf::Vector2f(i * SQUARE_SIZE, 0));
                window.draw(hLine);
                window.draw(vLine);
            }
            window.draw(brush);
        }
        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            view.move(5.f, 0.f);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            view.move(-5.f, 0.f);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            view.move(0.f, -5.f);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            view.move(0.f, 5.f);
            window.setView(view);
        }
   }

    return 0;
}
