#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!",sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    sf::Texture wood;
    if (!wood.loadFromFile("wood.jpg"))
    {
        std::cout << "Error loading wood texture!" << std::endl;
        return -1;
    }
    wood.setSmooth(true);

    sf::CircleShape log(200);
    log.setTexture(&wood);

    sf::Texture emptyTexture;
    if (!emptyTexture.create(50, 50))
    {
        std::cout << "Error creating empty texture!" << std::endl;
        return -1;
    }
    sf::Uint8 pixles[50 * 50 * 4];
    for (size_t i = 0; i < 50*50*4; i+=4)
    {
        if ((i/4)%14 > 6)
        {
            continue;
        }
        pixles[i] = 32;
        pixles[i+1] = 192;
        pixles[i+2] = 255;
        pixles[i+3] = 128;
    }   
    emptyTexture.update(pixles);

    std::vector<sf::Sprite> squares;

    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("A nice piece of text indeed!");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Yellow);

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
                    std::cout << "the left button was released" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    sf::Sprite square;
                    square.setTexture(emptyTexture);
                    square.setOrigin(25, 25);
                    square.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    squares.push_back(square);
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
        window.draw(log);
        window.draw(text);
        for (const sf::Sprite& square : squares)
        {
            window.draw(square);
        }
        window.display();
    }

    return 0;
}
