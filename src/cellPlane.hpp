#ifndef CELLPLANE_H
#define CELLPLANE_H

#include "cells.hpp"
#include "grid.hpp"
#include <SFML/Graphics.hpp>

class CellPlane: public sf::Drawable, public sf::Transformable
{
public:
    CellPlane(const size_t size, const uint8_t width, const sf::Color& alive, const sf::Color& dead, const sf::Color& back, const sf::Color& grid);
    inline void raise(size_t x, size_t y){m_cells.raise(x, y);}
    inline void kill(size_t x, size_t y){m_cells.kill(x, y);}
    inline void setDead(size_t x, size_t y){m_cells.setDead(x, y);}
    inline void setCellSize(const uint8_t width)
    {
        m_cells.setCellSize(width);
        m_grid.setCellSize(width);
    }
    inline void showGrid(bool show){m_showGrid = show;}
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Cells m_cells;
    Grid m_grid;
    bool m_showGrid;
};

CellPlane::CellPlane(const size_t size, const uint8_t width, const sf::Color& alive, const sf::Color& dead, const sf::Color& back, const sf::Color& grid):
    m_cells(size, width, alive, dead, back),
    m_grid(size, width, grid),
    m_showGrid(true)
{}

void CellPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_cells);
    if (m_showGrid) target.draw(m_grid);
}

# endif
