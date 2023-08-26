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
//	typedef ReverseIterator<iterator, T&, T*> reverse_iterator;//T& ������ǵ�������ָ���Ԫ�ص�����, T* ������ǵ�������ָ���Ԫ�ص�ָ������, Ҳ����˵, ��������ָ���Ԫ�ص�������T
//	typedef ReverseIterator<iterator, const T&, const T*> const_reverse_iterator;//const T& ������ǵ�������ָ���Ԫ�ص�����, const T* ������ǵ�������ָ���Ԫ�ص�ָ������
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
//	Myvector(const Myvector<T>& V) //�������캯��
//	{
//		_start = new T[V.capacity()];
//		for (size_t i = 0; i < V.size(); ++i)
//		{
//			_start[i] = V._start[i]; // ����ԭ��������
//		}
//		_finish = _start + V.size(); // ����_finish
//		_end_of_storage = _start + V.capacity(); // ����_end_of_storage
//	}
//
//	template <class InputIterator>
//	Myvector(InputIterator first, InputIterator last)
//	{
//		//����û�п����µĿռ䣬ֻ�ǽ�first��last֮���Ԫ�ؿ�������Myvector��
//		//�����first��last�ǵ���������������ָ�룬���������first��last��ָ��
//		while (first != last)
//		{
//			push_back(*first);
//			++first;
//		}
//	}
//
//	//������ֵ���������
//	Myvector<T>& operator=(Myvector<T> V)
//	{
//		//�ִ�C++д��
//		//�����V��һ�����������V��һ����ֵ�������V��һ����ʱ����
//		swap(V);
//		return *this;
//	}
//
//	//��������
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
//		std::swap(_start, V._start); // ����_start
//		std::swap(_finish, V._finish); // ����_finish
//		std::swap(_end_of_storage, V._end_of_storage); //����_end_of_storage
//	}
//
//	void resize(size_t n, T val = T())
//	{
//		if (n < size())
//		{
//			//����ֱ��ɾ�����ݣ����ǽ�_finishָ���λ����ǰ�ƶ�n��λ��
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
//			size_t sz = size(); // ����ԭ����size
//			T* tmp = new T[n]; // �����¿ռ�
//			if (_start)//���_start��Ϊ��
//			{
//				for (size_t i = 0; i < sz; ++i)
//				{
//					tmp[i] = _start[i]; // ����ԭ��������
//				}
//				delete[] _start; // �ͷ�ԭ���Ŀռ�
//			}
//			_start = tmp; // ����_start
//			_finish = _start + sz; // ����_finish
//			_end_of_storage = _start + n; // ����_end_of_storage
//		}
//	}
//
//	void push_back(const T& val)
//	{
//		if (_finish == _end_of_storage)// ����ռ䲻����
//		{
//			size_t newcapacity = capacity() == 0 ? 1 : capacity() * 2;// ���ԭ���Ŀռ�Ϊ0, ��ô�¿ռ�Ϊ1, ����Ϊԭ����2��
//			reverse(newcapacity);// �����¿ռ�
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
//		//ȷ��pos�ĺϷ���
//		assert(pos >= _start);
//		assert(pos <= _finish);
//
//		if (_finish == _end_of_storage) //����������ˣ�����Ҫ����
//		{
//			size_t len = pos - _start;//����pos��λ��
//
//			reverse(capacity() == 0 ? 1 : capacity() * 2); //����
//
//			//���ݺ����pos,���posʧЧ������
//			pos = _start + len;
//		}
//
//		//�Ӻ���ǰ�ƶ�����
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
//	//ɾ��posλ�õ�Ԫ��
//	iterator erase(iterator pos)
//	{
//		//ȷ��pos�ĺϷ���
//		assert(pos >= _start);
//		assert(pos < _finish);
//
//		ierator start = pos + 1;
//		//��ǰ�����ƶ�����
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
//		//ȷ��pos�ĺϷ���
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
////˫��ѭ������
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
//	//���캯��
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