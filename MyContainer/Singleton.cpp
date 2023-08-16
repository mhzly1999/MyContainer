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
		//˫������
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

	//һ��ȫ�ֶ�Ҫʹ�õ����������Ե�������һ�㲻��Ҫ��ʾ�ͷ�
	//��Щ���ⳡ��������ʾ�ͷ�һ��
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

	//�����������
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
		//�־û�
	}

private:

	//�����������ⴴ������
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