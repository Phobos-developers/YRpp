/*******************************************************************************
/*                     O P E N  S O U R C E  --  T S + +                      **
/*******************************************************************************
 *
 *  @project       TS++
 *
 *  @file          QUEUE.H
 *
 *  @authors       CCHyper, ZivDero (adjustments for YR)
 *
 *  @brief         FIFO queue for events.
 *
 *  @license       TS++ is free software: you can redistribute it and/or
 *                 modify it under the terms of the GNU General Public License
 *                 as published by the Free Software Foundation, either version
 *                 3 of the License, or (at your option) any later version.
 *
 *                 TS++ is distributed in the hope that it will be
 *                 useful, but WITHOUT ANY WARRANTY; without even the implied
 *                 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *                 PURPOSE. See the GNU General Public License for more details.
 *
 *                 You should have received a copy of the GNU General Public
 *                 License along with this program.
 *                 If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
#pragma once

#include <Unsorted.h>


template<class T, int size>
class QueueClass
{
public:
	QueueClass();
	~QueueClass() { }

	T& operator[](int index);

	T& First();
	void Init();
	int Next();
	bool Add(const T& q);

	int GetHead();
	int GetTail();
	T* GetArray();

public:
	int Count;

private:
	int Head;
	int Tail;
	T Array[size];
	int Timings[size];
};


template<class T, int size>
inline QueueClass<T, size>::QueueClass() :
	Count(0)
{
	Init();
}


template<class T, int size>
inline void QueueClass<T, size>::Init()
{
	Count = 0;
	Head = 0;
	Tail = 0;
}


template<class T, int size>
inline bool QueueClass<T, size>::Add(const T& q)
{
	if (Count < size)
	{
		Array[Tail] = q;
		#pragma warning(suppress: 4996)
		Timings[Tail] = static_cast<int>(Imports::TimeGetTime()());
		Tail = (Tail + 1) & (size - 1);
		Count = Count + 1;
		return true;
	}
	return false;
}


template<class T, int size>
inline int QueueClass<T, size>::Next()
{
	if (Count)
	{
		Head = (Head + 1) & (size - 1);
		Count = Count - 1;
	}
	return Count;
}


template<class T, int size>
inline T& QueueClass<T, size>::operator[](int index)
{
	return Array[(Head + index) & (size - 1)];
}


template<class T, int size>
inline T& QueueClass<T, size>::First()
{
	return Array[Head];
}


template<class T, int size>
inline int QueueClass<T, size>::GetHead()
{
	return Head;
}


template<class T, int size>
inline int QueueClass<T, size>::GetTail()
{
	return Tail;
}


template<class T, int size>
inline T* QueueClass<T, size>::GetArray()
{
	return Array;
}
