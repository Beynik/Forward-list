#pragma once
#include <memory>
#include <functional>
#include "iterator.h"

template <class T>
using SplinPredicate = std::function<bool(const T& value_)>;

template <class T>
class forwardList
{
private:
	std::unique_ptr<Node<T>> Start;
	size_t size;
public:
	forwardList();
	forwardList(size_t size_, const T& value_);
	forwardList(const forwardList<T>& Rop);
	forwardList(forwardList<T>&& Rop);
	forwardList(std::initializer_list<T> init);
	~forwardList();

	Iterator<T> begin();
	Iterator<T> end();
	Iterator<T> before_begin();
	const Iterator<T> cbegin() const;
	const Iterator<T> cend() const;
	const Iterator<T> cbefore_begin() const;

	bool empty();

	void push_front(const T& value_);
	void push_front(T&& value_);
	void pop_front();
	size_t Size() const;
	void swap(forwardList& Rop) noexcept;
	void clear();
	
	forwardList<T> splin_when(SplinPredicate<T> condition);
};




template<class T>
inline forwardList<T>::forwardList()
	: Start(new Node<T>(T())),
	size(0) {}

template<class T>
inline forwardList<T>::forwardList(size_t size_, const T& value_)
	: Start(new Node<T>(value_))
{
	while (size != size_)
	{
		push_front(value_);
	}
}



template<class T>
inline forwardList<T>::forwardList(const forwardList<T>& Rop)
	:  Start(new Node<T>(Rop.Start->value)), size(0)
{
	push_front(Rop.cbegin().node->value);
	Node<T>* curr = begin().node;
	Node<T>* Rop_curr = Rop.cbegin().node->pNext.get();
	while (size != Rop.size)
	{
		curr->pNext.reset(new Node<T>(Rop_curr->value));
		curr = curr->pNext.get();
		Rop_curr = Rop_curr->pNext.get();
		++size;
	}
}

template<class T>
inline forwardList<T>::forwardList(forwardList<T>&& Rop)
	: Start(new Node<T>(std::move(Rop.Start->value))), size(Rop.size)
{
	Start->pNext = std::move(Rop.Start->pNext);
	Rop.size = 0;
	Rop.Start->pNext = nullptr;
}

template<class T>
inline forwardList<T>::forwardList(std::initializer_list<T> Rop)
	: Start(new Node<T>(T())),
	size(0)
{
	if (std::begin(Rop) != std::end(Rop))
	{
		auto elem = std::begin(Rop);
		push_front(*elem);
		Node<T>* curr = begin().node;
		for (++elem; elem != std::end(Rop); ++elem)
		{
			curr->pNext.reset(new Node<T>(*elem));
			curr = curr->pNext.get();
			++size;
		}
	}
}



template<class T>
inline forwardList<T>::~forwardList()
{
	clear();
}



template<class T>
inline Iterator<T> forwardList<T>::begin()
{
	Iterator<T> k = Start->pNext.get();
	return k;
}

template<class T>
inline Iterator<T> forwardList<T>::end()
{
	Iterator<T> k = nullptr;
	return k;
}

template<class T>
inline Iterator<T> forwardList<T>::before_begin()
{
	Iterator<T> k = Start.get();
	return k;
	
}

template<class T>
inline const Iterator<T> forwardList<T>::cbegin() const
{
	const Iterator<T> k = Start->pNext.get();
	return k;
	
}

template<class T>
inline const Iterator<T>  forwardList<T>::cend() const
{
	const Iterator<T> k = nullptr;
	return k;
}

template<class T>
inline const Iterator<T>  forwardList<T>::cbefore_begin() const
{
	const Iterator<T> k = Start.get();
	return k;
}
template<class T>
inline bool  forwardList<T>::empty()
{
	return (size == 0);
}


template<class T>
inline void forwardList<T>::push_front(const T& value_)
{
	Node<T>* tmp = Start->pNext.release();
	Start->pNext.reset(new Node<T>(value_, tmp));
	++size;
}

template<class T>
inline void forwardList<T>::push_front(T&& value_)
{
	Start->pNext.reset(new Node<T>(std::move(value_), std::move(Start->pNext)));
	++size;
}

template<class T>
inline void forwardList<T>::pop_front()
{
	Start->pNext = std::move(Start->pNext->pNext);
	--size;
}

template<class T>
inline size_t forwardList<T>::Size() const
{
	return size;
}



template<class T>
inline void forwardList<T>::swap(forwardList& Rop) noexcept
{
	Start.swap(Rop.Start);
	std::swap(size, Rop.size);
}

template<class T>
inline void forwardList<T>::clear()
{
	while (size)
	{
		pop_front();
	}
}

template<class T>
inline forwardList<T> forwardList<T>::splin_when(SplinPredicate<T> condition)
{
	size_t counter = 0;
	for (auto it = before_begin(); it.node->pNext != nullptr; it++)
	{
		forwardList<T> tmp;
		if (condition(it.node->pNext->value))
		{
			tmp.size = size - counter;
			size = counter;
			tmp.Start->pNext = (std::move(it.node->pNext));
			return std::move((tmp));
		}
		++counter;
	}
	return std::move((forwardList<T>()));
}