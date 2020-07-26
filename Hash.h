#include "afx.h"



class MyHashSet {
public:

	void add(int key) {
		if (contains(key))
			return;

		int index = key % SIZE;
		bucket& buc = m_buckets[index];

		if (buc.size == NODES)
		{
			map<int, int> temp;
			for (auto ukey : buc.ulist)
			{
				temp.insert(make_pair(ukey, ukey));
			}

			temp.insert(make_pair(key, key));

			buc.ulist.~list();

			new (&buc.umap) map<int, int>(temp);

			buc.ismap = true;
		}
		else if (buc.size < NODES)
		{
			buc.ulist.push_back(key);
		}
		else
		{
			buc.umap.insert(make_pair(key, key));
		}

		buc.size++;
	}

	void remove(int key) {
		int index = key % SIZE;
		bucket& buc = m_buckets[index];

		if (buc.ismap)
		{
			buc.umap.erase(key);
		}
		else
		{
			buc.ulist.remove(key);
		}

		buc.size--;
	}

	/** Returns true if this set contains the specified element */
	bool contains(int key) {
		int index = key % SIZE;
		bucket& buc = m_buckets[index];

		if (buc.ismap)
		{
			return buc.umap.find(key) != buc.umap.end();
		}
		else
		{
			return find(buc.ulist.begin(), buc.ulist.end(), key) != buc.ulist.end();
		}
	}

private:
	struct bucket
	{
		int size;

		union
		{
			list<int> ulist;
			map<int, int> umap;
		};

		bool ismap;

		bucket() : size(0), ismap(false)
		{
			new (&ulist) list<int>();
		}

		~bucket()
		{
			if (ismap)
			{
				umap.~map<int, int>();
			}
			else
			{
				ulist.~list<int>();
			}
		}

	};

	enum
	{
		SIZE = 100,
		NODES = 8,
	};

	bucket m_buckets[SIZE];

};
