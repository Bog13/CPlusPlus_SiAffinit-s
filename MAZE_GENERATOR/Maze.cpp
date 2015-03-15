#include <Maze.hpp>
#include <Tree.hpp>
#include <cstdlib>
#include <random>
#include <chrono>
#include <map>
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

	    m_cells[i][j].i = i;
	    m_cells[i][j].j = j;
			
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

  void Maze::connect(size_t i1, size_t j1, size_t i2, size_t j2)
  {
    assert( (abs(i1 - i2) == 1) || (abs(j1 - j2) == 1) );
    assert(i1 >= 0);
    assert(i1 < ROW);
    assert(i2 >= 0);
    assert(i2 < ROW);
    assert(j1 >= 0);
    assert(j1 < COLUMN);
    assert(j2 >= 0);
    assert(j2 < COLUMN);
    
    //up
    if( i1 + 1 == i2 )
      {
	m_cells[i1][j1].border[1] = false;
	m_cells[i2][j2].border[0] = false;
      }
    //down
    else if( i1 - 1 == i2 )
      {
	m_cells[i1][j1].border[0] = false;
	m_cells[i2][j2].border[1] = false;
      }
    //left
    else if( j1 + 1 == j2 )
      {
	m_cells[i1][j1].border[3] = false;
	m_cells[i2][j2].border[2] = false;
      }
    //right
    else if( j1 - 1 == j2 )
      {
	m_cells[i1][j1].border[2] = false;
	m_cells[i2][j2].border[3] = false;
      }

  }

  void Maze::connect(Cell* c1, Cell *c2)
  {
    connect(c1->i, c1->j, c2->i, c2->j);
  }
  
  void Maze::compute()
  {
    std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(0,100);
    
    /* creating edges */
    std::vector<Edge*> edges;
    std::vector<Tree*> trees;
    std::map<Cell*, Tree*> m;
    
    for(size_t i=0; i<ROW; i++)
      {
	for(size_t j=0; j<COLUMN; j++)
	  {
	    Tree* t = new Tree( &m_cells[i][j] );
	    trees.push_back(t);
	    m[ &m_cells[i][j] ] = t;
	    
	    if( j + 1 < COLUMN )
	      {
		Edge* e = new Edge;
		e->c1 = &m_cells[i][j];
		e->c2 = &m_cells[i][j+1];
		e->weight = distrib(dre);
		edges.push_back(e);
	      }

	    if( i + 1 < ROW)
	      {
		Edge* e = new Edge;
		e->c1 = &m_cells[i][j];
		e->c2 = &m_cells[i+1][j];
		e->weight = distrib(dre);
		edges.push_back(e);
	      }
	  }
      }


    int ok = 3;

    while( edges.size() > 0 )
      {
	/* find the minimum weight */
	size_t weight_min = 0;
	for( size_t i =0; i< edges.size(); i++ )
	  {
	    if( edges[i]->weight < edges[weight_min]->weight )
	      {
		weight_min = i;
	      }
	  }

	/* make connection */
	Edge* edge_min = edges[weight_min];
	if( m[edge_min->c1]->Find() != m[edge_min->c2]->Find() )
	  {
	    connect(edge_min->c1, edge_min->c2);
	    m[edge_min->c1]->Union( m[edge_min->c2] );
	  }

	/* remove min edge */
	edges.erase(edges.begin() + weight_min);
	
	ok --;
      }

    /* free edges */
    for( Edge* e: edges )
      {
	delete e;
      }

    /* free trees */
    for( Tree* t: trees )
      {
	delete t;
      }
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
