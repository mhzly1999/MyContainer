#pragma once

#include "RBTree.h"

template<class K>
class Set
{
	struct SetKeyOfT
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
public:
	typedef typename RBTree<K, K, SetKeyOfT>::const_itertaor iterator;
	typedef typename RBTree<K, K, SetKeyOfT>::const_itertaor const_iterator;


	iterator begin()
	{
		return _t.begin();
	}

		iterator end()
		{
		return _t.end();
	}

	pair<iterator, bool> insert(const K& key)
	{
		return _t.Insert(key);
	}
private:
	RBTree<K, K, SetKeyOfT> _t;
};