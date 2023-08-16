#pragma once

#include "HashTable.h"

template <class K, class V, class Hash = HashFunc<K>>
class Unordered_Map
{
	struct MapKeyOfT
	{
		const K& operator()(const pair<K, V>& kv)
		{
			return kv.first;
		}
	};
public:
	typedef typename HashBucket::HashTable<K, pair<K, V>, MapKeyOfT, Hash>::iterator iterator;
	typedef typename HashBucket::HashTable<K, pair<K, V>, MapKeyOfT, Hash>::const_iterator const_iterator;

	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

	const_iterator begin() const
	{
		return _ht.begin();
	}

	const_iterator end() const
	{
		return _ht.end();
	}

	pair<iterator, bool> Insert(const pair<K, V>& kv)
	{
		return _ht.Insert(kv);
	}

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
		return ret.first->second;
	}

	iterator find(const K& key)
	{
		return _ht.Find(key);
	}

	bool erase(const K& key)
	{
		return _ht.Erase(key);
	}

private:
	HashBucket::HashTable<K, pair<K, V>, MapKeyOfT, Hash> _ht;
};