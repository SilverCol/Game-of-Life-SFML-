#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid: public sf::Drawable, public sf::Transformable
{
public:
    Grid(const size_t size, const uint8_t width, const sf::Color& color);
    void setCellSize(const uint8_t width);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_lines;
    size_t m_size;
};

Grid::Grid(const size_t size, const uint8_t width, const sf::Color& color):
    m_size(size),
    m_lines(sf::Lines, 4 * (size - 1))
{
    for (size_t i = 0; i < m_size - 1; ++i)
    {
        size_t j = 4 * i;
        size_t x = (i + 1) * width;
        size_t y = m_size * width;
        m_lines[j].position = sf::Vector2f(x, 0);
        m_lines[j].color = color;
        m_lines[j + 1].position = sf::Vector2f(x, y);
        m_lines[j + 1].color = color;
        m_lines[j + 2].position = sf::Vector2f(0, x);
        m_lines[j + 2].color = color;
        m_lines[j + 3].position = sf::Vector2f(y, x);
        m_lines[j + 3].color = color;
    }
}

void Grid::setCellSize(const uint8_t width)
{
    for (size_t i = 0; i < m_size - 1; ++i)
    {
        size_t j = 4 * i;
        size_t x = (i + 1) * width;
        size_t y = m_size * width;
        m_lines[j].position = sf::Vector2f(x, 0);
        m_lines[j + 1].position = sf::Vector2f(x, y);
        m_lines[j + 2].position = sf::Vector2f(0, x);
        m_lines[j + 3].position = sf::Vector2f(y, x);
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_lines, states);
}

#endif
