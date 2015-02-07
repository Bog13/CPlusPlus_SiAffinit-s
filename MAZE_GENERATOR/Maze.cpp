#include "Maze.hpp"

Maze::Maze(): ROW(10), COLUMN(5)
{
  std::cout<<"Hello world !\n";
  initArray();
}

void Maze::initArray()
{
  m_wallRow = new bool*[ROW];
  for(int i=0; i< ROW;i++)
    {
      m_wallRow[i] = new bool[COLUMN];
    }

  for(int i=0;i<ROW;i++)
    {
      for(int j=0;j<COLUMN;j++)
	{
	  m_wallRow[i][j] = true;
	}
    }

  for(int i=0;i<ROW;i++)
    {
      for(int j=0;j<COLUMN;j++)
	{
	  std::cout<<m_wallRow[i][j];
	  
	}std::cout<<"\n";
    }
}

Maze::~Maze()
{

  for(int i=0;i<ROW;i++)
    {
      delete[] m_wallRow[i];
    }
  delete[] m_wallRow;
}
