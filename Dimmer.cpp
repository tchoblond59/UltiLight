#include "Dimmer.h"
#include <core/MySensorsCore.h>

//Dimmer Dimmer;

void Dimmer::init(char i2c_address, char channel_0)
{
	m_i2c_address = i2c_address;
	m_channel_0 = channel_0;
	for (int channel = 0; channel < CHANNELS; channel++)
	{
		m_target_value[channel] = 100;
		m_old_value[channel] = 100;
		m_delay_between_change[channel] = DIMMER_DELAY / 100;
		m_last_change[channel] = millis();
		m_min_light_value[channel] = 0;
		m_max_light_value[channel] = 100;
		m_enable_dimmer_delay[channel] = true;

	}
}

void Dimmer::handleMsg(const MyMessage& message)
{
	if (message.sensor >= m_channel_0 && message.sensor < m_channel_0 + CHANNELS)//If channel exists
	{
		char channel = message.sensor - m_channel_0;
		if (message.type == V_PERCENTAGE)
		{
			setLevel(channel, message.getInt());
		}
		else if (message.type == V_STATUS)
		{
			if (message.getBool())
			{
				setLevel(channel, 100);
			}
			else
			{
				setLevel(channel, 0);
			}
		}
		else if (message.type == V_VAR1)//Delay for dimming
		{
			setDimmerDelay(channel, message.getInt());
		}
		else if (message.type == V_VAR2)//Min light value
		{
			setMinValue(channel, message.getInt());
		}
		else if (message.type == V_VAR3)//Max light value
		{
			setMaxValue(channel, message.getInt());
		}
		else if (message.type == V_VAR4)//Enable dimmer delay or not
		{
			if (message.getBool())
				enableDimmerTime(channel);
			else
				disableDimmerTime(channel);
		}
	}
}

void Dimmer::setLevel(char channel, char level, bool no_delay = false)
{
	if (level < m_min_light_value[channel])
		level = m_min_light_value[channel];
	else if (level > m_max_light_value[channel])
		level = m_max_light_value[channel];

	if (no_delay == true)//Force instant level
	{
		m_old_value[channel] = level;
		set(channel, level);
	}
	else
	{
		m_target_value[channel] = level;
	}
}

void Dimmer::enableDimmerTime(char channel)
{
	m_enable_dimmer_delay[channel] = true;
}

void Dimmer::disableDimmerTime(char channel)
{
	m_enable_dimmer_delay[channel] = false;
}

void Dimmer::setMinValue(char channel, char value)
{
	m_min_light_value[channel] = value;
}

void Dimmer::setMaxValue(char channel, char value)
{
	m_max_light_value[channel] = value;
}

void Dimmer::setDimmerDelay(char channel, char seconds)
{
	m_delay_between_change[channel] = seconds * 10;//seconds * 1000 / 100
}

void Dimmer::update()
{
	for (int channel = 0; channel < CHANNELS; channel++)
	{
		if (m_target_value[channel] != m_old_value[channel])
		{
			char diff = abs(m_old_value[channel] - m_target_value[channel]);
			if (m_enable_dimmer_delay[channel])
			{
				if (millis() - m_last_change[channel] >= m_delay_between_change[channel])//If it's time to change value
				{
					if (m_target_value[channel] > m_old_value[channel])//Target value is higher
					{
						m_old_value[channel]++;//Increase value
					}
					else
					{
						m_old_value[channel]++;//Decrease value
					}
					set(channel, m_old_value[channel]);
					m_last_change[channel] = millis();
				}
			}
			else
			{
				set(channel, m_target_value[channel]);
				m_old_value[channel] = m_target_value[channel];
			}
		}
	}
}

void Dimmer::set(char channel, char level)
{
	Wire.beginTransmission(m_i2c_address);
	Wire.write(BASE_CH + channel);
	Wire.write(100 - level);
	Wire.endTransmission();
}
