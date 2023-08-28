#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <memory>
#include <iostream>


class MyString
{
public:
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin() const
	{
		return _str;
	}

	const_iterator end() const
	{
		return _str + _size;
	}

	MyString(const char* str = "")
		:_size(strlen(str))
	{
		_capacity = _size == 0 ? 3 : _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}

	//MyString(const MyString& s)
	//	:_size(s._size)
	//	,_capacity(s._capacity)
	//{
	//	_str = new char[s._capacity + 1];
	//	strcpy(_str, s._str);
	//}

	//拷贝构造
	MyString(const MyString& s)
		:_str(nullptr)
	{
		std::cout << "MyString(const MyString& s) -- 深拷贝" << std::endl;

		MyString tmp(s._str);
		swap(tmp);
	}

	//移动构造
	MyString(MyString&& s)
		:_str(s._str)
	{
		std::cout << "MyString(MyString&& s) -- 移动拷贝" << std::endl;
		swap(s);
	}

	//赋值重载
	MyString& operator=(const MyString& s)
	{
		std::cout << "MyString& operator=(const MyString& s) --- 深拷贝" << std::endl;
		MyString tmp(s);
		swap(tmp);

		return *this;
	}

	//移动赋值
	//s1 = 将亡值
	MyString& operator=(MyString&& s)
	{
		std::cout<<"MysString& operator=(MyString&& s) --- 移动赋值"<<std::endl;
		swap(s);

		return *this;
	}

	//MyString& operator=(const MyString& s)
	//{
	//	if (this != &s)
	//	{
	//		/*	delete[]_str;
	//			_str = new char[s._capacity + 1];
	//			strcpy(_str, s._str);
	//			_size = s._size;
	//			_capacity = s._capacity;*/

	//		char* tmp = new char[s._capacity + 1];
	//		strcpy(tmp, s._str);
	//		delete[]_str;
	//		_str = tmp;

	//		_size = s._size;
	//		_capacity = s._capacity;
	//	}

	//	return *this;
	//}

	~MyString()
	{
		delete[]_str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	const char* c_str()
	{
		return _str;
	}

	const char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}

	size_t size() const
	{
		return _size;
	}

	size_t capacity() const
	{
		return _capacity;
	}

	bool operator>(const MyString& s) const
	{
		return strcmp(_str, s._str) > 0;
	}

	bool operator==(const MyString& s) const
	{
		return strcmp(_str, s._str) == 0;
	}
	bool operator>=(const MyString& s) const
	{
		return *this > s || s == *this;
	}
	bool operator<(const MyString& s) const
	{
		return !(*this >= s);
	}

	bool operator<=(const MyString& s) const
	{
		return !(*this > s);
	}
	bool operator!=(const MyString& s) const
	{
		return !(*this == s);
	}

	void resize(size_t n, char ch = '\0')
	{
		if (n < _size)
		{
			_size = n;
			_str[_size] = '\0';
		}

		else if (n > _size)
		{
			if (n > _capacity)
			{
				reserve(n);
			}

			size_t i = _size;
			while (i < n)
			{
				_str[i] = ch;
				++i;
			}

			_size = n;
			_str[_size] = '\0';
		}
	}

	void reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[]_str;

			_str = tmp;
			_capacity = n;
		}
	}

	void push_back(char ch)
	{
		insert(_size, ch);
	}

	void append(const char* str)
	{
		insert(_size, str);
	}

	MyString& operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}

	MyString& operator+=(const char* ch)
	{
		append(ch);
		return *this;
	}

	MyString& insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		if (_size + 1 > _capacity)
		{
			reserve(2 * _capacity);
		}
		size_t end = _size + 1;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}

		_str[pos] = ch;
		++_size;

		return *this;
	}

	MyString& insert(size_t pos, const char* str)
	{
		assert(pos <= _size);

		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}

		//挪动数据
		size_t end = _size + len;

		while (end > pos + len - 1);
		{
			_str[end] = _str[end - len];
			--end;
		}

		//拷贝插入
		strncpy(_str + pos, str, len);
		_size += len;

		return *this;
	}

	void swap(MyString& s)
	{
		std::swap(_str, s._str);
		std::swap(_capacity, s._capacity);
		std::swap(_size, s._size);
	}

	size_t find(char ch, size_t pos = 0)
	{
		assert(pos < _size);

		for (size_t i = pos; i < _size; ++i)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}

		return npos;
	}

	size_t find(const char* str, size_t pos = 0)
	{
		assert(pos < _size);

		char* p = strstr(_str + pos, str);

		if (p == nullptr)
		{
			return npos;
		}
		else
		{
			return p - _str;
		}
	}

	MyString& erase(size_t pos, size_t len = npos)
	{
		assert(pos < _size);

		if (len == npos || pos + len >= _size)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}

		return *this;
	}

	void clear()
	{
		_str[0] = '\0';
		_size = 0;
	}
private:
	char* _str;
	size_t _capacity;
	size_t _size;

	static const size_t npos;
};

const size_t MyString::npos = -1;


//void test()
//{
//	MyString s1("hello");
//
//	std::cout << s1[1] << std::endl;
//}

//int main()
//{
//	//test();
//}

//ostream& operator<<(ostream& out, const MyString& s)