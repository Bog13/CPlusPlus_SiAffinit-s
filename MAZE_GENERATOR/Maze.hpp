#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

namespace MazeGenerator
{
  struct Cell
  {
    size_t i;
    size_t j;
    bool border[4];
  };

  struct Edge
  {
    Cell *c1;
    Cell *c2;

    int weight;
  };

  class Maze
  {
  public:
    Maze(size_t row, size_t column);

    Cell* get(size_t i, size_t j) const;
    void connect(size_t i1, size_t j1, size_t i2, size_t j2);
    void connect(Cell* c1, Cell *c2);
    void compute();
    void display() const;
    static int random(int a,int b);

    ~Maze();
  
  private:
  
    const size_t ROW;
    const size_t COLUMN ;
    const size_t NB_CELLS;
    unsigned int m_visitedCells;
    
    Cell **m_cells;

  
    void initArray();
  };

}

#endif
