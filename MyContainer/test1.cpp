//#include<assert.h>
//#include<iostream>
////#include<utility>
//#include"Iterator.h"
//
//using std::cout;
//using std::endl;
//
//template<typename T>
//class Myvector
//{
//public:
//	typedef T* iterator;
//	typedef const T* const_iterator;
//	typedef ReverseIterator<iterator, T&, T*> reverse_iterator;//T& 代表的是迭代器所指向的元素的类型, T* 代表的是迭代器所指向的元素的指针类型, 也就是说, 迭代器所指向的元素的类型是T
//	typedef ReverseIterator<iterator, const T&, const T*> const_reverse_iterator;//const T& 代表的是迭代器所指向的元素的类型, const T* 代表的是迭代器所指向的元素的指针类型
//
//
//	Myvector()
//	{}
//
//	Myvector(size_t n, const T& val = T())
//	{
//		reverse(n);
//		for (size_t i = 0; i < n; ++i)
//		{
//			push_back(val);
//		}
//	}
//
//	Myvector(int n, const T& val = T()) 
//	{
//		reverse(n);
//		for (int i = 0; i < n; ++i)
//		{
//			push_back(val);
//		}
//	}
//
//	Myvector(const Myvector<T>& V) //拷贝构造函数
//	{
//		_start = new T[V.capacity()];
//		for (size_t i = 0; i < V.size(); ++i)
//		{
//			_start[i] = V._start[i]; // 拷贝原来的数据
//		}
//		_finish = _start + V.size(); // 更新_finish
//		_end_of_storage = _start + V.capacity(); // 更新_end_of_storage
//	}
//
//	template <class InputIterator>
//	Myvector(InputIterator first, InputIterator last)
//	{
//		//这里没有开辟新的空间，只是将first和last之间的元素拷贝到了Myvector中
//		//这里的first和last是迭代器，迭代器是指针，所以这里的first和last是指针
//		while (first != last)
//		{
//			push_back(*first);
//			++first;
//		}
//	}
//
//	//拷贝赋值运算符重载
//	Myvector<T>& operator=(Myvector<T> V)
//	{
//		//现代C++写法
//		//这里的V是一个对象，这里的V是一个右值，这里的V是一个临时对象
//		swap(V);
//		return *this;
//	}
//
//	//析构函数
//	~Myvector()
//	{
//		if (_start)
//		{
//			delete[] _start;
//			_start = _finish = _end_of_storage = nullptr;
//		}
//	}
//
//	iterator begin()
//	{
//		return _start;
//	}
//
//	iterator begin() const
//	{
//		return _start;
//	}
//
//	iterator end()
//	{
//		return _finish;
//	}
//
//	iterator end() const
//	{
//		return _finish;
//	}
//
//	reverse_iterator rbegin()
//	{
//		return reverse_iterator(_finish);
//	}
//
//	reverse_iterator rend()
//	{
//		return reverse_iterator(_start);
//	}
//
//	void swap(Myvector<T>& V)
//	{
//		std::swap(_start, V._start); // 交换_start
//		std::swap(_finish, V._finish); // 交换_finish
//		std::swap(_end_of_storage, V._end_of_storage); //交换_end_of_storage
//	}
//
//	void resize(size_t n, T val = T())
//	{
//		if (n < size())
//		{
//			//不是直接删除数据，而是将_finish指向的位置向前移动n个位置
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
//	void reverse(size_t n)
//	{
//		if (n > capacity())
//		{
//			size_t sz = size(); // 保存原来的size
//			T* tmp = new T[n]; // 申请新空间
//			if (_start)//如果_start不为空
//			{
//				for (size_t i = 0; i < sz; ++i)
//				{
//					tmp[i] = _start[i]; // 拷贝原来的数据
//				}
//				delete[] _start; // 释放原来的空间
//			}
//			_start = tmp; // 更新_start
//			_finish = _start + sz; // 更新_finish
//			_end_of_storage = _start + n; // 更新_end_of_storage
//		}
//	}
//
//	void push_back(const T& val)
//	{
//		if (_finish == _end_of_storage)// 如果空间不够了
//		{
//			size_t newcapacity = capacity() == 0 ? 1 : capacity() * 2;// 如果原来的空间为0, 那么新空间为1, 否则为原来的2倍
//			reverse(newcapacity);// 申请新空间
//		}
//		*_finish = val;
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
//		//确保pos的合法性
//		assert(pos >= _start);
//		assert(pos <= _finish);
//
//		if (_finish == _end_of_storage) //如果容量满了，就需要扩容
//		{
//			size_t len = pos - _start;//计算pos的位置
//
//			reverse(capacity() == 0 ? 1 : capacity() * 2); //扩容
//
//			//扩容后更新pos,解决pos失效的问题
//			pos = _start + len;
//		}
//
//		//从后往前移动数据
//		iterator end = _finish - 1;
//		while (end >= pos)
//		{
//			*(end + 1) = *end;
//			end--;
//		}
//		*pos = val;
//		++_finish;
//
//		return pos;
//	}
//
//	//删除pos位置的元素
//	iterator erase(iterator pos)
//	{
//		//确保pos的合法性
//		assert(pos >= _start);
//		assert(pos < _finish);
//
//		ierator start = pos + 1;
//		//从前往后移动数据
//		while (start != _finish)
//		{
//			*(start - 1) = *start;
//			++start;
//		}
//
//		--_finish;
//
//		return pos;
//	}
//
//	size_t size() const
//	{
//		return _finish - _start;
//	}
//
//	size_t capacity() const
//	{
//		return _end_of_storage - _start;
//	}
//
//	bool empty()
//	{
//		return _start == _finish;
//	}
//
//	T& operator[](size_t pos)
//	{
//		//确保pos的合法性
//		assert(pos < size());
//
//		return _start[pos];
//	}
//
//	const T& operator[](size_t pos) const
//	{
//		assert(pos < size());
//
//		return _start[pos];
//	}
//private:
//	iterator _start = nullptr;
//	iterator _finish = nullptr;
//	iterator _end_of_storage = nullptr;
//};
//


//#include <iostream>
//#include <utility>
//#include <assert.h>
//#include "Iterator.h"
//
//template<class T>
////双向循环链表
//struct list_node
//{
//	list_node<T>* _next;
//	list_node<T>* _prev;
//	T _data;
//
//	list_node(const T& x = T())
//		:_next(nullptr)
//		, _prev(nullptr)
//		, _data(x)
//	{}
//};
//
//template<class T, class Ref, class Ptr>
//struct __list_iterator
//{
//	typedef list_node<T> node;
//	typedef __list_iterator<T, Ref, Ptr> self;
//	node* _node;
//
//	//构造函数
//	__list_iterator(node* n)
//		:_node(n)
//	{}
//
//	Ref operator*()
//	{
//		return &_node->_data;
//	}
//
//	Ptr operator->()
//	{
//		return &_node->_data;
//	}
//
//	self& operator++()
//	{
//		_node = _node->_next;
//
//		return *this;
//	}
//
//	self& operator++(int)
//	{
//		self tmp(*this);
//		_node = _node->_next;
//
//		return tmp;
//	}
//
//	self& operator--()
//	{
//		_node = _node->_prev;
//
//		return *this;
//	}
//
//	self& operator--(int)
//	{
//		self tmp(*this);
//		_node = _node->_prev;
//
//		return tmp;
//	}
//
//	bool operator!=(const self& s)
//	{
//		return _node != s._node;
//	}
//
//	bool operator==(const self& s)
//	{
//		return _node == s._node;
//	}
//};
//
//template<class T>
//class MyList
//{
//	typedef list_node<T> node;
//public:
//	typedef __list_iterator<T, T&, T*> iterator;
//	typedef __list_iterator<T, const T&, const T*> const_iterator;
//	typedef ReverseIterator<iterator, T&, T*> reverse_iterator;
//	typedef ReverseIterator<iterator, const T&, const T*> const_reverse_iterator;
//
//	iterator begin()
//	{
//		return iterator(_head->_next);
//	}
//
//	const_iterator begin() const
//	{
//		return const_iterator(_head->_next);
//	}
//
//	iterator end()
//	{
//		return iterator(_head);
//	}
//
//	const_iterator end() const
//	{
//		return const_iterator(_head);
//	}
//
//	reverse_iterator rbegin()
//	{
//		return reverse_iterator(end());
//	}
//
//	reverse_iterator rend()
//	{
//		return reverse_iterator(begin());
//	}
//
//	void empty_init()
//	{
//		_head = new node;
//		_head->next = _head;
//		_head->_prev = _head;
//	}
//
//	MyList()
//	{
//		empty_init();
//	}
//
//	template<class Iterator>
//	MyList(Iterator first, Iterator last)
//	{
//		empty_init();
//		while (first != last)
//		{
//			push_back(*first);
//			++first;
//		}
//	}
//
//	void swap(MyList<T>& tmp)
//	{
//		std::swap(_head, tmp._head);
//	}
//
//	MyList(const MyList<T>& It)
//	{
//		empty_init();
//
//		MyList<T> tmp(It.begin(), It.end());
//		swap(tmp);
//	}
//
//	MyList<T>& operator=(MyList<T> It)
//	{
//		swap(It);
//		return *this;
//	}
//
//	~MyList()
//	{
//		clear();
//		delete _head;
//		_head = nullptr;
//	}
//
//	void clear()
//	{
//		iterator it = begin();
//
//		while (it != end())
//		{
//			erase(it++);
//		}
//	}
//
//	void push_back(const T& x)
//	{
//		insert(end(), x);
//	}
//
//	void push_front(const T& x)
//	{
//		insert(begin(), x);
//	}
//
//	void pop_back()
//	{
//		erase(--end());
//	}
//
//	void pop_front()
//	{
//		erase(begin());
//	}
//
//	iterator insert(iterator pos, const T& x)
//	{
//		node* cur = pos._node;
//		node* prev = cur->_prev;
//
//		node* newnode = new node(x);
//
//		prev->_next = newnode;
//		newnode->_prev = prev;
//
//		newnode->_next = cur;
//		cur->_prev = newnode;
//
//		return iterator(newnode);
//	}
//
//	iterator erase(iterator pos)
//	{
//		assert(pos != end());
//
//		node* cur = pos._node;
//		node* prev = cur->_prev;
//		node* next = cur->_next;
//
//		prev->_next = next;
//		next->_prev = prev;
//
//		delete cur;
//
//		return iterator(next);
//	}
//
//private:
//	node* _head;
//};

//#include <list>
//
//using namespace std;
//
//template<class T, class Container = list<T>>
//class MyQueue
//{
//public:
//	void push(const T& x)
//	{
//		_con.push_back(x);
//	}
//
//	void pop()
//	{
//		_con.pop_front();
//	}
//
//	const T& front()
//	{
//		return _con.front();
//	}
//
//	const T& back()
//	{
//		return _con.back();
//	}
//
//	size_t size()
//	{
//		return _con.size();
//	}
//
//	bool empty()
//	{
//		return _con.empty();
//	}
//private:
//	Container _con;
//};