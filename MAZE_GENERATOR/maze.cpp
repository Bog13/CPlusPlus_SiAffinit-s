#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Maze.hpp"

using namespace std;
using namespace sf;
using namespace MazeGenerator;
#define INTERFACE
#define CELL_WIDTH 8
#define CELL_HEIGHT CELL_WIDTH
#define N 50

void addVertexArray(vector<VertexArray*> &vec, int x,int y, int w, int h, Color c);
void destroyVertexArray(vector<VertexArray*> &vec);
void displayVertexArray(vector<VertexArray*> &vec, RenderWindow &window);
void createVertexArray(vector<VertexArray*> &vec, Maze const& maze);


int main()
{

  /* init */
  srand(time(NULL));
  /**/
  
  Maze maze(N,N);
  maze.compute();
    
#ifdef INTERFACE

  RenderWindow window(VideoMode(CELL_WIDTH*N,CELL_HEIGHT*N,32), "SFML");
  Event event;

  //creating arrays
  vector<VertexArray*> vec;
  createVertexArray(vec, maze);
  
  while (window.isOpen())
    {
      while( window.pollEvent(event) )
	{
	  switch(event.type)
	    {
	    case Event::Closed:
	      window.close();
	      break;

	    case Event::KeyPressed:
	      switch( event.key.code )
		{
		case Keyboard::Escape:
		  window.close();
		  break;
		  
		default:break;
		}
	      break;
	      
	    default:break;
	    }
	}
      
      window.clear(Color(4,139,154));
      displayVertexArray(vec, window);
      window.display();
    }
  destroyVertexArray(vec);
#endif

  return 0;
}



  
void addVertexArray(vector<VertexArray*> &vec, int x,int y, int w, int h, Color c)
{
  VertexArray* tile = new VertexArray(Quads, 4);
  (*tile)[0].position = Vector2f(x,y);
  (*tile)[0].color = c;
  (*tile)[1].position = Vector2f(x+w,y);
  (*tile)[1].color = c;
  (*tile)[2].position = Vector2f(x+w,y+h);
  (*tile)[2].color = c;
  (*tile)[3].position = Vector2f(x,y+h);
  (*tile)[3].color = c;

  vec.push_back(tile);
}

void destroyVertexArray(vector<VertexArray*> &vec)
{
  for(size_t i=0; i < vec.size(); i++)
    {
      delete vec[i];
    }
}

void displayVertexArray(vector<VertexArray*> &vec, RenderWindow &window)
{
  for(VertexArray *v: vec)
    {
      window.draw(*v);
    }
}

void createVertexArray(vector<VertexArray*> &vec, Maze const& maze)
{
  const int border_thickness = 1;
  
  for(size_t i=0; i<N; i++)
    {
      for(size_t j=0; j<N; j++)
	{
	  //center
	  Color c = Color(100,100,150);
	  if( maze.get(i,j)->visited == true)
	    {
	      //c = Color(100,100,200);
	    }
	  
	  addVertexArray(vec,j*CELL_WIDTH,i*CELL_HEIGHT,CELL_WIDTH,CELL_HEIGHT, c);
	  
	  //north
	  if( maze.get(i,j)->border[0] )
	    {
	      addVertexArray(vec,j*CELL_WIDTH,i*CELL_HEIGHT, CELL_WIDTH, border_thickness,  Color::Black);
	    }   

	  //south
	  if( maze.get(i,j)->border[1] )
	    {
	      addVertexArray(vec,j*CELL_WIDTH,(i+1)*CELL_HEIGHT - 1, CELL_WIDTH, border_thickness,  Color::Black);
	    }
	  
	  if( maze.get(i,j)->border[2] )
	    {
	      //east
	      addVertexArray(vec,j*CELL_WIDTH,i*CELL_HEIGHT, border_thickness, CELL_HEIGHT,Color::Black);
	    }
	  
	  if( maze.get(i,j)->border[3] )
	    {
	      //west
	      addVertexArray(vec,(j+1)*CELL_WIDTH  - 1,i*CELL_HEIGHT, border_thickness, CELL_HEIGHT,Color::Black);
	    }
	  
	}
    }
}
