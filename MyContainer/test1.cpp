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

//#define _CRT_SECURE_NO_WARNINGS 1
//
//#include <assert.h>
//#include <memory>
//#include <iostream>
//
//class Mystring
//{
//public:
//	typedef char* iterator;
//	typedef const char* const_iterator;
//
//	iterator begin()
//	{
//		return _str;
//	}
//
//	iterator end()
//	{
//		return _str + _size;
//	}
//
//	const iterator begin() const
//	{
//		return _str;
//	}
//
//	const iterator end() const
//	{
//		return _str + _size;
//	}
//
//	//默认构造函数
//	Mystring(const char* str = "")
//	{
//		if (nullptr == str)
//		{
//			assert(false);
//			return;
//		}
//
//		_size = strlen(str);
//		_capacity = _size == 0 ? 4 : _size;
//		strcpy(_str, str);
//	}
//
//	////拷贝构造函数
//	//Mystring(const Mystring& str)
//	//	:_size(str._size)
//	//	, _capacity(str._capacity)
//	//{
//	//	_str = new char[_capacity + 1];
//	//	strcpy(_str, str._str);
//	//}
//
//	//现代写法的拷贝构造函数
//
//	Mystring(const Mystring& str)
//		:_str(nullptr)
//	{
//		std::cout << "Mystring(const Mystring& str)  --深拷贝" << std::endl;
//		Mystring tmp(str._str);
//		swap(tmp);
//	}
//
//	//移动构造
//	Mystring(Mystring&& str)
//		:_str(nullptr)
//	{
//		std::cout << "Mystring(Mystring&& str)  --移动拷贝" << std::endl;
//		swap(str);
//	}
//
//	////赋值运算符重载
//	//Mystring& operator=(const Mystring& s)
//	//{
//	//	if (this != &s)
//	//	{
//	//		//delete[] _str;
//	//		//_str = new char[s._capacity + 1];
//	//		//strcpy(_str, s._str);
//	//		//_size = s._size;
//	//		//_capacity = s._capacity;
//
//	//		char* tmp = new char[s._capacity + 1];
//	//		strcpy(tmp, s._str);
//	//		delete[] _str;
//	//		_str = tmp;
//
//	//		_size = s._size;
//	//		_capacity = s._capacity;
//	//	}
//
//	//	return *this;
//	//}
//
//	//现代写法的赋值运算符重载
//	Mystring& operator=(const Mystring& s)
//	{
//		std::cout << "Mystring& operator=(const Mystring& s)  --深拷贝" << std::endl;
//		Mystring tmp(s);
//		swap(tmp);
//
//		return *this;
//	}
//
//	//移动赋值运算符重载
//	Mystring& operator=(Mystring&& s)
//	{
//		std::cout << "Mystring& operator=(Mystring&& s) --移动赋值" << std::endl;
//		swap(s);
//
//		return *this;
//	}
//
//	//析构函数
//	~Mystring()
//	{
//		assert(_str);
//		delete[] _str;
//		_str = nullptr;
//		_size = _capacity = 0;
//	}
//
//	const char* c_str()
//	{
//		return _str;
//	}
//
//	const char& operator[](size_t pos) const
//	{
//		assert(pos < _size);
//		return _str[pos];
//	}
//
//	size_t size() const
//	{
//		return _size;
//	}
//
//	size_t capacity() const
//	{
//		return _capacity;
//	}
//
//	bool operator>(const Mystring& s) const
//	{
//		//size_t i = 0;
//		//while (i < _size && i < s._size)
//		//{
//		//	if (_str[i] > s._str[i])
//		//		return true;
//		//	else if (_str[i] < s._str[i])
//		//		return false;
//		//	else
//		//		++i;
//		//}
//
//		//if (i == _size)
//		//	return false;
//		//else
//		//	return true;
//
//		return strcmp(_str, s._str) > 0;
//	}
//
//	bool operator<(const Mystring& s) const
//	{
//		//size_t i = 0;
//		//while (i < _size && i < s._size)
//		//{
//		//	if (_str[i] < s._str[i])
//		//		return true;
//		//	else if (_str[i] > s._str[i])
//		//		return false;
//		//	else
//		//		++i;
//		//}
//
//		//if(i == s._size)
//		//	return false;
//		//else
//		//	return true;
//
//		//return strcmp(_str, s._str) < 0;
//		return !(*this >= s);
//	}
//
//	bool operator==(const Mystring& s) const
//	{
//		//if (_size != s._size)
//		//	return false;
//
//		//size_t i = 0;
//		//while (i < _size && i < s._size)
//		//{
//		//	if (_str[i] != s._str[i])
//		//		return false;
//		//	else
//		//		++i;
//		//}
//
//		//return true;
//
//		return strcmp(_str, s._str) == 0;
//	}
//
//	bool operator<=(const Mystring& s) const
//	{
//		return *this < s || *this == s;
//	}
//
//	bool operator>=(const Mystring& s) const
//	{
//		return *this > s || *this == s;
//	}
//
//	bool operator!=(const Mystring& s) const
//	{
//		return !(*this == s);
//	}
//
//	void resize(size_t n, char ch = '\0')
//	{
//		if (n < _size)
//		{
//			_size = n;
//			_str[_size] = '\0';
//		}
//
//		else if (n > _size)
//		{
//			if (n > _capacity)  //空间不够
//			{
//				reserve(n);
//			}
//
//			size_t i = _size;
//			while (i < n)
//			{
//				_str[i] = '\0';
//				i++;
//			}
//
//			_size = n;
//			_str[_size] = '\0'
//		}
//	}
//
//	void reserve(size_t n)
//	{
//		if (n > _capacity)
//		{
//			char* tmp = new char[n + 1];
//			strcpy(tmp, _str);
//			delete[] _str;
//
//			_str = tmp;
//			_capacity = n;
//		}
//	}
//
//	void push_back(char ch)
//	{
//		insert(_size, ch);
//	}
//
//	void append(const char* str)
//	{
//		insert(_size, str);
//	}
//
//	Mystring& operator+=(const char ch)
//	{
//		push_back(ch);
//		return *this;
//	}
//
//	Mystring& operator+=(const char* str)
//	{
//		//insert(_size, str);
//		append(str);
//		return *this;
//	}
//
//	Mystring& insert(size_t pos, char ch)
//	{
//		assert(pos <= _size);
//		if (_size + 1 > _capacity)
//		{
//			reserve(2 * _capacity);
//		}
//		size_t end = _size + 1;
//		while (end > pos)
//		{
//			_str[end] = _str[end - 1];
//			end--;
//		}
//
//		_str[pos] = ch;
//		++_size;
//
//		return *this;
//	}
//
//	Mystring& insert(size_t pos, const char* str)
//	{
//		assert(pos <= _size);
//		size_t len = strlen(str);
//		if (_size + len > _capacity)
//		{
//			reserve(_size + len);
//		}
//
//		//挪动数据
//		size_t end = _size + len;
//		while (end > pos)
//		{
//			_str[end] = _str[end - len];
//			end--;
//		}
//
//		//拷贝插入
//		strncpy(_str + pos, str, len);
//		_size += len;
//
//		return *this;
//	}
//
//	size_t find(char ch, size_t pos = 0)
//	{
//		assert(pos < _size);
//
//		for (size_t i = pos; i < _size; ++i)
//		{
//			if (_str[i] == ch)
//				return i;
//		}
//
//		return npos;
//	}
//
//	size_t find(const char* str, size_t pos = 0)
//	{
//		assert(pos < _size);
//
//		char* p = strstr(_str + pos, str);
//
//		if (p == nullptr)
//		{
//			return npos;
//		}
//		else
//		{
//			return p - _str;
//		}
//	}
//
//	Mystring& erase(size_t pos, size_t len = npos)
//	{
//		assert(pos < _size);
//
//		if (len == npos || pos + len >= _size)
//		{
//			_str[pos] = '\0';
//			_size = pos;
//		}
//		else
//		{
//			strcpy(_str + pos, _str + pos + len);
//			_size -= len;
//		}
//
//		return *this;
//	}
//
//	void clear()
//	{
//		_str[0] = '\0';
//		_size = 0;
//	}
//
//	void swap(Mystring& s)
//	{
//		std::swap(_str, s._str);
//		std::swap(_size, s._size);
//		std::swap(_capacity, s._capacity);
//	}
//private:
//	char* _str;
//	size_t _size;
//	size_t _capacity;
//
//	static const size_t npos;
//};
//
//const size_t Mystring::npos = -1;

//#include <vector>
//#include <utility>
//#include <iostream>
//
//template<class T>
//struct less
//{
//	bool operator()(const T& x, const T& y)
//	{
//		return x < y;
//	}
//};
//
//template<class T>
//struct greater
//{
//	bool operator()(const T& x, const T& y)
//	{
//		return x > y;
//	}
//};
//
//template<class T, class Container = std::vector<T>, class Compare = less<T>>
//class priority_queue
//{
//public:
//	void adjust_up(int child)
//	{
//		Compare _com;
//
//		int parent = (child - 1) / 2;
//		while (child > 0)
//		{
//			if (com(_con[parent], _con[child]))
//			{
//				std::swap(_con[parent], _con[child]);
//				child = parent;
//				parent = (child - 1) / 2;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//
//	void adjust_down(int parent)
//	{
//		size_t child = parent * 2 + 1;
//		while (child < _con.size())
//		{
//			Comparen com;
//			if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))//找到左右孩子中的最大值
//			{
//				child++;
//			}
//			if (com(_con[parent], _con[child]))
//			{
//				std::swap(_con[parent], _con[shild]);
//				parent = child;
//				child = parent * 2 + 1;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//
//	void push(const T& x)
//	{
//		_con.push_back(x);
//		adjust_up(_con.size() - 1);
//	}
//
//	void pop()
//	{
//		std::swap(_con[0], _con[_con.size() - 1]);
//		_con.pop_back();
//		adjust_down(0);
//	}
//
//	const T& top()
//	{
//		return _con[0];
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

//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//template<class T, class Container = vector<T>>
//class Stack
//{
//public:
//	void push(const T& x)
//	{
//		_con.push_back(x);
//	}
//
//	void pop()
//	{
//		_con.pop_back();
//	}
//
//	const T& top()
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

//#include <string>
//#include <mutex>
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		//双重检测
//		if (_ins == nullptr)
//		{
//			_imtx.lock();
//			if (_ins == nullptr)
//			{
//				_ins = new Singleton;
//			}
//			_imtx.unlock();
//		}
//
//		return _ins;
//	}
//
//	//一般全局都要使用单例对象，所以单例对象一般不需要显示的调用
//	//有些特殊场景，想显示释放一下
//	static void DelInstance()
//	{
//		_imtx.lock();
//		if (_ins)
//		{
//			delete _ins;
//			_ins = nullptr;
//		}
//		_imtx.unlock();
//	}
//
//	//单例对象回收
//	class GC
//	{
//	public:
//		~GC()
//		{
//			DelInstance();
//		}
//	};
//
//	static GC _gc;
//
//	void Add(const string& str)
//	{
//		_vmtx.lock();
//		_v.push_back(str);
//		_vmtx.unlock();
//	}
//
//	void Print()
//	{
//		_vmtx.lock();
//		for (auto& e : _v)
//		{
//			cout << e << endl;
//		}
//		cout<< endl;
//		_vmtx.unlock();
//	}
//	~Singleton()
//	{
//		//持久化
//	}
//
//private:
//	//声明私有但不定义，确保外部无法调用构造函数
//	Singleton()
//	{}
//
//	//声明私有但不定义，确保外部无法调用拷贝构造函数
//	Singleton(const Singleton& s)
//	{}
//
//	//声明私有但不定义，确保外部无法调用赋值运算符重载函数
//	Singleton& operator=(const Singleton& s)
//	{}
//
//private:
//	mutex _vmtx;
//	vector<string> _v;
//
//	static Singleton* _ins;
//	static mutex _imtx;
//};
//
//Singleton* Singleton::_ins = nullptr;
//mutex Singleton::_imtx;
//
//Singleton::GC Singleton::_gc;

//#include <iostream>
//#include <time.h>
//#include <assert.h>
//
//using namespace std;
//
//template<class K, class V>
//struct AVLTreeNode
//{
//	AVLTreeNode<K, V>* _left;
//	AVLTreeNode<K, V>* _right;
//	AVLTreeNode<K, V>* _parent;
//	pair<K, V> _kv;
//	int _bf;   //平衡因子
//
//
//	//构造函数
//	AVLTreeNode(const pair<K, V>& kv)
//		:_left(nullptr)
//		, _right(nullptr)
//		, _parent(nullptr)
//		, _kv(kv)
//		, _bf(0)
//	{}
//};
//
//template<class K, class V>
//class AVLTree
//{
//	typedef AVLTreeNode<K, V> Node;
//public:
//	bool Insert(const pair<K, V>& kv)
//	{
//		if (_root == nullptr)
//		{
//			_root = new Node(kv);
//			return true;
//		}
//
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_kv.first < kv.first)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (cur->_kv.first > kv.first)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				return false;
//			}
//		}
//
//		cur = new Node(kv);
//		if (parent->_kv.first > kv.first)
//		{
//			parent->_left = cur;
//		}
//		else
//		{
//			parent->_right = cur;
//		}
//		cur->_parent = parent;
//
//		//更新平衡因子
//		while (parent)
//		{
//			if (cur == parent->_right)
//			{
//				parent->_bf++;
//			}
//			else
//			{
//				parent->_bf--;
//			}
//
//			if (parent->_bf == 1 || parent->_bf == -1)
//			{
//				//继续向上更新
//				parent = parent->_parent;
//				cur = cur->_parent;
//			}
//			else if (parent->_bf == 0)
//			{
//				break;
//			}
//			else if (parent->_bf == 2 || parent->_bf == -2)
//			{
//				//需要旋转处理 
//				//1、让这颗子树平衡
//				//2、降低这颗子树的高度
//				if (parent->_bf == 2 && cur->_bf == 1)
//				{
//					//左旋
//					RotateL(parent);
//				}
//				else if (parent->_bf == -2 && cur->_bf == -1)
//				{
//					//右单旋
//					RotateR(parent);
//				}
//				else if (parent->_bf == 2 && cur->_bf == -1)
//				{
//					//先右旋，再左旋
//					RotateRL(parent);
//				}
//				else if (parent->_bf == -2 && cur->_bf == 1)
//				{
//					//先左旋，再右旋
//					RotateLR(parent);
//				}
//				else
//				{
//					assert(false);
//				}
//				break;
//			}
//			else
//			{
//				assert(false);
//			}
//		}
//
//		return true;
//	}
//
//	void InOrder()
//	{
//		_InOrder(_root);
//		cout << endl;
//	}
//
//	bool IsBalance()
//	{
//		return _IsBalance(_root);
//	}
//
//	int Height()
//	{
//		return _Height(_root);
//	}
//private:
//	void _Height(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return 0;
//		}
//
//		int leftH = _Height(root->_left);
//		int rightH = _Height(root->_right);
//
//		return leftH > rightH ? leftH + 1 : rightH + 1;
//	}
//
//	bool _IsBalance(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return true;
//		}
//
//		int leftH = _Height(root->_left);
//		int rightH = _Height(root->_right);
//
//		if (rightH - leftH != root->_bf)
//		{
//			cout << root->_kv.first << "节点平衡因子错误" << endl;
//			return false;
//		}
//
//		return abs(leftH - rightH) < 2
//			&& _IsBalance(root->_left)
//			&& _isBalance(root->_right);
//	}
//	void RotateL(Node* parent)
//	{
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//
//		parent->_right = subRL;
//		if (subRL)
//		{
//			subRL->_parent = parent;
//		}
//
//		Node* ppnode = parent->_parent;
//
//		subR->_left = parent;
//		parent->_parent = subR;
//
//		if (ppnode == nullptr)
//		{
//			_root == subR;
//			_root->_parent = nullptr;
//		}
//		else
//		{
//			if (ppnode->_left == parent)
//			{
//				ppnode->_left = subR;
//			}
//			else
//			{
//				ppnode->_right = subR;
//			}
//			subR->_parent = ppnode;
//		}
//		parent->_bf = subR->_bf = 0;
//	}
//
//	void RotateR(Node* parent)
//	{
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//
//		parent->_left = subLR;
//		if (subLR)
//		{
//			subLR->_parent = parent;
//		}
//
//		Node* ppnode = parent->_parent;
//
//		subL->_right = parent;
//		parent->_parent = subL;
//
//		if (parent == _root)
//		{
//			_root = subL;
//			_root->_parent = nullptr;
//		}
//		else
//		{
//			if (ppnode->_left = parent)
//			{
//				ppnode->_left = subL;
//			}
//			else
//			{
//				ppnode->_right = subL;
//			}
//			subL->_parent = ppnode;
//		}
//		subL->_bf = parent->_bf = 0;
//	}
//
//	void RotateLR(Node* parent)
//	{
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//		int bf = subLR->_bf;
//
//		RotateL(parent->_left);
//		RotateR(parent);
//
//		if (bf == 1)
//		{
//			parent->_bf = 0;
//			subLR->_bf = 0;
//			subL->_bf = -1;
//		}
//		else if (bf == -1)
//		{
//			parent->_bf = 1;
//			subLR->_bf = 0;
//			subL->_bf = 0;
//		}
//		else if (bf == 0)
//		{
//			parent->_bf = 0;
//			subLR->_bf = 0;
//			subL->_bf = 0;
//		}
//		else
//		{
//			assert(false);
//		}
//	}
//
//	void RotateRL(Node* parent)
//	{
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//		int bf = subRL->_bf;
//
//		RotateR(parent->_right);
//		RotateL(parent);
//
//		if (bf == 1)
//		{
//			subR->_bf = 0;
//			parent->_bf = -1;
//			subRL->_bf = 0;
//		}
//		else if (bf == -1)
//		{
//			subR->_bf = 1;
//			parent->_bf = 0;
//			subRL->_bf = 0;
//		}
//		else if (bf == 0)
//		{
//			subR->_bf = 0;
//			parent->_bf = 0;
//			subRL->_bf = 0;
//		}
//	}
//
//	void _InOrder(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return;
//		}
//		_InOrder(root->_left);
//		cout << root->_kv.first << " ";
//		_InOrder(root->_right);
//	}
//private:
//	Node* _root = nullptr;
//};