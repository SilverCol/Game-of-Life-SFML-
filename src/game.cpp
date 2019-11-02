#include <SFML/Graphics.hpp>

namespace
{
    static const float force = .01f;
    static const float gravity = .01f;
    static const float drag = .01f;
}

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Game");

    // The player
    sf::CircleShape player(20.f, 5);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("../images/player.png");
    player.setTexture(&playerTexture);
    float speedX = 0.f;
    float speedY = 0.f;

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (player.getPosition().y < 500.f)
        {
            speedY += gravity;
        }
        else
        {
            speedY = 0.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                speedY -= 200*force;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            speedX += force;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            speedX -= force;
        }
        speedX -= drag * speedX;
        speedY -= drag * speedY;
        player.move(speedX, speedY);

        window.clear(sf::Color::White);
        window.draw(player);
        window.display();
    }

    return 0;
}

