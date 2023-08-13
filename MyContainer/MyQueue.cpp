#include <list>

using namespace std;

template<class T, class Container = list<T>>
class queue
{
public:
	void push(const T& x)
	{
		_con.push_back(x);
	}

	void pop()
	{
		_con.pop_front();
	}

	const T& front()
	{
		return _con.front();
	}

	const T& back()
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