#include "unity.h"
#include "leds.h"

/**
 * Init all LED's off
 * Turn one LED on
 * Turn one LED off
 * Turn on and turn off multiple leds
 * Turn all LED's on at once
 * Turn all LED's off at once
 * Check LED state ON
 * Check LED state OFF
 * Review Parameters border condition limits
 * Review Parameters outside limits
 */

/* Simulate gpio port address */
uint16_t virtual_leds;

/* Executed before starting tests */
void setUp(void)
{
    CreateLeds(&virtual_leds);
}

// Init all leds off
void test_init_leds_off(void)
{
    /* Simulate gpio port address */
    uint16_t virtual_leds = 0xFFFF;

    CreateLeds(&virtual_leds);

    /* Bits should be equals to zero */
    TEST_ASSERT_EQUAL(0x0000, virtual_leds);
}

// Turn one led on
void test_turn_led_on(void)
{
    TurnLedOn(3);

    /* Bit 2 should be equals to 1 --> 0000000000000100 */
    TEST_ASSERT_EQUAL(1 << 2, virtual_leds);
}

// Turn one led off
void test_turn_led_off(void)
{
    TurnLedOn(3);
    TurnLedOff(3);

    /* Bit 2 should be equals to 1 --> 0000000000000100 */
    TEST_ASSERT_EQUAL(0, virtual_leds);
}

// Turn on and turn off multiple leds
void test_toggle_multiple_leds(void)
{
    TurnLedOn(3);
    TurnLedOn(7);
    TurnLedOff(7);

    /* Bit 2 should be equals to 1 --> 0000000000000100 */
    TEST_ASSERT_EQUAL(1 << 2, virtual_leds);
}

// Turn on all led's at once
void test_turn_all_led_on(void)
{
    TurnAllLedOn();

    /* All led's on corresponds to port -> 0xFFFF */
    TEST_ASSERT_EQUAL(0xFFFF, virtual_leds);
}

// Turn off all led's at once
void test_turn_all_led_off(void)
{
    TurnAllLedOff();

    /* All led's on corresponds to port -> 0 */
    TEST_ASSERT_EQUAL(0, virtual_leds);
}

// Check Led State is ON
void test_check_led_state_on(void)
{
    TurnLedOn(5);

    bool ledState = CheckLedState(5);

    /* ledState == true -> ledState ON */
    TEST_ASSERT_EQUAL(true, ledState);
}

// Check Led State is OFF
void test_check_led_state_off(void)
{
    TurnLedOn(8);
    TurnLedOff(8);

    bool ledState = CheckLedState(8);

    /* ledState == false -> ledState OFF */
    TEST_ASSERT_EQUAL(false, ledState);
}