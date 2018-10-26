#include <SFML/Graphics.hpp>
#include <bitset>
#include <iostream>

namespace
{
    static const size_t WORLD_SIZE = 128;
    static const size_t SQUARE_SIZE = 5;
    static const size_t WINDOW_SIZE = WORLD_SIZE * SQUARE_SIZE;
    static const size_t GRID_WIDTH = 1;
    static const size_t GRID_OPACITY = 32;

    static std::bitset<WORLD_SIZE*WORLD_SIZE> auxCells(0);
    void stepForward(std::bitset<WORLD_SIZE*WORLD_SIZE>& cells)
    {
        std::cout << "START" << std::endl;
        auxCells = cells;
        for (int y = 0; y < WORLD_SIZE; ++y)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                int8_t count = 0;
                if (y == 0)
                {
                    if (x == 0)
                    {
                        if (cells.test(WORLD_SIZE*y + x+1)) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + x+1)) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + x)) ++count;
                    }
                    else if (x == WORLD_SIZE - 1)
                    {
                        if (cells.test(WORLD_SIZE*(y) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x))) ++count;
                    }
                    else
                    {
                        if (cells.test(WORLD_SIZE*(y) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x+1))) ++count;
                    }
                }
                else if (y == WORLD_SIZE - 1)
                {
                    if (x == 0)
                    {
                        if (cells.test(WORLD_SIZE*(y) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x))) ++count;
                    }
                    else if (x == WORLD_SIZE - 1)
                    {
                        if (cells.test(WORLD_SIZE*(y) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x))) ++count;
                    }
                    else
                    {
                        if (cells.test(WORLD_SIZE*(y) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x+1))) ++count;
                    }
                }
                else if (x == 0)
                {
                        if (cells.test(WORLD_SIZE*(y+1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x+1))) ++count;
                }
                else if (x == WORLD_SIZE - 1)
                {
                        if (cells.test(WORLD_SIZE*(y+1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x-1))) ++count;
                }
                else
                {
                        if (cells.test(WORLD_SIZE*(y-1) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y-1) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y) + (x+1))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x-1))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x))) ++count;
                        if (cells.test(WORLD_SIZE*(y+1) + (x+1))) ++count;
                }

                if (cells.test(WORLD_SIZE*y + x) && (count < 2 || count > 3))
                {
                    auxCells.flip(WORLD_SIZE*y + x);
                }
                if (!cells.test(WORLD_SIZE*y + x) && count == 3)
                {
                    auxCells.flip(WORLD_SIZE*y + x);
                }
            }
        }
        cells = auxCells;
        std::cout << "STOP" << std::endl;
    }
}

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Game Of Life");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    square.setFillColor(sf::Color::White);
    sf::RectangleShape hLine(sf::Vector2f(WINDOW_SIZE, GRID_WIDTH));
    hLine.setFillColor(sf::Color(255, 255, 255, GRID_OPACITY));
    sf::RectangleShape vLine(sf::Vector2f(GRID_WIDTH, WINDOW_SIZE));
    vLine.setFillColor(sf::Color(255, 255, 255, GRID_OPACITY));

    sf::RectangleShape brush(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    brush.setFillColor(sf::Color(255, 0, 0, 128));
    int32_t brushSize = 1;

    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Game Of Life");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::White);

    std::bitset<WORLD_SIZE*WORLD_SIZE> cells(0);
    bool gameOn = false;
    bool keyControl = false;

    sf::Clock timer;
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

            if (event.type == sf::Event::LostFocus)
            {
                std::cout << "Focus lost." << std::endl;
            }
            
            if (event.type == sf::Event::GainedFocus)
            {
                std::cout << "Focus gained." << std::endl;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    gameOn = !gameOn;
                }
                else if (event.key.code == sf::Keyboard::LShift && !gameOn)
                {
                    keyControl = !keyControl;
                }
            }

            if (!gameOn && !keyControl)
            {
                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    {
                        std::cout << "wheel type: vertical" << std::endl;
                        brushSize += event.mouseWheelScroll.delta;
                        if (brushSize < 1) brushSize = 1;
                        brush.setSize(sf::Vector2f(brushSize * SQUARE_SIZE, brushSize * SQUARE_SIZE));
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        size_t x = event.mouseButton.x;
                        size_t y = event.mouseButton.y;
                        std::cout << "the right button was released" << std::endl;
                        std::cout << "mouse x: " << x << std::endl;
                        std::cout << "mouse y: " << y << std::endl;

                        size_t cellX = x/SQUARE_SIZE;
                        size_t cellY = y/SQUARE_SIZE;
                        for (int n = cellY; n < cellY + brushSize && n < WORLD_SIZE; ++n)
                        {
                            for (int m = cellX; m < cellX + brushSize && m < WORLD_SIZE; ++m)
                            {
                                cells.reset(WORLD_SIZE*n + m);
                            }
                        }
                    }
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        size_t x = event.mouseButton.x;
                        size_t y = event.mouseButton.y;
                        std::cout << "the left button was released" << std::endl;
                        std::cout << "mouse x: " << x << std::endl;
                        std::cout << "mouse y: " << y << std::endl;

                        size_t cellX = x/SQUARE_SIZE;
                        size_t cellY = y/SQUARE_SIZE;
                        for (int n = cellY; n < cellY + brushSize && n < WORLD_SIZE; ++n)
                        {
                            for (int m = cellX; m < cellX + brushSize && m < WORLD_SIZE; ++m)
                            {
                                cells.set(WORLD_SIZE*n + m);
                            }
                        }
                    }
                }

                if (event.type == sf::Event::MouseMoved)
                {
                    size_t x = event.mouseMove.x;
                    size_t y = event.mouseMove.y;
                    std::cout << "new mouse x: " << x << std::endl;
                    std::cout << "new mouse y: " << y << std::endl;
                    size_t cellX = x/SQUARE_SIZE;
                    size_t cellY = y/SQUARE_SIZE;
                    brush.setPosition(sf::Vector2f(cellX*SQUARE_SIZE, cellY*SQUARE_SIZE));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        for (int n = cellY; n < cellY + brushSize && n < WORLD_SIZE; ++n)
                        {
                            for (int m = cellX; m < cellX + brushSize && m < WORLD_SIZE; ++m)
                            {
                                cells.set(WORLD_SIZE*n + m);
                            }
                        }
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        for (int n = cellY; n < cellY + brushSize && n < WORLD_SIZE; ++n)
                        {
                            for (int m = cellX; m < cellX + brushSize && m < WORLD_SIZE; ++m)
                            {
                                cells.reset(WORLD_SIZE*n + m);
                            }
                        }
                    }
                }

                if (event.type == sf::Event::MouseEntered)
                    std::cout << "the mouse cursor has entered the window" << std::endl;
                
                if (event.type == sf::Event::MouseLeft)
                    std::cout << "the mouse cursor has left the window" << std::endl;
            }
        }

        if (gameOn)
        {
            if (timer.getElapsedTime().asMilliseconds() > 50)
            {
                std::cout << "New step after " << timer.getElapsedTime().asMilliseconds() << std::endl;
                stepForward(cells);
                timer.restart();
            }
        }
        else if (keyControl)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                brush.move(0, -1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                brush.move(0, 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                brush.move(1, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                brush.move(-1, 0);
            }
        }

        window.clear();
        for (int y = 0; y < WORLD_SIZE; ++y)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                if (cells.test(WORLD_SIZE*y + x))
                {
                    square.setPosition(sf::Vector2f(x * SQUARE_SIZE, y * SQUARE_SIZE));
                    window.draw(square);
                }
            }
        }
        if (!gameOn)
        {
            for (int i = 0; i <= WORLD_SIZE; ++i)
            {
                hLine.setPosition(sf::Vector2f(0, i * SQUARE_SIZE - 1));
                vLine.setPosition(sf::Vector2f(i * SQUARE_SIZE - 1, 0));
                window.draw(hLine);
                window.draw(vLine);
            }
            window.draw(brush);
            window.draw(text);
        }
        window.display();
    }

    return 0;
}
