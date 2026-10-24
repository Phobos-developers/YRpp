#pragma once

#include <YRPP.h>

struct TheirSync
{
	DEFINE_ARRAY_REFERENCE(TheirSync, [7], Array, 0xAFA358)

	int Frame;
	int CommandsSent;
	int CommandsReceived;
	int ResponseTime;
	int RouterResponseTime;
	int LastHeardTime;
};
static_assert(sizeof(TheirSync) == 0x18);
