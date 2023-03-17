// Dimmer.h
#ifndef _DIMMER_h
#define _DIMMER_h


#define BASE_CH 0x80
#define CHANNELS 4
#define DIMMER_DELAY 3000
#include "MyNodeDefinition.h"
#include <Wire.h>
#include <core/MyMessage.h>

class Dimmer
{
protected:


public:
	void init(char i2c_address, char channel_0);
	void handleMsg(const MyMessage& message);
	void setLevel(char channel, char level, bool no_delay = false);
	void enableDimmerTime(char channel);
	void disableDimmerTime(char channel);
	void setMinValue(char channel, char value);
	void setMaxValue(char channel, char value);
	void setDimmerDelay(char channel, char seconds);
	void update();
private:
	void set(char channel, char level);
	unsigned long m_delay_between_change[CHANNELS];
	unsigned long m_last_change[CHANNELS];
	char m_target_value[CHANNELS];
	char m_old_value[CHANNELS];
	char m_min_light_value[CHANNELS];
	char m_max_light_value[CHANNELS];
	bool m_enable_dimmer_delay[CHANNELS];
	char m_i2c_address;
	char m_channel_0;
};

//extern Dimmer Dimmer;

#endif
