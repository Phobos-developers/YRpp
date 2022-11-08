#pragma once

#include <Memory.h>

// The Westwood genius pointer priority queue
template<typename T, typename Pr = std::less<T>>
class PointerHeapClass
{
public:
	PointerHeapClass(int capacity)
	{
		Capacity = capacity;
		Datas = (T**)YRMemory::Allocate(sizeof(T*) * (Capacity + 1));
		Count = 0;
		LMost = (T*)nullptr;
		RMost = (T*)0xFFFFFFFF;

		ClearAll();
	}

	~PointerHeapClass()
	{
		YRMemory::Deallocate(Datas);
		Datas = (T**)nullptr;
	}

	void Clear()
	{
		memset(Datas, 0, sizeof(T*) * (Count + 1));
	}

	T* Top()
	{
		return Count == 0 ? nullptr : Datas[1];
	}

	bool Pop()
	{
		if (Count == 0)
			return false;

		Datas[1] = Datas[Count--];
		int now = 1;
		while (now * 2 <= Count)
		{
			int next = now * 2;
			if (next < Count && Comp(Datas[next + 1], Datas[next]))
				++next;
			if (Comp(Datas[now], Datas[next]))
				break;

			// Westwood did Datas[now] = Datas[next] here
			std::swap(Datas[now], Datas[next]);

			now = next;
		}

		return true;
	}

	bool Push(T* pValue)
	{
		if (Count >= Capacity)
			return false;

		Datas[++Count] = pValue;
		int now = Count;
		while (now != 1)
		{
			int next = now / 2;
			if (!Comp(Datas[now], Datas[next]))
				break;

			// Westwood did Datas[now] = Datas[next] here
			std::swap(Datas[now], Datas[next]);

			now = next;
		}

		return true;
	}

	bool WWPop()
	{
		if (Pop())
		{
			for (int i = 1; i <= Count; ++i)
				WWPointerUpdate(Datas[i]);

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
		memset(Datas, 0, sizeof(T*) * (Capacity + 1));
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
	T** Datas;
	T* LMost;
	T* RMost;
};