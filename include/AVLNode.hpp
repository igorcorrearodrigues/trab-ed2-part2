#ifndef AVLNODE_HPP
#define AVLNODE_HPP

#include <cstddef>

struct AVLNode
{
	AVLNode *esq;
	AVLNode *dir;
	size_t info;
	size_t fbal; 

	AVLNode():
		esq(nullptr),
		dir(nullptr),
		info(),
		fbal()
	{
	}
};

#endif // AVLNODE_HPP