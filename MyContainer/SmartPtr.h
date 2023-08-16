#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <functional>

template<class T>
class auto_ptr
{
public:
	auto_ptr(T* ptr)
		:_ptr(ptr)
	{}

	~auto_ptr()
	{
		if (_ptr)
		{

			std::cout << "delete:" << _ptr << std::endl;
			delete _ptr;
		}
	}

	//管理权转移
	auto_ptr(auto_ptr<T>* ap)
		:_ptr(ap->_ptr)
	{
		ap->_ptr = nullptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	T* _ptr;
};

template<class T>
class unique_ptr
{
public:
	unique_ptr(T* ptr)
		:_ptr(ptr)
	{}

	~unique_ptr()
	{
		if (_ptr)
		{
			std::cout << "delete:" << _ptr << std::endl;
			delete _ptr;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	//C++11的思路：语法直接支持
	unique_ptr(const unique_ptr<T>& up) = delete;
	unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;

private:
	//unique_ptr(const unique_ptr<T>& up);
	//unique_ptr<T>& operator=(const unique_ptr<T>& up);

private:
	T* _ptr;
};

namespace mhzly
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr)
			, _pcount(new int(1))
			, _pmtx(new mutex)
		{}

		template<class D>
		shared_ptr(T* ptr, D del)
			: _ptr(ptr)
			, _pcount(new int(1))
			, _pmtx(new mutex)
			, _del(del)
		{}

		~shared_ptr()
		{
			Release();
		}

		void Release()
		{
			_pmtx->lock();

			bool deleteFlag = false;

			if (--(*_pcount) == 0)
			{
				//std::cout << "delete:" << _ptr << std::endl;
				//delete _ptr;
				//delete _pcount;

				if (_ptr)
				{
					//删除器进行删除
					_del(_ptr);
				}
				delete _pcount;
				deleteFlag = true;
			}
			_pmtx->unlock();

			if (deleteFlag)
			{
				delete _pmtx;
			}
		}

		void AddCount()
		{
			_pmtx->lock();
			++(*_pcount);
			_pmtx->unlock();
		}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pcount(sp._pcount)
			, _pmtx(sp._pmtx)
		{
			AddCount();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr != sp._ptr)
			{
				Release();

				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;

				AddCount();
			}

			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T* get()
		{
			return _ptr;
		}

		int use_count()
		{
			return *_pcount;
		}

	private:
		T* _ptr;
		int* _pcount;
		mutex* _pmtx;

		//包装器
		function<void(T*)> _del = [](T* ptr) {
			cout << "lambda delete:" << ptr << endl;
			delete ptr;
			};
	};
}

template <class T>
class weak_ptr
{
public:
	weak_ptr()
		:_ptr(nullptr)
	{}

	weak_ptr(const mhzly::shared_ptr<T>& sp)
		:_ptr(sp.get())
	{}

	weak_ptr<T>& operator=(const mhzly::shared_ptr<T>& sp)
	{
		_ptr = sp.get();
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	T* get()
	{
		return _ptr;
	}

private:
	T* _ptr;
};