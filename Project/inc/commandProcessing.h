//FIXME


#ifndef __COMMANDPROCESSING_H__
#define __COMMANDPROCESSING_H__

#include "arch/cc.h"
extern "C" {
#include "stm32f4x7_eth.h"
#include "netconf.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tcpip.h"
#include <string.h>
#include "LCD.h"
}
#include "errorHandlers.h"
#include "sendRcvTask.h"

struct OnePacket
{
	u16_t length; //2 bytes
	uint8_t * data;//[560];
	void clean()
	{
		if( shouldClean() )
		{
			vPortFree(this->data);
		}
	}
	bool shouldClean()
	{
		return (!(this->length & (1 << 13)));
	}
	u16_t cleanLength()
	{
		return (this->length & 0x1FFF);
	}
	bool markToNoFree()
	{
		this->length |= (1 << 13);
	}
};

struct TableOf16bits
{
	u16_t length; //2 bytes
	u16_t * data;//[280];
	void clean()
	{
		vPortFree(this->data);
	}
};

struct PointerToTableOf16bits
{
	u16_t length; //2 bytes
	uint8_t * data;
	void clean()
	{
		vPortFree(this);
	}
};

struct Cluster
{
	u8_t command;
	u8_t nrOfParameters;
	u16_t parameters[270];
	u8_t check_for_parameters(u8_t expected);
	void parseCommand();
};


#endif
