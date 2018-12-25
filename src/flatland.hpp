#ifndef FLATLAND_H
#define FLATLAND_H

#include <bitset>

template <size_t m_size>
class Flatland
{
public:
    Flatland();
    void evolve();
    int8_t countNeighbours(const size_t x, const size_t y);
    inline bool isAlive(const size_t x, const size_t y){return m_cells.test(m_size*y + x);}
    inline bool change(const size_t x, const size_t y){return m_diff.test(m_size*y + x);}
    inline void raise(const size_t x, const size_t y){m_cells.set(m_size*y + x);}
    inline void kill(const size_t x, const size_t y){m_cells.reset(m_size*y + x);}
private:
    std::bitset<m_size*m_size> m_cells;
    std::bitset<m_size*m_size> m_helper;
    std::bitset<m_size*m_size> m_diff;
};

template <size_t m_size>
Flatland<m_size>::Flatland():
    m_cells(0),
    m_diff(0)
{}

template <size_t m_size>
void Flatland<m_size>::evolve()
{
    m_helper = m_cells;
    m_diff = m_cells;
    for (size_t y = 0; y < m_size; ++y)
    {
        for (size_t x = 0; x < m_size; ++x)
        {
            size_t position = m_size*y + x;
            bool alive = m_cells.test(position);
            int8_t neighbours = countNeighbours(x, y);
            if (alive && (neighbours < 2 || neighbours > 3)) m_helper.flip(position);
            if (!alive && neighbours == 3) m_helper.flip(position);
        }
    }
    m_diff^=m_helper;
    m_cells = m_helper;
}

template <size_t m_size>
int8_t Flatland<m_size>::countNeighbours(const size_t x, const size_t y)
{
    int8_t count = 0;

    if (y == 0)
    {
        if (x == 0)
        {
            if (m_cells.test(m_size*y + x+1)) ++count;
            if (m_cells.test(m_size*(y+1) + x+1)) ++count;
            if (m_cells.test(m_size*(y+1) + x)) ++count;
        }
        else if (x == m_size - 1)
        {
            if (m_cells.test(m_size*(y) + (x-1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x))) ++count;
        }
        else
        {
            if (m_cells.test(m_size*(y) + (x-1))) ++count;
            if (m_cells.test(m_size*(y) + (x+1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x))) ++count;
            if (m_cells.test(m_size*(y+1) + (x+1))) ++count;
        }
    }
    else if (y == m_size - 1)
    {
        if (x == 0)
        {
            if (m_cells.test(m_size*(y) + (x+1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x+1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x))) ++count;
        }
        else if (x == m_size - 1)
        {
            if (m_cells.test(m_size*(y) + (x-1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x))) ++count;
        }
        else
        {
            if (m_cells.test(m_size*(y) + (x-1))) ++count;
            if (m_cells.test(m_size*(y) + (x+1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x))) ++count;
            if (m_cells.test(m_size*(y-1) + (x+1))) ++count;
        }
    }
    else if (x == 0)
    {
            if (m_cells.test(m_size*(y) + (x+1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x))) ++count;
            if (m_cells.test(m_size*(y-1) + (x+1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x+1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x))) ++count;
    }
    else if (x == m_size - 1)
    {
            if (m_cells.test(m_size*(y) + (x-1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x))) ++count;
            if (m_cells.test(m_size*(y-1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x))) ++count;
    }
    else
    {
            if (m_cells.test(m_size*(y) + (x-1))) ++count;
            if (m_cells.test(m_size*(y) + (x+1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y-1) + (x))) ++count;
            if (m_cells.test(m_size*(y-1) + (x+1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x-1))) ++count;
            if (m_cells.test(m_size*(y+1) + (x))) ++count;
            if (m_cells.test(m_size*(y+1) + (x+1))) ++count;
    }
    return count;
}

#endif
