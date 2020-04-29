#ifndef __OCTREE_HPP__
# define __OCTREE_HPP__

#include <map>
#include <string>

# define ABS(x) (((x) < 0) ? (-x) : (x))

class Coords
{
public:
  int x;
  int y;
  int z;

  Coords(int x, int y, int z) : x(x), y(y), z(z){}
  ~Coords(){}

  bool operator<(Coords const &c) const
  {
    return (this->x < c.x ||
	    (this->x == c.x &&
	     (this->y < c.y ||
	      (this->y == c.y && this->z < c.z))));

  }
};

template<typename T>
class Node
{
  T	*elem;
  int	x;
  int	y;
  int	z;
  unsigned int size;
  unsigned int nbChilds;
  Node<T> *lastChild;

public:
  Node<T> *childs[8];

public:
  Node(T *elem, int x, int y, int z, unsigned int size);
  Node(Node<T> const &node);
  ~Node();

  unsigned int getNbChilds() const;
  Node<T> *getLastChild() const;
  T *getElem();
  T const *getElem() const;
  unsigned int getSize() const;
  int getX() const;
  int getY() const;
  int getZ() const;

  void addChild(Node<T> &node);
  Node<T> *findChild(int x, int y, int z) const;
  void delChild(int x, int y, int z);
};

template<typename T>
class Octree
{
  Node<T> *node[8];
  std::map<Coords, T> map;

public:
  Octree();
  ~Octree();
  Octree(Octree const &);

  void displayContent(Node<T> *node = 0, std::string space = "- ") const;
  void push(T const &elem, int x, int y, int z);

  void pop(int x, int y, int z);
  T *find(int x, int y, int z) const;
  T *find(int x, int y, int z);

private:
  int		findOctreeId(int x, int y, int z) const;
  Node<T>	*findOctree(int x, int y, int z) const;
  void		delBranch(int id, Node<T> &delNode, int x, int y, int z);
  bool		isContain(Node<T> const &node, int x, int y, int z) const;
  Node<T>	*searchChild(Node<T> const &node, int x, int y, int z) const;
  Node<T>	*createChild(Node<T> &node, T *elem, int x, int y, int z);
  Node<T>	*createParent(Node<T> &node) const;
  void		freeOctree(Node<T> &node);
};

#include "Octree.ipp"

#endif /* !__OCTREE_HPP__ */
