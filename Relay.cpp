// 
// 
// 

#include "Relay.h"
#include <core/MySensorsCore.h>

void Relay::receive(const MyMessage& message)
{
	if (message.sensor == m_pin)//If concern
	{
		if (message.type == V_STATUS)
		{
			if (message.getBool())
			{
				enable();
			}
			else
			{
				disable();
			}
		}
	}
}

void Relay::init(uint8_t pin, bool state)
{
	m_pin = pin;
	pinMode(m_pin, OUTPUT);
	m_state = state;
	if (m_state)
		enable();
	else
		disable();
}

void Relay::enable()
{
	m_state = RELAY_ON;
	digitalWrite(m_pin, m_state);
}

void Relay::disable()
{
	m_state = RELAY_OFF;
	digitalWrite(m_pin, m_state);
}
