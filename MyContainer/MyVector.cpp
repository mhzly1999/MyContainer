#include <assert.h>
#include <iostream>
#include <utility>
#include "Iterator.h"

using std::cout;
using std::endl;


template<typename T>
class Myvector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef ReverseIterator<iterator, T&, T*> reverse_iterator;
	typedef ReverseIterator<iterator, const T&, const T*> const_reverse_iterator;

	Myvector()
	{}

	Myvector(size_t n, const T& val = T())
	{
		reserve(n);
		for (size_t i = 0; i < n; ++i)
		{
			push_back(val);
		}
	}

	Myvector(int n, const T& val = T())
	{
		reserve(n);
		for (int i = 0; i < n; ++i)
		{
			push_back(val);
		}
	}

	Myvector(const Myvector<T>& v)
	{
		_start = new T[v.capacity()];
		for (size_t i = 0; i < v.size(); ++i)
		{
			_start[i] = v._start[i];
		}
		_finish = _start + v.size();
		_end_of_storage = _start + v.capacity();
	}

	template <class InputIterator>
	Myvector(InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	Myvector<T>& operator=(Myvector<T> v)
	{
		swap(v);
		return *this;
	}

	~Myvector()
	{
		delete[]_start;
		_start = _finish = _end_of_storage = nullptr;
	}

	iterator begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	iterator begin() const
	{
		return _start;
	}

	iterator end() const
	{
		return _finish;
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	void swap(Myvector<T>& v)
	{
		std::swap(_start, v._start);
		std::swap(_finish, v._finish);
		std::swap(_end_of_storage, v._end_of_storage);
	}

	void resize(size_t n, T val = T())
	{
		if (n < size())
		{
			//删除数据
			_finish = _start + n;
		}
		else
		{
			if (n > capacity)
			{
				reserve(n);
			}
			while (_finish != _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}
	}

	void reserve(size_t n)
	{
		if (n > capacity())
		{
			size_t sz = size();
			T* tmp = new T[n];
			if (_start)
			{
				for (size_t i = 0; i < sz; ++i)
				{
					tmp[i] = _start[i];
				}
				delete[]_start;
			}
			_start = tmp;
			_finish = _start + sz;
			_end_of_storage = _start + n;
		}
	}

	void push_back(const T& x)
	{
		if (_finish == _end_of_storage)
		{
			reserve(capacity() == 0 ? 4 : capacity() * 2);
		}

		*_finish = x;
		++_finish;
	}

	void pop_back()
	{
		assert(!empty());

		--_finish;
	}

	iterator insert(iterator pos, const T& val)
	{
		assert(pos >= _start);
		assert(pos <= _finish);

		if (_finish == _end_of_storage)
		{
			size_t len = pos - _start;

			reserve(capacity() == 0 ? 4 : capacity() * 2);

			//扩容后更新pos, 解决pos失效的问题
			pos = _start + len;
		}

		iterator end = _finish - 1;
		while (end >= pos)
		{
			*(end + 1) = *end;
			--end;
		}

		*pos = val;
		++_finish;

		return pos;
	}

	iterator erase(iterator pos)
	{
		assert(pos >= _start);
		assert(pos < _finish);

		iterator start = pos + 1;
		while (start != _finish)
		{
			*(start - 1) = *start;
			++start;
		}

		--_finish;

		return pos;
	}

	size_t capacity() const
	{
		return _end_of_storage - _start;
	}

	size_t size() const
	{
		return _finish - _start;
	}

	bool empty()
	{
		return _start == _finish;
	}

	T& operator[](size_t pos)
	{
		assert(pos < size());

		return _start[pos];
	}

	const T& operator[](size_t pos) const
	{
		assert(pos < size());

		return _start[pos];
	}

private:
	iterator _start = nullptr;
	iterator _finish = nullptr;
	iterator _end_of_storage = nullptr;
};

//int main()
//{
//	//Myvector<int> v1(5, 5);
//	//Myvector<int> v2(v1);
//
//	//for (int i = 0; i < v1.size(); ++i)
//	//{
//	//	cout << v1[i] << " " ;
//	//}
//
//	//cout << endl;
//
//	//for (int i = 0; i < v2.size(); ++i)
//	//{
//	//	cout << v2[i] << " ";
//	//}
//
//	Myvector<int> v1(7);
//
//	int n = v1.size();
//
//	cout << n << endl;
//
//	for (int i = 0; i < v1.size(); ++i)
//	{
//		cout << v1[i] << " " ;
//	}
//
//}