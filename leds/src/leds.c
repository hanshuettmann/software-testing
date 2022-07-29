#include <leds.h>

#define LEDS_OFFSET 1
#define FIRST_BIT_ON 1
#define LEDS_ALL_OFF 0
#define LEDS_ALL_ON 0xFFFF

static uint16_t *port;

static uint16_t LedToMask(uint8_t led)
{
    return (FIRST_BIT_ON << (led - LEDS_OFFSET));
}

void CreateLeds(uint16_t *port_address)
{
    port = port_address;
    *port = LEDS_ALL_OFF;
}

void TurnLedOn(uint8_t led)
{
    *port |= LedToMask(led);
}

void TurnLedOff(uint8_t led)
{
    *port &= ~LedToMask(led);
}

void TurnAllLedOn(void)
{
    *port = LEDS_ALL_ON;
}

void TurnAllLedOff(void)
{
    *port = LEDS_ALL_OFF;
}

bool CheckLedState(uint8_t led)
{
    return *port & (1 << led - LEDS_OFFSET);
}