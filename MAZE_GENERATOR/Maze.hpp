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
    bool visited;
    bool border[4];
  };

  class Maze
  {
  public:
    Maze(size_t row, size_t column);

    Cell* get(size_t i, size_t j) const;
    void compute();
    void display() const;
    size_t openAWall(size_t i, size_t j);
    static int random(int a,int b);

    std::vector<std::pair<size_t,size_t> *> getNeighbor(size_t a, size_t b);
    std::pair<size_t,size_t> connect(size_t i, size_t j);
    
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
