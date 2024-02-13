#pragma once
#include <memory>
#include "Node.h"
template <class T>
class forwardList;

template <class T>
class Iterator;

template <class T>
class Iterator : std::iterator<std::forward_iterator_tag, T>
{
	friend class forwardList<T>;

private:
	Node<T>* node;
	Iterator(Node<T>* node_)
		: node(node_) {}
public:
	Iterator(const Iterator& Rop)
		: node(Rop.node) {}

	Iterator& operator=(const Iterator& Rop)
	{
		if (this != &Rop)
		{
			node = Rop.node;
		}
		return *this;
	}

	
	typename Iterator::reference operator*() const
	{
		return (node->_value);
	}

	
	operator Iterator<const T>()
	{
		return Iterator<T>(node);
	}
};