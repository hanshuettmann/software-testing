#include <stdint.h>
#include <stdbool.h>

void CreateLeds(uint16_t *port_address);
void TurnLedOn(uint8_t led);
void TurnLedOff(uint8_t led);
void TurnAllLedOn(void);
void TurnAllLedOff(void);
bool CheckLedState(uint8_t led);