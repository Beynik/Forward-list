#pragma once
#include <memory>
template <class T>
class forwardList;

template <class T>
class Iterator;

template <class T>
class Node
{
	friend class Iterator<T>;
	friend class forwardList<T>;
private:
	T value;
	std::unique_ptr<Node<T>> pNext;
	Node(const T& value_, Node<T>* next = nullptr)
		: value(value_),
		pNext(next)
	{}

	Node(T&& value_, std::unique_ptr<Node<T>>&& next)
		: value(std::move(value_)), pNext(std::move(next))
	{
		next = nullptr;
	}
};