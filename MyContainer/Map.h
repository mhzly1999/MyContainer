#pragma once
#include "RBTree.h"

template<class K, class V>
class Map
{
	struct MapKeyOfT
	{
		const K& operator()(const pair<const K, V>& kv)
		{
			return kv.first;
		}
	};

public:
	typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;

	iterator begin()
	{
		return _t.begin();
	}
	
	iterator end()
	{
		return _t.end();
	}

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
		return ret.first->second;
	}

	pair<iterator, bool> insert(const pair<const K, V>& kv)
	{
		return _t.Insert(kv);
	}

private:
	RBTree<K, pair<const K, V>, MapKeyOfT> _t;
};