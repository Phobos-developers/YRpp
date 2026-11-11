#pragma once

#include <YRPP.h>

struct CommHeaderType;

// Flag bits shared by both queue entry types. Westwood declared these as
// single-bit bitfields; the game reads and writes them as a plain int.
enum CommQueueFlags
{
	COMMQUEUE_IS_ACTIVE = 0x1, // this entry holds a packet and is ready to be processed
	COMMQUEUE_IS_READ = 0x2,   // send queue: ACK received. receive queue: caller has read it
	COMMQUEUE_IS_ACK = 0x4,    // an ACK has been sent for this packet
};

// One outgoing queue entry.
struct SendQueueType
{
	int Flags;
	int FirstTime;   // time this packet was first sent
	int LastTime;    // time this packet was last sent
	int SendCount;   // number of times this packet has been sent
	int BufLen;      // size of the packet stored in this entry
	CommHeaderType* Buffer;
	int ExtraLen;    // size of the extra data (an IPXAddressClass, for global conns)
	void* ExtraBuffer;
	short Port;      // destination port this entry was queued for
};
static_assert(sizeof(SendQueueType) == 0x24);

// One incoming queue entry. Unlike RA's, YR's tracks the time the packet was
// received so IPXGlobalConnClass::Strip_Packets can age entries out.
struct ReceiveQueueType
{
	int Flags;
	int Time;
	int BufLen;
	void* Buffer;
	int ExtraLen;
	void* ExtraBuffer;
};
static_assert(sizeof(ReceiveQueueType) == 0x18);

// Stores the packets sent and received by a single ConnectionClass. Entries
// are addressed through an index array rather than moved, so unqueueing an
// entry does not disturb the others.
class NOVTABLE CommBufferClass
{
public:
	virtual ~CommBufferClass() RX;

	// Clears both queues. Init_Send_Queue clears only the send queue, which
	// is what a reconnect needs.
	void Init()
		{ JMP_THIS(0x48B2A0); }
	void Init_Send_Queue()
		{ JMP_THIS(0x48B390); }

	// Send queue. Queue_Send returns zero when the queue is full.
	int Queue_Send(void* buf, int buflen, void* extrabuf, int extralen, short port)
		{ JMP_THIS(0x48B410); }
	int UnQueue_Send(void* buf, int* buflen, int index, void* extrabuf, int* extralen, short port)
		{ JMP_THIS(0x48B570); }
	SendQueueType* Get_Send(int index)
		{ JMP_THIS(0x48B720); }
	int Num_Send() const
		{ return this->SendCount; }
	int Max_Send() const
		{ return this->MaxSend; }

	// Receive queue.
	int Queue_Receive(void* buf, int buflen, void* extrabuf, int extralen)
		{ JMP_THIS(0x48B750); }
	int UnQueue_Receive(void* buf, int* buflen, int index, void* extrabuf, int* extralen)
		{ JMP_THIS(0x48B890); }
	ReceiveQueueType* Get_Receive(int index)
		{ JMP_THIS(0x48B9E0); }
	int Num_Receive() const
		{ return this->ReceiveCount; }
	int Max_Receive() const
		{ return this->MaxReceive; }

	// Response time tracking. The caller feeds in a delay whenever it detects
	// an outgoing message has been ACK'd; the class keeps a running mean.
	void Add_Delay(unsigned int delay)
		{ JMP_THIS(0x48BA10); }
	unsigned int Avg_Response_Time()
		{ JMP_THIS(0x48BA80); }
	unsigned int Max_Response_Time()
		{ JMP_THIS(0x48BA90); }

	// Properties
public:
	int MaxSend;
	int MaxReceive;
	int MaxPacketSize;
	int MaxExtraSize;

	unsigned int DelaySum;
	unsigned int NumDelay;
	unsigned int MeanDelay;
	unsigned int MaxDelay;

	SendQueueType* SendQueue;
	int SendCount;          // number of entries currently queued
	unsigned int SendTotal; // total ever added, used as the outgoing packet ID
	int* SendIndex;

	ReceiveQueueType* ReceiveQueue;
	int ReceiveCount;
	unsigned int ReceiveTotal;
	int* ReceiveIndex;

	int DebugOffset;
	int DebugSize;
	char** DebugNames;
	int DebugNameStart;
	int DebugNameCount;
};
static_assert(sizeof(CommBufferClass) == 0x58);
