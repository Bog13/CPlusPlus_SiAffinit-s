#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>

class Maze
{
public:
  Maze();

  //init
  void initArray();
  
  ~Maze();
private:
  const int ROW;
  const int COLUMN ;		
  //  bool m_wallRow[ROW][COLUMN];	
  bool **m_wallRow;
};

#endif
