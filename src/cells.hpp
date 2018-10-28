#ifndef CELLS_H
#define CELLS_H

#include <SFML/Graphics.hpp>

class Cells: public sf::Drawable, public sf::Transformable
{
public:
    Cells(const size_t size, const uint8_t width, const sf::Color& alive, const sf::Color& dead, const sf::Color& back);
    void raise(size_t x, size_t y);
    void kill(size_t x, size_t y);
    void setDead(size_t x, size_t y);
    void setCellSize(const uint8_t width);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_cells;
    size_t m_size;
    sf::Color m_aliveColor;
    sf::Color m_deadColor;
    sf::Color m_backColor;
};

Cells::Cells(const size_t size, const uint8_t width, const sf::Color& alive, const sf::Color& dead, const sf::Color& back):
    m_size(size),
    m_aliveColor(alive),
    m_deadColor(dead),
    m_cells(sf::Quads, 4 * size * size)
{
    for (size_t i = 0; i < m_size * m_size; ++i)
    {
        size_t j = 4 * i;
        size_t x = (i % m_size) * width;
        size_t y = (i / m_size) * width;
        size_t x1 = (1 + i % m_size) * width;
        size_t y1 = (1 + i / m_size) * width;

        m_cells[j].position = sf::Vector2f(x, y);
        m_cells[j].color = back;

        m_cells[j + 1].position = sf::Vector2f(x1, y);
        m_cells[j + 1].color = back;

        m_cells[j + 2].position = sf::Vector2f(x1, y1);
        m_cells[j + 2].color = back;

        m_cells[j + 3].position = sf::Vector2f(x, y1);
        m_cells[j + 3].color = back;
    }
}

void Cells::raise(size_t x, size_t y)
{
    size_t j = 4 * (x + m_size * y);
    m_cells[j].color = m_aliveColor;
    m_cells[j + 1].color = m_aliveColor;
    m_cells[j + 2].color = m_aliveColor;
    m_cells[j + 3].color = m_aliveColor;
}

void Cells::kill(size_t x, size_t y)
{
    size_t j = 4 * (x + m_size * y);
    m_cells[j].color = m_deadColor;
    m_cells[j + 1].color = m_deadColor;
    m_cells[j + 2].color = m_deadColor;
    m_cells[j + 3].color = m_deadColor;
}

void Cells::setDead(size_t x, size_t y)
{
    size_t j = 4 * (x + m_size * y);
    m_cells[j].color = m_backColor;
    m_cells[j + 1].color = m_backColor;
    m_cells[j + 2].color = m_backColor;
    m_cells[j + 3].color = m_backColor;
}

void Cells::setCellSize(const uint8_t width)
{
    for (size_t i = 0; i < m_size * m_size; ++i)
    {
        size_t j = 4 * i;
        size_t x = (i % m_size) * width;
        size_t y = (i / m_size) * width;
        size_t x1 = (1 + i % m_size) * width;
        size_t y1 = (1 + i / m_size) * width;

        m_cells[j].position = sf::Vector2f(x, y);

        m_cells[j + 1].position = sf::Vector2f(x1, y);

        m_cells[j + 2].position = sf::Vector2f(x1, y1);

        m_cells[j + 3].position = sf::Vector2f(x, y1);
    }
}

void Cells::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_cells, states);
}

# endif
