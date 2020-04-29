#ifndef  _OCTREE_IPP_
# define _OCTREE_IPP_

/////// Class Node ////////

#include <iostream>

template<typename T>
Node<T>::Node(T *elem, int x, int y, int z, unsigned int size)
  : elem(elem), x(x), y(y), z(z), size(size), nbChilds(0), lastChild(0)
{
  this->childs[0] = 0;
  this->childs[1] = 0;
  this->childs[2] = 0;
  this->childs[3] = 0;
  this->childs[4] = 0;
  this->childs[5] = 0;
  this->childs[6] = 0;
  this->childs[7] = 0;
}

template<typename T>
Node<T>::Node(Node<T> const &node)
    : elem(node.elem), x(node.x), y(node.y), z(node.z), size(node.size), nbChilds(node.nbChilds), lastChild(node.lastChild)
{
  this->childs[0] = 0;
  this->childs[1] = 0;
  this->childs[2] = 0;
  this->childs[3] = 0;
  this->childs[4] = 0;
  this->childs[5] = 0;
  this->childs[6] = 0;
  this->childs[7] = 0;
}

template<typename T>
Node<T>::~Node()
{}

template<typename T>
unsigned int Node<T>::getNbChilds() const
{
  return (this->nbChilds);
}

template<typename T>
Node<T> *Node<T>::getLastChild() const
{
  return (this->lastChild);
}

template<typename T>
T *Node<T>::getElem()
{
  return (this->elem);
}

template<typename T>
T const *Node<T>::getElem() const
{
  return (this->elem);
}

template<typename T>
unsigned int Node<T>::getSize() const
{
  return (this->size);
}

template<typename T>
int Node<T>::getX() const
{
  return (this->x);
}

template<typename T>
int Node<T>::getY() const
{
  return (this->y);
}

template<typename T>
int Node<T>::getZ() const
{
  return (this->z);
}

template<typename T>
void Node<T>::addChild(Node<T> &node)
{
  int x = (node.getX() - this->x) >> node.getSize();
  int y = (node.getY() - this->y) >> node.getSize();
  int z = (node.getZ() - this->z) >> node.getSize();

  this->childs[(x << 2) + (y << 1) + z] = &node;
  this->lastChild = &node;
  this->nbChilds++;
}

template<typename T>
Node<T> *Node<T>::findChild(int x, int y, int z) const
{
  unsigned int size;
  int x2;
  int y2;
  int z2;

  if (this->size < 1)
    return (0);
  size = this->size - 1;
  x2 = ((x >> size << size) - this->x) >> size;
  y2 = ((y >> size << size) - this->y) >> size;
  z2 = ((z >> size << size) - this->z) >> size;
  return (this->childs[(x2 << 2) + (y2 << 1) + z2]);
}

template<typename T>
void Node<T>::delChild(int x, int y, int z)
{
  unsigned int size;
  int i;
  int cpt;
  int x2;
  int y2;
  int z2;

  size = this->size - 1;
  x2 = ((x >> size << size) - this->x) >> size;
  y2 = ((y >> size << size) - this->y) >> size;
  z2 = ((z >> size << size) - this->z) >> size;
  cpt = (x2 << 2) + (y2 << 1) + z2;
  if (this->childs[cpt] == this->lastChild)
    {
      this->childs[cpt] = 0;
      if (this->nbChilds == 1)
	this->lastChild = 0;
      else
	{
	  for (i = 0; i < 8 && this->childs[i] == 0; ++i);
	  if (i < 8)
	    this->lastChild = this->childs[i];
	}
    }
  else
    this->childs[cpt] = 0;
  this->nbChilds--;
}

/////// Class Octree ////////

template<typename T>
Octree<T>::Octree()
{
  this->node[0] = 0;
  this->node[1] = 0;
  this->node[2] = 0;
  this->node[3] = 0;
  this->node[4] = 0;
  this->node[5] = 0;
  this->node[6] = 0;
  this->node[7] = 0;
}

template<typename T>
Octree<T>::Octree(Octree const &octree)
{
  this->node[0] = octree.node[0];
  this->node[1] = octree.node[1];
  this->node[2] = octree.node[2];
  this->node[3] = octree.node[3];
  this->node[4] = octree.node[4];
  this->node[5] = octree.node[5];
  this->node[6] = octree.node[6];
  this->node[7] = octree.node[7];
}

template<typename T>
Octree<T>::~Octree()
{
  int cpt;

  for (cpt = 0; cpt < 8; cpt++)
    {
      if (this->node[cpt])
	this->freeOctree(*this->node[cpt]);
    }
  this->map.clear();
}

template<typename T>
void Octree<T>::displayContent(Node<T> *node, std::string space) const
{
  int cpt;
  bool b;

  if (!node)
    {
      std::cout << std::endl;
      b = true;
      for (cpt = 0; cpt < 8; ++cpt)
	{
	  if (this->node[cpt])
	    {
	      b = false;
	      this->displayContent(this->node[cpt], space);
	    }
	}
      if (b)
	std::cout << "<vide>" << std::endl;
    }
  else
    {
      std::cout << space << "(" << node->getX() << ", " << node->getY() << ", " << node->getZ() << ") - size = " << (1 << node->getSize());
//      if (node->getElem())
//	std::cout << " - content : " << *node->getElem();
      std::cout << std::endl;
      for (cpt = 0; cpt < 8; ++cpt)
	{
	  if (node->childs[cpt])
	    this->displayContent(node->childs[cpt], space + "- ");
	}
    }
}

template<typename T>
void Octree<T>::push(T const &ele, int x, int y, int z)
{
  int id = this->findOctreeId(x, y, z);
  Node<T> *node;
  Node<T> *tmpNode;

  T &elem = (*(this->map.insert(std::pair<Coords, T>(Coords(x, y, z), ele))).first).second;
  x = ABS(x);
  y = ABS(y);
  z = ABS(z);
  if (this->node[id])
    {
      while (!this->isContain(*this->node[id], x, y, z))
	this->node[id] = this->createParent(*this->node[id]);
      node = this->node[id];
      while ((tmpNode = this->searchChild(*node, x, y, z)) != 0)
	node = tmpNode;
      if (node->getSize() > 0)
	{
	  while (node->getSize() > 1)
	    node = this->createChild(*node, 0, x, y, z);
	  this->createChild(*node, &elem, x, y, z);
	}
    }
  else
    this->node[id] = new Node<T>(&elem, x, y, z, 0);
}

template<typename T>
void Octree<T>::delBranch(int id, Node<T> &delNode, int x, int y, int z)
{
  Node<T> *node;
  Node<T> *tmpNode;

  node = &delNode;
  tmpNode = this->searchChild(*node, x, y, z);
  node->delChild(x, y, z);
  node = tmpNode;
  while (node->getSize())
    {
      tmpNode = node->getLastChild();
      delete node;
      node = tmpNode;
    }
  delete node;
  if (this->node[id]->getNbChilds() == 1)
    {
      while (this->node[id]->getNbChilds() == 1)
  	{
  	  node = this->node[id];
  	  this->node[id] = this->node[id]->getLastChild();
  	  delete node;
  	}
    }
}

template<typename T>
void Octree<T>::pop(int x, int y, int z)
{
  int x2;
  int y2;
  int z2;
  int id = this->findOctreeId(x, y, z);
  Node<T> *node;
  Node<T> *tmpNode;

  x2 = x;
  y2 = y;
  z2 = z;
  x = ABS(x);
  y = ABS(y);
  z = ABS(z);
  if (this->node[id])
    {
      node = this->node[id];
      tmpNode = 0;
      if (this->isContain(*node, x, y, z))
	{
	  while (node->getSize())
	    {
	      if (node->getNbChilds() > 1)
		tmpNode = node;
	      node = this->searchChild(*node, x, y, z);
	      if (!node)
		return ;
	    }
	  if (this->isContain(*node, x, y, z))
	    {
	      this->map.erase(Coords(x2, y2, z2));
	      if (tmpNode)
		this->delBranch(id, *tmpNode, x, y, z);
	      else if (this->node[id] == node)
		{
		  delete this->node[id];
		  this->node[id] = 0;
		}
	      else
		this->delBranch(id, *this->node[id], x, y, z);
	    }
	}
    }
}

template<typename T>
T *Octree<T>::find(int x, int y, int z) const
{
  int id = this->findOctreeId(x, y, z);
  Node<T> *node;

  x = ABS(x);
  y = ABS(y);
  z = ABS(z);
  if (this->node[id])
    {
      node = this->node[id];
      if (this->isContain(*node, x, y, z))
	{
	  while (node->getSize())
	    {
	      node = this->searchChild(*node, x, y, z);
	      if (!node)
		return (0);
	    }
	  if (this->isContain(*node, x, y, z))
	    return (node->getElem());
	}
    }
  return (0);
}

template<typename T>
T *Octree<T>::find(int x, int y, int z)
{
  int id = this->findOctreeId(x, y, z);
  Node<T> *node;

  x = ABS(x);
  y = ABS(y);
  z = ABS(z);
  if (this->node[id])
    {
      node = this->node[id];
      if (this->isContain(*node, x, y, z))
	{
	  while (node->getSize())
	    {
	      node = this->searchChild(*node, x, y, z);
	      if (!node)
		return (0);
	    }
	  if (this->isContain(*node, x, y, z))
	    return (node->getElem());
	}
    }
  return (0);
}

template<typename T>
bool Octree<T>::isContain(Node<T> const &node, int x, int y, int z) const
{
  int size = 1 << node.getSize();

  return (x >= node.getX() && x < node.getX() + size &&
	  y >= node.getY() && y < node.getY() + size &&
	  z >= node.getZ() && z < node.getZ() + size);
}

template<typename T>
Node<T>	*Octree<T>::searchChild(Node<T> const &node, int x, int y, int z) const
{
  return (node.findChild(x, y, z));
}

template<typename T>
Node<T>	*Octree<T>::createChild(Node<T> &node, T *elem, int x, int y, int z)
{
  Node<T>	*newNode;
  unsigned int size = node.getSize() - 1;

  newNode = new Node<T>(elem, x >> size << size,
			y >> size << size,
			z >> size << size, size);
  node.addChild(*newNode);
  return (newNode);
}

template<typename T>
Node<T>	*Octree<T>::createParent(Node<T> &node) const
{
  Node<T>	*newNode;
  unsigned int size = node.getSize() + 1;

  newNode = new Node<T>(0, node.getX() >> size << size,
			node.getY() >> size << size,
			node.getZ() >> size << size, size);
  newNode->addChild(node);
  return (newNode);
}

template<typename T>
int Octree<T>::findOctreeId(int x, int y, int z) const
{
  int x2 = x >> 31 & 1;
  int y2 = y >> 31 & 1;
  int z2 = z >> 31 & 1;

  return ((x2 << 2) + (y2 << 1) + z2);
}

template<typename T>
Node<T>	*Octree<T>::findOctree(int x, int y, int z) const
{
  return (this->node[this->findOctreeId(x, y, z)]);
}

template<typename T>
void Octree<T>::freeOctree(Node<T> &node)
{
  unsigned int cpt;
  unsigned int nbChilds;

  for (nbChilds = cpt = 0; cpt < 8 && nbChilds < node.getNbChilds(); ++cpt)
    {
      if (node.childs[cpt])
	{
	  this->freeOctree(*node.childs[cpt]);
	  ++nbChilds;
	}
    }
  delete &node;
}

#endif /* !_OCTREE_IPP_ */
