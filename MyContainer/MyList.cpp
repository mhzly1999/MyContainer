#include <assert.h>
#include <utility>
#include <iostream>

template<class T>
struct list_node
{
	list_node<T>* _next;
	list_node<T>* _prev;
	T _data;

	list_node(const T& x = T())
		:_next(nullptr)
		,_prev(nullptr)
		,_data(x)
	{}
};

template<class T, class Ref, class Ptr>
struct __list_iterator
{
	typedef list_node<T> node;
	typedef __list_iterator<T, Ref, Ptr> self;
	node* _node;

	__list_iterator(node* n)
		:_node(n)
	{}

	Ref operator*()
	{
		return _node->_data;
	}
	
	Ptr operator->()
	{
		return &_node->_data;
	}

	self& operator++()
	{
		_node = _node->_next;

		return *this;
	}

	self operator++(int)
	{
		self tmp(*this);
		_node = _node->_next;

		return tmp;
	}

	self& operator--()
	{
		_node = _node->_prev;

		return _node;
	}

	self operator--()
	{
		self tmp(*this);
		_node = _node->prev;

		return tmp;
	}

	bool operator!=(const self& s)
	{
		return _node != s._node;
	}

	bool operator==(const self& s)
	{
		return _node == s._node;
	}
};


template <class T>
class MyList
{
	typedef list_node<T> node;
public:
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;

	iterator begin()
	{
		return iterator(_head->_next);
	}

	const_iterator begin() const
	{
		return const_iterator(_head->_next);
	}

	iterator end()
	{
		return iterator(_head);
	}

	const_iterator end() const
	{
		return const_iterator(_head);
	}

	void empty_init()
	{
		_head = new node;
		_head->_next = _head;
		_head->_prev = _head;
	}

	MyList()
	{
		empty_init();
	}

	template<class Iterator>
	MyList(Iterator first, Iterator last)
	{
		empty_init();

		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	void swap(MyList<T>& tmp)
	{
		std::swap(_head, tmp._head);
	}

	MyList(const MyList<T>& lt)
	{
		empty_init();

		MyList<T> tmp(lt.begin(), lt.end());
		swap(tmp);
	}

	MyList<T>& operator=(MyList<T> lt)
	{
		swap(lt);
		return *this;
	}

	~MyList()
	{
		clear();
		delete _head;
		_head = nullptr;
	}

	void clear()
	{
		iterator it = begin();
		while (it != end())
		{
			erase(it++);
		}
	}

	void push_back(const T& x)
	{
		insert(end(), x);
	}

	void push_front(const T& x)
	{
		insert(begin(), x);
	}

	void pop_back()
	{
		erase(--end());
	}

	void pop_front()
	{
		erase(begin());
	}

	void insert(iterator pos, const T& x)
	{
		node* cur = pos._node;
		node* prev = cur->_prev;

		node* new_node = new node(x);

		prev->_next = new_node;
		new_node->_prev = prev;
		new_node->_next = cur;
		cur->_prev = new_node;
	}

	iterator erase(iterator pos)
	{
		assert(pos != end());

		node* prev = pos._node->_prev;
		node* next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;
		delete pos._node;

		return iterator(next);
	}

private:
	node* _head;
};

//int main()
//{
//	int a = 3;
//	int b = 4;
//	std::swap(a, b);
//
//	std::cout << a << b << std::endl;
//}