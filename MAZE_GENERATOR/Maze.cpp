#include "Maze.hpp"
#include <cstdlib>

namespace MazeGenerator
{
  
  int Maze::random(int a,int b)
  {
    return rand()%(b-a)+a;
  }

  Maze::Maze(size_t row, size_t column): ROW(row), COLUMN(column), NB_CELLS(ROW*COLUMN), m_visitedCells(0)
  {
    initArray();
  }

  void Maze::initArray()
  {
    m_cells = new Cell*[ROW];
    for(size_t i=0; i< ROW;i++)
      {
	m_cells[i] = new Cell[COLUMN];
      }

    for(size_t i=0;i<ROW;i++)
      {
	for(size_t j=0;j<COLUMN;j++)
	  {
	    for(int k =0; k<4; k++)
	      {
		m_cells[i][j].border[k] = true;
	      }

	    m_cells[i][j].visited = false;
			
	  }
      }
  }

  Cell* Maze::get(size_t i, size_t j) const
  {
    assert(i>=0);
    assert(i<ROW);
    assert(j>=0);
    assert(j<COLUMN);
    
    return &m_cells[i][j];
  }

  void Maze::display() const
  {
    int tmp = 0;
    for(size_t i=0;i<ROW;i++)
      {
	for(size_t j=0;j<COLUMN;j++)
	  {
	    std::cout<<tmp<<"  ";
	    tmp++;
	 	  
	  }std::cout<<"\n";
      }

    std::cout<<"\n";
  }

  size_t Maze::openAWall(size_t i, size_t j)
  {
    std::cout<<"NEW\n";
    int nb_wall = 4;
    size_t wall = Maze::random(0,4);
    std::cout<<"Starting wall: "<<wall<<std::endl;
    
    while(m_cells[i][j].border[wall] == false)
      {
	std::cout<<"Trying wall number "<<wall<<"\n";
	nb_wall--;
	wall += 1;
	wall %= 4;
      }

    if( m_cells[i][j].border[wall] == true )
      {
	m_cells[i][j].border[wall] = false;
	return wall;
      }
    
    
    return 4;
  }

  std::vector<std::pair<size_t,size_t>*> Maze::getNeighbor(size_t a, size_t b)
  {
    std::vector<std::pair<size_t,size_t> *> vec;

    size_t i = a+1;
    size_t j = b;
    if( (size_t)i>=0 && (size_t)i< COLUMN && (size_t)j>=0 && (size_t)j<ROW && m_cells[i][j].visited==false)
      {
	std::pair<size_t,size_t> *coord = new std::pair<size_t, size_t>(i,j);
	vec.push_back(coord);
      }

    i = a-1;
    j = b;
    if( (size_t)i>=0 && (size_t)i< COLUMN && (size_t)j>=0 && (size_t)j<ROW && m_cells[i][j].visited==false )
      {
	std::pair<size_t,size_t> *coord = new std::pair<size_t, size_t>(i,j);
	vec.push_back(coord);
      }

    i = a;
    j = b+1;
    if( (size_t)i>=0 && (size_t)i< COLUMN && (size_t)j>=0 && (size_t)j<ROW && m_cells[i][j].visited==false )
      {
	std::pair<size_t,size_t> *coord = new std::pair<size_t, size_t>(i,j);
	vec.push_back(coord);
      }

    i = a;
    j = b-1;
    if( (size_t)i>=0 && (size_t)i< COLUMN && (size_t)j>=0 && (size_t)j<ROW && m_cells[i][j].visited==false )
      {
	std::pair<size_t,size_t> *coord = new std::pair<size_t, size_t>(i,j);
	vec.push_back(coord);
      }

    return vec;
  }

  std::pair<size_t,size_t> Maze::connect(size_t i, size_t j)
  {
    std::vector<std::pair<size_t,size_t> *> neighbor = getNeighbor(i,j);

    //check if we have neighbor
    if( neighbor.size() == 0 )
      {
	std::pair<size_t,size_t> error(-1,-1);
	return error;
	
      }
    
    //get a random coordinate and delete the others
    std::pair<size_t,size_t> *ptr_coord = neighbor[ Maze::random(0,neighbor.size()) ];
    std::pair<size_t, size_t> coord(*ptr_coord);
    for(size_t k = 0; k<neighbor.size(); k++){ delete neighbor[k]; }
    
    //compute difference between i j and first second
    int di, dj;
    di = i - coord.first;
    dj = j - coord.second;

    //find the walls to open
    size_t wall_to_open = -1;
    size_t opposite_wall;
    
    if( di == 1 ){ wall_to_open = 0; }
    if( di == -1 ){ wall_to_open = 1; }
    if( dj == 1 ){ wall_to_open = 2; }
    if( dj == -1 ){ wall_to_open = 3; }
      
    switch(wall_to_open)
      {
      case 0: opposite_wall = 1; break;
      case 1: opposite_wall = 0; break;
      case 2: opposite_wall = 3; break;
      case 3: opposite_wall = 2; break;
      }
    
    m_cells[i][j].border[wall_to_open] = false;
    m_cells[coord.first][coord.second].border[opposite_wall] = false;
    
    /*
      wall index
    0
  2   3
    1
    */

    return coord;
  }

  
  void Maze::compute()
  {/*
    do
      {
	size_t i, j;	  	
	do
	  {
	    i = Maze::random(0,ROW);
	    j = Maze::random(0,COLUMN);
	  }
	while(m_cells[i][j].visited == true);
	  
	connect(i,j);
	m_cells[i][j].visited = true;
	m_visitedCells++;

      }
      while(m_visitedCells != NB_CELLS);*/

    std::pair<size_t,size_t> error(-1,-1);
    std::pair<size_t,size_t> last_good;
    std::vector<std::pair<size_t,size_t> > history;
    
    //find a non visited cell
    size_t i, j;
    /*
    do
      {
	i = Maze::random(0,ROW);
	j = Maze::random(0,COLUMN);
      }
      while(m_cells[i][j].visited == true);*/
    i = 0;
    j = 0;
	
    do
      {
	std::pair<size_t,size_t> next = connect(i,j);

	m_cells[i][j].visited = true;
	m_visitedCells++;		
	
	//if no neighbor unvisited
	if(next == error )
	  {
	    //jump to last good cell/*

	    bool found = false;
	    
	    for(size_t k = history.size()-1; k>0; k--)
	      {
		if( getNeighbor(history[k].first, history[k].second).size()>1 )
		  {
		    i = history[k].first;
		    j = history[k].second;
		    found = true;
		    break;
		  }
	      }

	    if( !found )
	      {std::cout<<"OK";
		do
		  {
		    i = Maze::random(0,ROW);
		    j = Maze::random(0,COLUMN);
		  }
		while(m_cells[i][j].visited == true);
	      }

	  }
	//
	else
	  {
	    history.push_back(next);

	    i = next.first;
	    j = next.second;
	  }
	  

      }
      while(m_visitedCells != NB_CELLS);

    std::cout<<"\tDONE\n";
  }

  Maze::~Maze()
  {

    for(size_t i=0;i<ROW;i++)
      {
	delete[] m_cells[i];
      }
    delete[] m_cells;
  }
  
}
