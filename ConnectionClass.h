#pragma once

#include <YRPP.h>
#include <CommBufferClass.h>

// A single "connection" with another system. This is a pure virtual base
// class; a derived class supplies Init (protocol-specific setup) and Send
// (the actual hardware-dependent transmit).
//
// Every packet the application sends is prefixed with a CommHeaderType. The
// header carries a magic number (unique per product, so foreign traffic can
// be rejected), a code saying whether this is data or an ACK, and a packet ID
// used to detect resends and to hand packets to the application in order.
//
// Service() drives the ACK/retry logic and must be polled as often as
// possible. Because a derived class can override Service_Send_Queue and
// Service_Receive_Queue, a protocol that already guarantees delivery can skip
// ACKing entirely.

// Values for CommHeaderType::Code.
enum class ConnectionEnum : unsigned char
{
	PACKET_DATA_ACK = 0,   // a data packet requiring an ACK
	PACKET_DATA_NOACK = 1, // a data packet not requiring an ACK
	PACKET_ACK = 2,        // an ACK for a packet
	PACKET_COUNT = 3,      // for computational purposes
};

// The header prefixed to every packet the connection sends. YR widened RA's
// 7-byte header to 14 bytes; `ForwardTo` holds the packet router forwarding
// mask and is only filled in for internet games routed via the packet router.
#pragma pack(push, 1)
struct CommHeaderType
{
	short MagicNumber;
	ConnectionEnum Code;
	char ForwardTo;
	int PacketID;
	int field_8;
	short field_C;
};
#pragma pack(pop)
static_assert(sizeof(CommHeaderType) == 14);

class NOVTABLE ConnectionClass
{
public:
	virtual ~ConnectionClass() RX;

	virtual void Init()
		{ JMP_THIS(0x48BF10); }

	// Queues a packet for sending. `forwardto` is only written into the
	// header when the game is an internet game running via the packet router.
	virtual int Send_Packet(void* buf, int buflen, int ack_req, char forwardto)
		{ JMP_THIS(0x48BF40); }

	// Tells the connection a packet has arrived; the connection manager calls
	// this after parsing an incoming datagram.
	virtual int Receive_Packet(CommHeaderType* buf, int buflen)
		{ JMP_THIS(0x48C040); }

	// Pulls the next application packet out of the receive queue, stripping
	// the CommHeaderType. Returns zero when nothing is ready.
	virtual int Get_Packet(void* buf, int* buflen)
		{ JMP_THIS(0x48C320); }

	// The main polling routine. Should be called as often as possible.
	virtual int Service()
		{ JMP_THIS(0x48C3B0); }

	// Returns the current time in 16-millisecond ticks, the retry logic's unit.
	static unsigned int Time()
		{ JMP_STD(0x48C600); }

protected:
	// Drops send queue entries that have been ACK'd. The base implementation
	// is a stub returning zero; IPXGlobalConnClass overrides it.
	virtual int Purge_Send_Queue()
		{ JMP_THIS(0x48C590); }

	virtual int Service_Send_Queue()
		{ JMP_THIS(0x48C3E0); }
	virtual int Service_Receive_Queue()
		{ JMP_THIS(0x48C5A0); }

	// Performs the hardware-dependent send. Pure virtual, and protected
	// because only the ACK/retry logic calls it, never the application.
	virtual int Send(CommHeaderType* buf, int buflen, void* extrabuf, int extralen, bool isGlobalConn, short port) = 0;

	// Properties
public:
	CommBufferClass* Queue;
	int NumResends;
	int NumLost;
	int PercentLost;
	int MissedOverall;
	int MissedMagic;
	unsigned int MaxPacketLen; // includes the CommHeaderType
	// Global connections append a 2-byte ProductID at +14: their payload
	// starts at +16, not sizeof(CommHeaderType).
	CommHeaderType* PacketBuf;
	unsigned short MagicNum;
	unsigned int RetryDelta; // delay before a packet is re-sent
	unsigned int MaxRetries;
	unsigned int Timeout;
	int NumRecNoAck;
	int NumRecAck;
	int NumSendNoAck;
	int NumSendAck;
	int LastSeqID;  // ID of the last consecutively-received packet
	int LastReadID; // ID of the last PACKET_DATA_ACK packet read
};
static_assert(sizeof(ConnectionClass) == 0x4C);
