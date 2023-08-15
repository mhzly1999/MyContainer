#include <vector>
#include <utility>
#include <iostream>

template<class T>
struct less
{
	bool operator()(const T& x, const T& y)
	{
		return x < y;
	}
};

template<class T>
struct greater
{
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};

template<class T, class Container = std::vector<T>, class Compare = less<T>>
class priority_queue
{
public:
	void adjust_up(int child)
	{
		Compare com;

		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (com(_con[parent], _con[child]))
			{
				std::swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void adjust_down(int parent)
	{
		size_t child = parent * 2 + 1;
		while (child < _con.size())
		{
			Compare com;

			if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
			{
				++child;
			}

			if (com(_con[parent], _con[child]))
			{
				std::swap(_con[parent], _con[child]);
				parent = child;
				child = parent * 2 + 1;
			}

			else
			{
				break;
			}
		}
	}

	void push(const T& x)
	{
		_con.push_back(x);
		adjust_up(_con.size() - 1);
	}

	void pop()
	{
		std::swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();
		adjust_down(0);
	}

	const T& top()
	{
		return _con[0];
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

void test_priority_queue()
{
	//priority_queue<int, vector<int>, greater<int>> pq;
	priority_queue<int> pq;
	//priority_queue<int, deque<int>> pq;
	pq.push(1);
	pq.push(0);
	pq.push(5);
	pq.push(2);
	pq.push(1);
	pq.push(7);

	while (!pq.empty())
	{
		std::cout << pq.top() << " ";
		pq.pop();
	}
	std::cout << std::endl;
}

//int main()
//{
//	test_priority_queue();
//}