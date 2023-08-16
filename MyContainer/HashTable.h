#pragma once

#include <vector>
#include <iostream>

using namespace std;

enum State
{
	EMPTY,
	EXIST,
	DELETE
};

template <class K, class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = EMPTY;
};

template<class K, class V>
class HashTable
{
public:


	bool Insert(const pair<K, V>& kv)
	{
		if (Find(kv.first))
		{
			return false;
		}

		//负载因子超过0.7就扩容
		//if((double)_n/(double)_table.size() >= 0.7)
		if (_tables.size() == 0 || _n * 10 / _tables.size() >= 0.7)
		{
			//size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			//vector<HashData> newtables(newsize);
			////遍历旧表，重新映射到新表
			//for (auto& data : _tables)
			//{
			//	if (data._state == EXIST)
			//	{
			//		//重新算在新表的位置
			//		size_t i = 1;
			//		size_t index = hashi;
			//		while (newtables[index]._state == EXIST)
			//		{
			//			index = hashi + i;
			//			index% = newtables.size();
			//			++i;
			//		}

			//		newtables[index]._kv = data._kv;
			//		newtables[index]._state = EXIST;
			//	}
			//}

			//_tables.swap(newtables);

			size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			HashTable<K, V> newht;
			newht._tables.resize(newsize);

			//遍历旧表，重新映射到新表
			for (auto& data : _tables)
			{
				if (data._state == EXIST)
				{
					newht.Insert(data._kv);
				}
			}
			_tables.swap(newht._tables);
		}
		size_t hashi = kv.first % _tables.size();

		//线性探测
		size_t i = 1;
		size_t index = hashi;
		while (_tables[index]._state == EXIST)
		{
			index = hashi + i;
			index %= _tables.size();
			++i;
		}

		_tables[index]._kv = kv;
		_tables[index]._state = EXIST;
		_n++;

		return true;
	}

	HashData<K, V>* Find(const K& key)
	{
		if (_tables.size() == 0)
		{
			return false;
		}

		size_t hashi = key % _tables.size();

		//线性探测
		size_t i = 1;
		size_t index = hashi;
		while (_tables[index]._state != EMPTY)
		{
			if (_tables[index]._state == EXIST
				&& _tables[index]._kv.first == key)
			{
				return &_tables[index];
			}

			index = hashi + i;
			index %= _tables.size();
			++i;

			//如果已经查找一圈，那么说明全是存在+删除
			if (index == hashi)
			{
				break;
			}
		}

		return nullptr;
	}

	bool Erase(const K& key)
	{
		HashData<K, V>* ret = Find(key);
		if (ret)
		{
			ret->_state = DELETE;
			--_n;
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	vector<HashData<K, V>> _tables;
	size_t _n = 0; //存储的数据个数
};

template<class  K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//特化
template<>
struct HashFunc<string>
{
	//BKDR
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto ch : s)
		{
			hash += ch;
			hash *= 31;
		}

		return hash;
	}
};

namespace HashBucket
{
	template<class T>
	struct HashNode
	{
		HashNode<T>* _next;
		T _data;

		HashNode(const T& data)
			:_next(nullptr)
			, _data(data)
		{}
	};

	//前置声明
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
	struct __HashIterator
	{
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyOfT, Hash> HT;
		typedef __HashIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		typedef __HashIterator<K, T, T&, T*, KeyOfT, Hash> Iterator;

		Node* _node;
		const HT* _ht;

		__HashIterator(Node* node, const HT* ht)
			:_node(node)
			, _ht(ht)
		{}

		__HashIterator(const Iterator& it)
			:_node(it._node)
			, _ht(it._ht)
		{}

		Ptr operator*()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		Self& operator++()
		{
			if (_node->_next != nullptr)
			{
				_node = _node->_next;
			}
			else
			{
				//找下一个不为空的桶
				KeyOfT kot;
				Hash hash;

				//算出我当前的桶位置
				size_t hashi = hash(kot(_node->_data)) % _ht->_tables.size();
				++hashi;
				while (hashi < _ht->_tables.size())
				{
					if (_ht->_tables[hashi])
					{
						_node = _ht->_tables[hashi];
						break;
					}
					else
					{
						++hashi;
					}
				}

				//没有找到不为空的桶
				if (hashi == _ht->_tables.size())
				{
					_node = nullptr;
				}
			}
			return *this;
		}
	};

	template<class K, class T, class KeyOfT, class Hash>
	class HashTable
	{
		template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
		friend struct __HashIterator;

		typedef HashNode<T> Node;
	public:
		typedef __HashIterator<K, T, T&, T*, KeyOfT, Hash> iterator;
		typedef __HashIterator<K, T, const T&, const T*, KeyOfT, Hash> const_iterator;

		iterator begin()
		{
			Node* cur = nullptr;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				cur = _tables[i];
				if (cur)
				{
					break;
				}
			}

			return iterator(cur, this);
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		const_iterator begin() const
		{
			Node* cur = nullptr;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				cur = _tables[i];
				if (cur)
				{
					break;
				}
			}
			return const_iterator(cur, this);
		}

		const_iterator end() const
		{
			return const_iterator(nullptr, this);
		}

		~HashTable()
		{
			for (auto& cur : _tables)
			{
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				cur = nullptr;
			}
		}

		iterator Find(const K& key)
		{
			if (_tables.size() == 0)
			{
				return end();
			}

			KeyOfT kot;
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return iterator(cur, this);
				}

				cur = cur->_next;
			}

			return end();
		}

		bool Erase(const K& key)
		{
			Hash hash;
			KeyOfT kot;
			size_t hashi = hash(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					return true;
				}

				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}

			return false;
		}

		size_t GetNextPrime(size_t prime)
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};

			size_t i = 0;
			for (; i < __stl_num_primes; ++i)
			{
				if (__stl_prime_list[i] > prime)
				{
					return __stl_prime_list[i];
				}
			}

			return __stl_prime_list[i];
		}

		pair<iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;
			iterator it = Find(kot(data));
			if (it != end())
			{
				return make_pair(it, false);
			}

			Hash hash;

			//负载因子==1时扩容
			if (_n == _tables.size())
			{
				/*			size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
							HashTable<K, V> newht;
							newht.resize(newsize);
							for (auto cur : _tables)
							{
								while (cur)
								{
									newht.Insert(cur->_kv);
									cur = cur->_next;
								}
							}

							_tables.swap(newht._tables);*/

							//size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				size_t newsize = GetNextPrime(_tables.size());
				vector<Node*> newtables(newsize, nullptr);
				//for(Node*& cur : _tables)
				for (auto& cur : _tables)
				{
					while (cur)
					{
						Node* next = cur->_next;
						size_t hashi = hash(kot(cur->_data)) % newtables.szie();

						//头插到新表
						cur->_next = newtables[hashi];
						newtables[hashi] = cur;

						cur = next;
					}
				}

				_tables.swap(newtables);
			}

			size_t hashi = hash(kot(data)) % _tables.size();

			//头插
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;

			++_n;
			return make_pair(iterator(newnode, this), false);
		}

		size_t MaxBucketSize()
		{
			size_t max = 0;
			for (auto cur : _tables)
			{
				size_t count = 0;
				while (cur)
				{
					++count;
					cur = cur->_next;
				}

				if (count > max)
				{
					max = count;
				}
			}

			return max;
		}

	private:
		vector<Node*> _tables; //指针数组
		size_t _n; //元素个数
	};
}
