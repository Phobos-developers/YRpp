#pragma once

#include <Memory.h>

template<typename T, typename Pr = std::less<T>>
class PriorityQueueClass
{
public:
	PriorityQueueClass(int capacity)
	{
		Capacity = capacity;
		Nodes = (T**)YRMemory::Allocate(sizeof(T*) * (Capacity + 1));
		Count = 0;
		LMost = (T*)nullptr;
		RMost = (T*)0xFFFFFFFF;

		ClearAll();
	}

	~PriorityQueueClass()
	{
		YRMemory::Deallocate(Nodes);
		Nodes = (T**)nullptr;
	}

	void Clear()
	{
		memset(Nodes, 0, sizeof(T*) * (Count + 1));
	}

	T* Top()
	{
		return Count == 0 ? nullptr : Nodes[1];
	}

	bool Pop()
	{
		if (Count == 0)
			return false;

		Nodes[1] = Nodes[Count--];
		int now = 1;
		while (now * 2 <= Count)
		{
			int next = now * 2;
			if (next < Count && Comp(Nodes[next + 1], Nodes[next]))
				++next;
			if (Comp(Nodes[now], Nodes[next]))
				break;

			// Westwood did Nodes[now] = Nodes[next] here
			std::swap(Nodes[now], Nodes[next]);

			now = next;
		}

		return true;
	}

	bool Push(T* pValue)
	{
		if (Count >= Capacity)
			return false;

		Nodes[++Count] = pValue;
		int now = Count;
		while (now != 1)
		{
			int next = now / 2;
			if (!Comp(Nodes[now], Nodes[next]))
				break;

			// Westwood did Nodes[now] = Nodes[next] here
			std::swap(Nodes[now], Nodes[next]);

			now = next;
		}

		return true;
	}

	bool WWPop()
	{
		if (Pop())
		{
			for (int i = 1; i <= Count; ++i)
				WWPointerUpdate(Nodes[i]);

			return true;
		}

		return false;
	}

	bool WWPush(T* pValue)
	{
		if (Push(pValue))
		{
			WWPointerUpdate(pValue);

			return true;
		}

		return false;
	}

private:
	void ClearAll()
	{
		memset(Nodes, 0, sizeof(T*) * (Capacity + 1));
	}

	bool Comp(T* p1, T* p2)
	{
		return Pr()(*p1, *p2);
	}

	void WWPointerUpdate(T* pValue)
	{
		if (pValue > RMost)
			RMost = pValue;
		if (pValue < LMost)
			LMost = pValue;
	}

public:
	int Capacity;
	int Count;
	T** Nodes;
	T* LMost;
	T* RMost;
};

struct PriorityQueueClassNode
{
	static int __fastcall SurfaceDataCount() JMP_STD(0x42B1F0);
	static int __fastcall ToSurfaceIndex(const CellStruct& mapCoord) JMP_STD(0x42B1C0);

	int ToSurfaceIndex()
	{
		return ToSurfaceIndex(MapCoord);
	}

	CellStruct MapCoord;
	float Score;

	bool operator<(const PriorityQueueClassNode& another) const
	{
		return Score < another.Score;
	}
};
