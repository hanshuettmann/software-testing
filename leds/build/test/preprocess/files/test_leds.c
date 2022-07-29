#include "src/leds.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
uint16_t virtual_leds;





void setUp(void)

{

    CreateLeds(&virtual_leds);

}





void test_init_leds_off(void)

{



    uint16_t virtual_leds = 0xFFFF;



    CreateLeds(&virtual_leds);





    UnityAssertEqualNumber((UNITY_INT)((0x0000)), (UNITY_INT)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

}





void test_turn_led_on(void)

{

    TurnLedOn(3);





    UnityAssertEqualNumber((UNITY_INT)((1 << 2)), (UNITY_INT)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT);

}





void test_turn_led_off(void)

{

    TurnLedOn(3);

    TurnLedOff(3);





    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);

}





void test_toggle_multiple_leds(void)

{

    TurnLedOn(3);

    TurnLedOn(7);

    TurnLedOff(7);





    UnityAssertEqualNumber((UNITY_INT)((1 << 2)), (UNITY_INT)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_INT);

}





void test_turn_all_led_on(void)

{

    TurnAllLedOn();





    UnityAssertEqualNumber((UNITY_INT)((0xFFFF)), (UNITY_INT)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);

}





void test_turn_all_led_off(void)

{

    TurnAllLedOff();





    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((virtual_leds)), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT);

}





void test_check_led_state_on(void)

{

    TurnLedOn(5);



    

   _Bool 

        ledState = CheckLedState(5);





    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((ledState)), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);

}





void test_check_led_state_off(void)

{

    TurnLedOn(8);

    TurnLedOff(8);



    

   _Bool 

        ledState = CheckLedState(8);





    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((ledState)), (

   ((void *)0)

   ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);

}
