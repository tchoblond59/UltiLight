#include "MyNodeDefinition.h"
#include <MySensors.h>
#include "Dimmer.h"
#include "Relay.h"

#include <SPI.h>


Dimmer dimmer1;
Dimmer dimmer2;
Relay array_relay[6];
void setup() {
	Serial.begin(MY_BAUD_RATE);
	Wire.begin();
	dimmer1.init(0x27, CHILD_ID_DIMMER1);
	dimmer2.init(0x26, CHILD_ID_DIMMER2);
	for (size_t i = 0; i < 6; i++)
	{
		Relay my_relay;
		my_relay.init(A0 + i, RELAY_OFF);
		array_relay[i] = my_relay;
	}
	Serial.println("Running");
	Serial.println(A0);

}

// the loop function runs over and over again until power down or reset
void loop() {
	dimmer1.update();
	dimmer2.update();
}

void receive(const MyMessage& message)
{
	Serial.println("Receive");
	dimmer1.handleMsg(message);
	dimmer2.handleMsg(message);
	for (size_t i = 0; i < 6; i++)
	{
		array_relay[i].receive(message);
	}
}
