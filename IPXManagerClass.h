#pragma once
#include <YRPP.h>

class IPXConnClass;
class IPXGlobalConnClass;
class ConnectionClass;

class NOVTABLE IPXManagerClass
{
public:
	// Static
	DEFINE_REFERENCE(IPXManagerClass, Instance, 0xA8E9C0u)

	virtual ~IPXManagerClass() RX;

	ConnectionClass* SetTiming(int retrydelta, int maxretries, int timeout, bool a5)
		{ JMP_THIS(0x540C60) }

	int ResponseTime()
		{ JMP_THIS(0x542450) }

	// Properties
public:
	BYTE IPXStatus;
	BYTE Listening;
	DWORD Glb_MaxPacketLen;
	int Glb_NumPackets;
	DWORD Pvt_MaxPacketLen;
	DWORD Pvt_NumPackets;
	DWORD __Ext_MaxPacketLen;
	DWORD __Ext_MaxPackets;
	WORD ProductID;
	WORD Socket;
	DWORD ConnectionNum;
	IPXConnClass* Connection[7];
	DWORD NumConnections;
	IPXGlobalConnClass* __GlobalChannel;
	IPXGlobalConnClass* __IPXGlobalConn2;
	ConnectionClass* __MulticastConnection;
	DWORD CurConnection;
	DWORD RetryDelta;
	DWORD MaxRetries;
	DWORD Timeout;
	int __Global1RetryDelta;
	int __Global1Timing;
	int __Global1RetryTimeout;
	char field_70;
	char field_71;
	char field_72;
	char field_73;
	int field_74;
	char field_78;
	char field_79;
	char field_7A;
	char field_7B;
	int field_7C;
	int field_80;
	int field_84;
	int field_88;
	int field_8C;
	int field_90;
	int field_94;
	int field_98;
	int field_9C;
	DWORD SendOverflows;
	DWORD ReceiveOverflows;
	DWORD BadConnection;
};
static_assert(sizeof(IPXManagerClass) == 0xAC);
