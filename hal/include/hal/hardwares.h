// Sample button module 
// Part of the Hardware Abstraction Layer (HAL) 

#ifndef _BUTTON_H_
#define _BUTTON_H_

#define JS_LEFT "/sys/class/gpio/gpio65/value"
#define JS_RIGHT "/sys/class/gpio/gpio47/value"
#define JS_UP "/sys/class/gpio/gpio26/value"
#define JS_DOWN "/sys/class/gpio/gpio46/value"

#define LED0 "/sys/class/leds/beaglebone:green:usr0"
#define LED1 "/sys/class/leds/beaglebone:green:usr1"
#define LED2 "/sys/class/leds/beaglebone:green:usr2"
#define LED3 "/sys/class/leds/beaglebone:green:usr3"




#include <stdbool.h>

void runCommand(char*);
void init_all(void);
void ledDefault(void);
void upLight(void);
void downLight(void);
void allLight(void);
void allOff(void);
int readFromFileToScreen(char*);

#endif