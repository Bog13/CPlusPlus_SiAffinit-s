#include <Tree.hpp>
#include <Maze.hpp>

namespace MazeGenerator
{
  Tree::Tree(Cell* data): m_father(nullptr), m_data(data)
  {
    m_depth = 0;
  }

  void Tree::Union(Tree *target)
  {
    Tree* target_root = target->Find();
    Tree* root = Find();

    if( root->m_depth < target_root->m_depth )
      {
	root->m_father = target_root;
      }
    else if( root->m_depth > target_root->m_depth )
      {
	target_root->m_father = root;
      }
    else
      {
	root->m_father = target_root;
	target_root->m_depth++;
      }
  }

  Tree* Tree::Find()
  {
    if( m_father == nullptr )
      {
	return this;
      }
    m_father = m_father->Find();
    return m_father;
  }

  Tree::~Tree()
  {
    
  }
}
