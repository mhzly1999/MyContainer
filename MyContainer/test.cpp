//#include <assert.h>
//
//template<typename T>
//class Myvector
//{
//public:
//	typedef T* iterator;
//	typedef const T* const_iterator;
//
//	Myvector()
//	{}
//
//	Myvector(size_t n, const T& val = T())
//	{
//		reserve(n);
//		for (size_t i = 0; i < n; ++i)
//		{
//			push_back(val);
//		}
//	}
//
//	Myvector(int n, const T& val = T())
//	{
//		reserve(n);
//		for (int i = 0; i < n; ++i)
//		{
//			push_back(val);
//		}
//	}
//
//	Myvector(const Myvector<T>& v)
//	{
//		_start = new T[v.capacity()];
//		for (size_t i = 0; i < v.size(); ++i)
//		{
//			_start[i] = v._start[i];
//		}
//		_finish = _start + v.size();
//		_end_of_storage = _start + v.capacity();
//	}
//
//
//	template <typename InputIterator>
//	Myvector(InputIterator first, InputIterator last)
//	{
//		while (first != last)
//		{
//			push_back(*first);
//			++first;
//		}
//	}
//
//	~Myvector()
//	{
//		delete[]_start;
//		_start = _finish = _end_of_storage = nullptr;
//	}
//
//	iterator begin()
//	{
//		return _start;
//	}
//
//	iterator end()
//	{
//		return _finish;
//	}
//
//	iterator begin() const
//	{
//		return _start;
//	}
//
//	iterator end() const
//	{
//		return _ end;
//	}
//
//	void resize(size_t n, const T& val = T())
//	{
//		if (n < size())
//		{
//			_finish = _start + n;
//		}
//		else
//		{
//			if (n > capacity())
//			{
//				reserve(n);
//			}
//			while (_finish != _start + n)
//			{
//				*_finish = val;
//				++_finish;
//			}
//		}
//	}
//
//	void reserve(size_t n)
//	{
//		if (n > capacity)
//		{
//			size_t sz = size();
//			T* tmp = new T[n];
//			if (_start)
//			{
//				for (size_t i = 0; i < sz; ++i)
//				{
//					tmp[i] = _start[i];
//				}
//				delete[]_start;
//			}
//			_start = tmp;
//			_finish = _start + sz;
//			_end_of_storage = _start + n;
//		}
//	}
//
//	void push_back(const T& x)
//	{
//		if (_finish == _end_of_storage)
//		{
//			reserve(capacity() == 0 ? 4 : capacity() * 2);
//		} 
//		*_finish = x;
//		++_finish;
//	}
//	
//	void pop_back()
//	{
//		assert(!empty());
//		--_finish;
//	}
//
//	iterator insert(iterator pos, const T& val)
//	{
//		assert(pos >= _start);
//		assert(pos <= _finish);
//
//		if (_finish == _end_of_storage)
//		{
//			size_t len = pos - _start;
//
//			reserve(capacity() == 0 ? 4 : capacity() * 2);
//
//			pos = _start + len;
//		}
//
//		iterator end = _finish - 1;
//		while (end >= pos)
//		{
//			*(end + 1) = *end;
//			end--;
//		}
//		*pos = val;
//		_finish++;
//
//		return pos;
//	}
//
//
//
//
//
//	iterator erase(iterator pos)
//	{
//		assert(pos >= _start);
//		assert(pos < _finish);
//
//		iterator strat = pos + 1;
//		while (start != _finish)
//		{
//			*(start - 1) = *start;
//			start++;
//		}
//
//		_finish--;
//
//		return pos;
//	}
//
//	size_t capacity() const
//	{
//		return _end_of_storage - _start;
//	}
//
//	size_t size() const
//	{
//		return _finish - _start;
//	}
//
//	bool empty()
//	{
//		return _start == _finish;
//	}
//
//	T& operator[](size_t pos)
//	{
//		assert(pos < size());
//
//		return _start[pos];
//	}
//
//	const T& operator[](size_t pos)
//	{
//		assert(pos < size());
//
//		return _start[pos];
//	}
//
//private:
//	iterator _start;
//	iterator _finish;
//	iterator _end_of_storage;
//};

#include "AVLTree.h"
#include "RBTree.h"
#include "Map.h"
#include "Set.h"

#include "HashTable.h"
int main()
{
	//Test_AVLTree2();
}