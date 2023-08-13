#include <iostream>
//#include <list>
#include <vector>
//#include <stack>

using namespace std;

template<class T, class Container = vector<T>>
class Mystack
{
public:

	void push(const T& x)
	{
		_con.push_back(x);
	}

	void pop()
	{
		_con.pop_back();
	}

	const T& top()
	{
		return _con.back();
	}

	size_t size()
	{
		return _con.size();
	}

	bool empty()
	{
		return _con.empty();
	}

private:
	Container _con;
};