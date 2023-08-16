#include <string>
#include <mutex>
#include <iostream>
#include <vector>
using namespace std;

class Singleton
{
public:
	static Singleton* GetInstance()
	{
		//双检查加锁
		if (_ins == nullptr)
		{
			_imtx.lock();

			if (_ins == nullptr)
			{
				_ins = new Singleton;
			}

			_imtx.unlock();
		}

		return _ins;
	}

	//一般全局都要使用单例对象，所以单例对象一般不需要显示释放
	//有些特殊场景，想显示释放一下
	static void DelInstance()
	{
		_imtx.lock();
		if (_ins)
		{
			delete _ins;
			_ins = nullptr;
		}
		_imtx.unlock();
	}

	//单例对象回收
	class GC
	{
	public:
		~GC()
		{
			DelInstance();
		}
	};

	static GC _gc;

	void Add(const string& str)
	{
		_vmtx.lock();
		_v.push_back(str);
		_vmtx.unlock();
	}

	void Print()
	{
		_vmtx.lock();
		for (auto& e : _v)
		{
			cout<<e << endl;
		}
		cout << endl;
		_vmtx.unlock();
	}

	~Singleton()
	{
		//持久化
	}

private:

	//限制类外随意创建对象
	Singleton()
	{}

private:
	mutex _vmtx;
	vector<string> _v;

	static Singleton* _ins;
	static mutex _imtx;
};

Singleton* Singleton::_ins = nullptr;
mutex Singleton::_imtx;

Singleton::GC Singleton::_gc;