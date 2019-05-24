#ifndef MyNodeDefinition_h
#define MyNodeDefinition_h

/* *******************************************************************************************************************
*                                          MYSENSORS
* ******************************************************************************************************************/
#define MY_BAUD_RATE      115200
#define MY_NODE_ID        1
#define MY_DEBUG
#define MY_DEBUG_SKETCH                               // Enable specific sketch debug prints to serial monitor, comment it to save memory

// Enable and select radio type attached
#define MY_RADIO_RFM69          // Enable RFM69 radio
#define MY_IS_RFM69HW // Omit if your RFM is not "H"
#define MY_RFM69_NEW_DRIVER
#define MY_RFM69_FREQUENCY   RFM69_915MHZ

#define RELEASE           "0.1"
#define NODE_NAME         "UltiLight"

#define CHILD_ID_DIMMER1 10
#define CHILD_ID_DIMMER2 20

#endif