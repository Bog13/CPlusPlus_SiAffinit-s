#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>


namespace MazeGenerator
{

  class Cell;
  
  class Tree
  {
  public:
    Tree(Cell* data);
    ~Tree();

    void Union(Tree* target);
    Tree* Find();
    
  private:
    unsigned m_depth;
    Tree* m_father;
    Cell* m_data;
  };


}
#endif
