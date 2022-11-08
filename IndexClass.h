#pragma once

#include <YRPPCore.h>
#include <GenericList.h>

/*
* IndexClass, most impl from CCR
* --secsome
*/

// TKey is always int in WW's code
template<typename TKey, typename TValue>
class IndexClass
{
public:
	IndexClass(void);
	~IndexClass(void);

	constexpr bool AddIndex(TKey id, const TValue& data);
	bool AddIndex(TKey id, TValue&& data);
	bool RemoveIndex(TKey id);
	bool IsPresent(TKey id) const;
	int Count() const;
	const TValue& FetchIndex(TKey id) const;
	TValue& FetchIndex(TKey id);
	void Clear();
	bool Reverse(int nAmount);
	inline void Sort();

	struct NodeElement
	{
		NodeElement& operator=(const NodeElement& node) { ID = node.ID; Data = node.Data; return *this; }
		bool operator<(const NodeElement& another) const { return ID < another.ID; }
		bool operator==(const NodeElement& another) const { return ID == another.ID; }

		TKey ID;
		TValue Data;
	};

	NodeElement* IndexTable;
	int IndexCount;
	int IndexSize;
	bool IsSorted;
	PROTECTED_PROPERTY(char, padding[3]);
	NodeElement* Archive;

	// ranged for support
	NodeElement* begin() const { return IndexTable; }
	NodeElement* end() const { return &IndexTable[IndexCount]; }

private:
	bool IncreaseTableSize(int nAmount);
	bool IsArchiveSame(TKey id) const;
	void InvalidateArchive();
	void SetArchive(NodeElement const* pNode);
	NodeElement const* SearchForNode(TKey id) const;
};

template<typename TKey, typename TValue>
IndexClass<TKey, TValue>::IndexClass() :
	IndexTable(0),
	IndexCount(0),
	IndexSize(0),
	IsSorted(false),
	Archive(0)
{
	InvalidateArchive();
}

template<typename TKey, typename TValue>
IndexClass<TKey, TValue>::~IndexClass()
{
	Clear();
}

template<typename TKey, typename TValue>
void IndexClass<TKey, TValue>::Clear()
{
	GameDelete(IndexTable);
	IndexTable = 0;
	IndexCount = 0;
	IndexSize = 0;
	IsSorted = false;
	InvalidateArchive();
}

template<typename TKey, typename TValue>
bool IndexClass<TKey, TValue>::IncreaseTableSize(int amount)
{
	if (amount < 0) return false;

	NodeElement* table = GameCreateArray<NodeElement>(IndexSize + amount);
	if (table != nullptr)
	{
		for (int i = 0; i < IndexCount; ++i)
			table[i] = IndexTable[i];

		GameDelete(IndexTable);
		IndexTable = table;
		IndexSize += amount;
		InvalidateArchive();

		return true;
	}
	return false;
}

template<typename TKey, typename TValue>
bool IndexClass<TKey, TValue>::Reverse(int amount)
{
	Clear();
	return IncreaseTableSize(amount);
}

template<typename TKey, typename TValue>
inline void IndexClass<TKey, TValue>::Sort()
{
	if (!IsSorted)
	{
		std::sort(&IndexTable[0], &IndexTable[IndexCount]);
		InvalidateArchive();
		IsSorted = true;
	}
}

template<typename TKey, typename TValue>
int IndexClass<TKey, TValue>::Count() const
{
	return IndexCount;
}

template<typename TKey, typename TValue>
bool IndexClass<TKey, TValue>::IsPresent(TKey id) const
{
	if (!IndexCount)
		return false;

	if (IsArchiveSame(id))
		return true;

	NodeElement const* nodeptr = SearchForNode(id);

	if (nodeptr != nullptr)
	{
		const_cast<IndexClass<TKey, TValue>*>(this)->SetArchive(nodeptr);
		return true;
	}

	return false;
}

template<typename TKey, typename TValue>
const TValue& IndexClass<TKey, TValue>::FetchIndex(TKey id) const
{
	return IsPresent(id) ? Archive->Data : TValue();
}

template<typename TKey, typename TValue>
TValue& IndexClass<TKey, TValue>::FetchIndex(TKey id)
{
	if (!IsPresent(id))
	{
		AddIndex(id, TValue());
		IsPresent(id);
	}

	return Archive->Data;
}

template<typename TKey, typename TValue>
bool IndexClass<TKey, TValue>::IsArchiveSame(TKey id) const
{
	return Archive != 0 && Archive->ID == id;
}

template<typename TKey, typename TValue>
void IndexClass<TKey, TValue>::InvalidateArchive()
{
	Archive = nullptr;
}

template<typename TKey, typename TValue>
void IndexClass<TKey, TValue>::SetArchive(NodeElement const* node)
{
	Archive = const_cast<NodeElement*>(node);
}

template<typename TKey, typename TValue>
constexpr bool IndexClass<TKey, TValue>::AddIndex(TKey id, const TValue& data)
{
	if (IndexCount + 1 > IndexSize)
	{
		if (!IncreaseTableSize(IndexSize == 0 ? 10 : > IndexSize))
			return false;
	}

	IndexTable[IndexCount].ID = std::move(id);
	IndexTable[IndexCount].Data = std::move(data);
	++IndexCount;
	IsSorted = false;

	return true;
}

template<typename TKey, typename TValue>
bool IndexClass<TKey, TValue>::AddIndex(TKey id, TValue&& data)
{
	if (IndexCount + 1 > IndexSize)
	{
		if (!IncreaseTableSize(IndexSize == 0 ? 10 : IndexSize))
			return false;
	}

	IndexTable[IndexCount].ID = std::move(id);
	IndexTable[IndexCount].Data = std::move(data);
	++IndexCount;
	IsSorted = false;

	return true;
}

template<typename TKey, typename TValue>
bool IndexClass<TKey, TValue>::RemoveIndex(TKey id)
{
	int found_index = -1;
	for (int i = 0; i < IndexCount; ++i)
	{
		if (IndexTable[i].ID == id)
		{
			found_index = i;
			break;
		}
	}

	if (found_index != -1)
	{
		for (int i = found_index + 1; i < IndexCount; ++i)
			IndexTable[i - 1] = IndexTable[i];
		--IndexCount;

		IndexTable[IndexCount] = std::move(NodeElement(TKey(), TValue())); // zap last (now unused) element

		InvalidateArchive();
		return true;
	}

	return false;
}

template<typename TKey, typename TValue>
typename IndexClass<TKey, TValue>::NodeElement const* IndexClass<TKey, TValue>::SearchForNode(TKey id) const
{
	if (!IndexCount)
		return 0;

	const_cast<IndexClass<TKey, TValue>*>(this)->Sort();

	NodeElement node;
	node.ID = id;

	return std::lower_bound(&IndexTable[0], &IndexTable[IndexCount], node);
}
