#include "stdafx.h"
template<class T>
class stack
{
private:
	struct st
	{
		T _point;
		st *_next;
		st *_prev;
	};
	st *_first;
	int _size;
public:
	stack()
	{
		_first=NULL;
		_size = 0;
	}

	~stack()
	{
		delete []_first;
	}

	void push(T point)
	{
		_size++;
		st *tmp = new st;
		tmp->_point = point;
		tmp->_prev = NULL;
		if(_first == NULL)
		{
			tmp->_next = NULL;
			_first = tmp;
			return;
		}
		tmp->_next=_first;
		_first->_prev = tmp;
		_first = tmp;
	}

	void pop()
	{
		if(_size!=0)
		{
			_size--;
			st *tmp = new st;
			tmp = _first->_next;
			if(_first->_next!=NULL)
			{
				tmp->_prev = NULL;
			}
			_first = tmp;
		}
	}

	T get_el(int i)
	{
		st *tmp = new st;
		tmp = _first;
		for(int ix = 0;(ix<i-1)&(ix<_size);ix++)
		{
			tmp = tmp->_next;
		}
		return tmp->_point;
	}
};