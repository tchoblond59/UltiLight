// Relay.h

#ifndef _RELAY_h
#define _RELAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define RELAY_ON 1
#define RELAY_OFF 0
#include <C:\Users\julie\Documents\Arduino\libraries\MySensors\core\MySensorsCore.h> //If someone can explain me why i have to do this shit...
#include "MyNodeDefinition.h"
class Relay
{
 protected:


 public:
	void receive(const MyMessage &message);
	void init(uint8_t pin, bool state);
	void enable();
	void disable();
private:
	uint8_t m_pin;
	bool m_state;
};

#endif

