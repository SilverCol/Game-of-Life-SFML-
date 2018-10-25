#include <SFML/Graphics.hpp>
#include <iostream>

namespace
{
    static const size_t WORLD_SIZE = 128;
    static const size_t SQUARE_SIZE = 5;
    static const size_t WINDOW_SIZE = WORLD_SIZE * SQUARE_SIZE;

    static std::vector<std::vector<bool> > auxCells(WORLD_SIZE, std::vector<bool>(WORLD_SIZE, false));
    void stepForward(std::vector<std::vector<bool> >& cells)
    {
        std::cout << "START" << std::endl;
        for (int y = 0; y < WORLD_SIZE; ++y)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                int8_t count = 0;
                if (y == 0)
                {
                    if (x == 0)
                    {
                        if (cells.at(y).at(x+1)) ++count;
                        if (cells.at(y+1).at(x+1)) ++count;
                        if (cells.at(y+1).at(x)) ++count;
                    }
                    else if (x == WORLD_SIZE - 1)
                    {
                        if (cells.at(y).at(x-1)) ++count;
                        if (cells.at(y+1).at(x-1)) ++count;
                        if (cells.at(y+1).at(x)) ++count;
                    }
                    else
                    {
                        if (cells.at(y).at(x-1)) ++count;
                        if (cells.at(y).at(x+1)) ++count;
                        if (cells.at(y+1).at(x-1)) ++count;
                        if (cells.at(y+1).at(x)) ++count;
                        if (cells.at(y+1).at(x+1)) ++count;
                    }
                }
                else if (y == WORLD_SIZE - 1)
                {
                    if (x == 0)
                    {
                        if (cells.at(y).at(x+1)) ++count;
                        if (cells.at(y-1).at(x+1)) ++count;
                        if (cells.at(y-1).at(x)) ++count;
                    }
                    else if (x == WORLD_SIZE - 1)
                    {
                        if (cells.at(y).at(x-1)) ++count;
                        if (cells.at(y-1).at(x-1)) ++count;
                        if (cells.at(y-1).at(x)) ++count;
                    }
                    else
                    {
                        if (cells.at(y).at(x-1)) ++count;
                        if (cells.at(y).at(x+1)) ++count;
                        if (cells.at(y-1).at(x-1)) ++count;
                        if (cells.at(y-1).at(x)) ++count;
                        if (cells.at(y-1).at(x+1)) ++count;
                    }
                }
                else if (x == 0)
                {
                        if (cells.at(y+1).at(x)) ++count;
                        if (cells.at(y-1).at(x)) ++count;
                        if (cells.at(y+1).at(x+1)) ++count;
                        if (cells.at(y).at(x+1)) ++count;
                        if (cells.at(y-1).at(x+1)) ++count;
                }
                else if (x == WORLD_SIZE - 1)
                {
                        if (cells.at(y+1).at(x)) ++count;
                        if (cells.at(y-1).at(x)) ++count;
                        if (cells.at(y+1).at(x-1)) ++count;
                        if (cells.at(y).at(x-1)) ++count;
                        if (cells.at(y-1).at(x-1)) ++count;
                }
                else
                {
                        if (cells.at(y-1).at(x-1)) ++count;
                        if (cells.at(y-1).at(x)) ++count;
                        if (cells.at(y-1).at(x+1)) ++count;
                        if (cells.at(y).at(x-1)) ++count;
                        if (cells.at(y).at(x+1)) ++count;
                        if (cells.at(y+1).at(x-1)) ++count;
                        if (cells.at(y+1).at(x)) ++count;
                        if (cells.at(y+1).at(x+1)) ++count;
                }

                auxCells = cells;
                if (cells.at(x).at(y) && count < 3)
                {
                    auxCells.at(x).at(y) = false;
                }
                if (!cells.at(x).at(y) && count > 3)
                {
                    auxCells.at(x).at(y) = true;
                }
                cells = auxCells;
            }
        }
        std::cout << "STOP" << std::endl;
    }
}

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Game Of Life");
    window.setVerticalSyncEnabled(true);

    sf::Texture white;
    if (!white.create(SQUARE_SIZE, SQUARE_SIZE))
    {
        std::cout << "Error creating empty texture!" << std::endl;
        return -1;
    }
    sf::Uint8 pixles[SQUARE_SIZE * SQUARE_SIZE * 4];
    for (size_t i = 0; i < SQUARE_SIZE * SQUARE_SIZE * 4; ++i)
    {
        pixles[i] = 255;
    }   
    white.update(pixles);
    sf::Sprite square;
    square.setTexture(white);

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
    text.setFillColor(sf::Color::Yellow);

    std::vector<std::vector<bool> > cells(WORLD_SIZE, std::vector<bool>(WORLD_SIZE, false));
    bool gameOn = false;

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

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;

                    gameOn = !gameOn;
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
                }
                if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    std::cout << "the middle button was released" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    size_t x = event.mouseButton.x;
                    size_t y = event.mouseButton.y;
                    std::cout << "the left button was released" << std::endl;
                    std::cout << "mouse x: " << x << std::endl;
                    std::cout << "mouse y: " << y << std::endl;

                    if (!gameOn)
                    {
                        size_t cellX = x/SQUARE_SIZE;
                        size_t cellY = y/SQUARE_SIZE;
                        cells.at(cellY).at(cellX) = !cells.at(cellY).at(cellX);
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

        if (gameOn)
        {
            if (timer.getElapsedTime().asMilliseconds() > 500)
            {
                std::cout << "New step after " << timer.getElapsedTime().asMilliseconds() << std::endl;
                stepForward(cells);
                timer.restart();
            }
        }

        window.clear();
        for (int y = 0; y < WORLD_SIZE; ++y)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                if (cells.at(y).at(x))
                {
                    square.setPosition(sf::Vector2f(x * SQUARE_SIZE, y * SQUARE_SIZE));
                    window.draw(square);
                }
            }
        }
        window.draw(text);
        window.display();
    }

    return 0;
}
