#pragma once

#include <ASMMacros.h>

class IPXAddressClass
{
public:
	IPXAddressClass()
		{ JMP_THIS(0x53ECB0) }

	IPXAddressClass(const unsigned char* network, const unsigned char* node, unsigned short port)
		{ JMP_THIS(0x53ECE0) }

	void Set_Address(const unsigned char* network, const unsigned char* node, unsigned short port)
		{ JMP_THIS(0x53ED20) }

	void Get_Address(unsigned char* network, unsigned char* node, unsigned short* port) const
		{ JMP_THIS(0x53ED60) }

	void Get_Address(unsigned char* network, unsigned char* node) const
		{ JMP_THIS(0x53EDA0) }

	int Is_Broadcast() const
		{ JMP_THIS(0x53EE00) }

	const char* As_String(const IPXAddressClass* address = nullptr) const
		{ JMP_THIS(0x53F0E0) }

	void Set_Port(unsigned short port)
		{ JMP_THIS(0x53F200) }

	bool operator==(const IPXAddressClass& other) const
		{ JMP_THIS(0x53EE70) }

	bool operator!=(const IPXAddressClass& other) const
		{ JMP_THIS(0x53EF60) }

	unsigned char NetworkNumber[4];
	unsigned char NodeAddress[6];
};
